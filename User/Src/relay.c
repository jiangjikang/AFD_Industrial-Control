/*
 * relay.c
 *
 *  Created on: Oct 16, 2026
 *      Author: jiangjikang
 */

#include "relay.h"

/**
 * @brief 将0～85的流量线性映射为0～4095的DAC数值。
 * @param flow 目标流量，支持小数。
 * @return DAC数值。
 * @note 仅为开环估算，不能保证实际流量达到目标。
 */
uint16_t FlowToDac(float flow)
{
    if (!(flow > 0.0f)) return 0U;    // 零、负数或NaN返回0。
    if (flow >= 85.0f) return 4095U;  // 超出上限时限幅。

    return (uint16_t)(flow / 85.0f * 4095.0f + 0.5f);
}





