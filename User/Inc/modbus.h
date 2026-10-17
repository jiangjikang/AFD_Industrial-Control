/** @file modbus.h @brief EMF89瞬时流量读取及上位机简单命令处理。 */
#ifndef INC_MODBUS_H_
#define INC_MODBUS_H_
#include "main.h"

#define MODBUS_HOST_ADDRESS 1U       // 控制板在上位机总线上的从站地址。
#define MODBUS_FLOW_REGISTER 0x0252U // EMF89瞬时流量：手册0253减1后的实际请求地址。
#define MODBUS_TIMEOUT_MS 200U       // 一次发送或接收阶段的超时，单位ms。

typedef struct {
    uint16_t address;               // 上位机要写入的寄存器地址，具体用途由应用定义。
    uint16_t value;                 // 上位机下发的16位数值。
    uint8_t broadcast;              // 1表示广播命令，广播不能回复。
} ModbusCommand;

HAL_StatusTypeDef Modbus_ReadFlow(uint8_t meter_address, float *flow);

uint8_t Modbus_ParseCommand(const uint8_t *frame, uint16_t length,
                            ModbusCommand *command);

uint16_t Modbus_BuildReply(const ModbusCommand *command, uint8_t exception,
                           uint8_t *response);
#endif /* INC_MODBUS_H_ */
