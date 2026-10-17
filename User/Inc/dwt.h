//
// Created by Jack on 2026/6/23.
//

#ifndef AFU1_CAIL_BOARD_DWT_H
#define AFU1_CAIL_BOARD_DWT_H
#include <stdint.h>

void DWT_Init(void);
uint64_t DWT_GetUs(void);

#endif //AFU1_CAIL_BOARD_DWT_H