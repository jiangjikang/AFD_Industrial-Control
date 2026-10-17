/** @file crc16.c @brief 逐位CRC16/Modbus校验。 */
#include "crc16.h"
/**
 * @brief 计算CRC16/Modbus，初值FFFF，多项式A001。
 * @param data 不含CRC的数据。
 * @param length 数据字节数；零长度时data可为空。
 * @return CRC原值，发送时低字节在前；非法空指针返回零。
 */
uint16_t crc_16(const uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFFU;
    if (data == NULL && length != 0U) { return 0U; }
    for (uint16_t i = 0U; i < length; ++i) {
        crc ^= data[i];
        for (uint8_t bit = 0U; bit < 8U; ++bit) {
            /* 最低位优先，使用反向多项式0xA001。 */
            crc = (crc & 1U) ? (uint16_t)((crc >> 1U) ^ 0xA001U) : (uint16_t)(crc >> 1U);
        }
    }
    return crc;
}
/**
 * @brief 检查完整RTU帧末尾的CRC。
 * @param frame 完整帧。
 * @param length 完整帧长度，至少4字节。
 * @return 1正确，0参数错误或校验失败。
 */
int CRC16_Check(const uint8_t *frame, size_t length)
{
    uint16_t received;
    if (frame == NULL || length < 4U || length > UINT16_MAX) { return 0; }
    /* CRC低字节在前，与寄存器的大端字节序相反。 */
    received = (uint16_t)(frame[length - 2U] | ((uint16_t)frame[length - 1U] << 8U));
    return received == crc_16(frame, (uint16_t)(length - 2U));
}
