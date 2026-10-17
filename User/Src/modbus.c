/** @file modbus.c @brief 只保留流量查询、上位机命令解析和应答组帧。 */
#include "modbus.h"
#include "crc16.h"
#include "usart.h"
#include <math.h>
#include <string.h>

/**
 * @brief 通过UART5查询EMF89瞬时流量，完成发送、接收、校验及float转换。
 * @param meter_address 流量计实际从站地址，1~247。
 * @param flow 输出瞬时流量，单位取决于仪表设置；失败时保持原值。
 * @return HAL_OK成功，HAL_TIMEOUT收发超时，HAL_ERROR参数/应答/CRC错误。
 * @note 仅主循环调用，UART5不可同时用于接收IT/DMA或其他事务。
 *       UART5串口参数必须与仪表一致；PD4高发送、低接收，需符合硬件接线。
 */
HAL_StatusTypeDef Modbus_ReadFlow(uint8_t meter_address, float *flow)
{
    uint8_t request[8] = {0U, 0x03U, 0U, 0U, 0U, 2U, 0U, 0U};
    uint8_t response[9];
    uint16_t crc;
    uint32_t bits, started, elapsed;
    float result;
    HAL_StatusTypeDef status;

    if (flow == NULL || meter_address == 0U || meter_address > 247U
        || huart5.Instance != UART5 || huart5.Init.BaudRate == 0U) {
        return HAL_ERROR;
    }

    request[0] = meter_address;
    request[2] = (uint8_t)(MODBUS_FLOW_REGISTER >> 8U);
    request[3] = (uint8_t)MODBUS_FLOW_REGISTER;
    crc = crc_16(request, 6U);
    request[6] = (uint8_t)crc;           // CRC低字节先发送。
    request[7] = (uint8_t)(crc >> 8U);

    HAL_GPIO_WritePin(RS485D_GPIO_Port, RS485D_Pin, GPIO_PIN_SET);

    status = HAL_UART_Transmit(&huart5, request, sizeof(request), MODBUS_TIMEOUT_MS);
    /* HAL正常返回时最后一个停止位已发完；发送失败也必须释放发送方向。 */
    HAL_GPIO_WritePin(RS485D_GPIO_Port, RS485D_Pin, GPIO_PIN_RESET);
    if (status != HAL_OK) { return status; }

    started = HAL_GetTick();
    status = HAL_UART_Receive(&huart5, response, 3U, MODBUS_TIMEOUT_MS);
    if (status != HAL_OK) { return status; }
    if (response[0] != meter_address) { return HAL_ERROR; }

    /* 正常应答为9字节，异常应答为5字节，不能始终等待9字节。 */
    if (response[1] != 0x83U && (response[1] != 0x03U || response[2] != 4U)) {
        return HAL_ERROR;
    }

    elapsed = (uint32_t)(HAL_GetTick() - started);
    if (elapsed >= MODBUS_TIMEOUT_MS) { return HAL_TIMEOUT; }

    status = HAL_UART_Receive(&huart5, &response[3], response[1] == 0x83U ? 2U : 6U, MODBUS_TIMEOUT_MS - elapsed);

    if (status != HAL_OK) { return status; }
    if (!CRC16_Check(response, response[1] == 0x83U ? 5U : 9U) || response[1] == 0x83U) { return HAL_ERROR; }

    /* 手册示例C1 48 00 00为-12.5：高字节在前的IEEE754单精度数。 */
    bits = ((uint32_t)response[3] << 24U) | ((uint32_t)response[4] << 16U)
         | ((uint32_t)response[5] << 8U) | response[6];
    memcpy(&result, &bits, sizeof(result)); // 避免通过强制指针转换破坏严格别名规则。
    if (!isfinite(result)) { return HAL_ERROR; }
    *flow = result;                     // 全部验证成功后才更新流量。
    return HAL_OK;
}

/**
 * @brief 从一帧完整的上位机06写单寄存器请求中提取命令。
 * @param frame 完整8字节RTU请求，含CRC。
 * @param length 完整帧字节数。
 * @param command 输出命令；解析失败时保持原值。
 * @return 1解析成功，0表示地址、功能码、长度或CRC不符。
 * @note 上位机串口负责RTU分帧，本函数不接收字节、不执行设备动作。
 */
uint8_t Modbus_ParseCommand(const uint8_t *frame, uint16_t length,
                            ModbusCommand *command)
{
    if (frame == NULL || command == NULL || length != 8U
        || (frame[0] != MODBUS_HOST_ADDRESS && frame[0] != 0U)
        || frame[1] != 0x06U || !CRC16_Check(frame, length)) {
        return 0U;
    }
    command->address = (uint16_t)(((uint16_t)frame[2] << 8U) | frame[3]);
    command->value = (uint16_t)(((uint16_t)frame[4] << 8U) | frame[5]);
    command->broadcast = (uint8_t)(frame[0] == 0U);
    return 1U;
}

/**
 * @brief 业务处理完成后构建06成功/异常应答，不直接发送。
 * @param command 已由Modbus_ParseCommand成功解析且未修改的命令。
 * @param exception 0成功；01功能错误、02地址错误、03数值错误、04执行失败。
 * @param response 至少8字节的输出缓冲区。
 * @return 8为成功应答，5为异常应答，0为广播或空指针，无需发送。
 * @note 未接受或未执行命令时不要回复成功；实际发送使用上位机串口。
 */
uint16_t Modbus_BuildReply(const ModbusCommand *command, uint8_t exception,
                           uint8_t *response)
{
    uint16_t length, crc;
    if (command == NULL || response == NULL || command->broadcast) { return 0U; }
    response[0] = MODBUS_HOST_ADDRESS;
    if (exception == 0U) {
        response[1] = 0x06U;
        response[2] = (uint8_t)(command->address >> 8U);
        response[3] = (uint8_t)command->address;
        response[4] = (uint8_t)(command->value >> 8U);
        response[5] = (uint8_t)command->value;
        length = 6U;                   // 06成功应答回显寄存器地址和值。
    } else {
        response[1] = 0x86U;           // 功能码最高位置1，表示异常应答。
        response[2] = exception;
        length = 3U;
    }
    crc = crc_16(response, length);
    response[length] = (uint8_t)crc;
    response[length + 1U] = (uint8_t)(crc >> 8U);
    return (uint16_t)(length + 2U);
}
