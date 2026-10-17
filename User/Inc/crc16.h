/** @file crc16.h @brief Modbus RTU CRC16接口。 */
#ifndef USER_CRC16_H
#define USER_CRC16_H
#include <stdint.h>
#include <stddef.h>
uint16_t crc_16(const uint8_t *data, uint16_t length);
int CRC16_Check(const uint8_t *frame, size_t length);
#endif
