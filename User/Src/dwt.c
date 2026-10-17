//
// Created by Jack on 2026/6/23.
//

#include "dwt.h"
#include "stm32f4xx_hal.h"

static uint32_t last_cycle_count = 0;
static uint64_t cycle_count_high = 0;

/**
 * @brief 开启DWT周期计数器，并清零微秒计时的累计状态。
 * @return 无。
 * @note 在系统时钟配置完成后调用；再次调用会使时间从零重新开始。
 *       依赖本时钟的PID等模块需要同步复位，不能在计时过程中随意重置。
 */
void DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    DWT->CYCCNT = 0;
    last_cycle_count = 0;
    cycle_count_high = 0;

    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief 获取自DWT初始化以来累计的微秒时间。
 * @return 根据CPU周期计数换算的64位微秒数。
 * @note 必须先调用DWT_Init，且SystemCoreClock应正确并保持不变。
 *       函数通过比较相邻计数值扩展回绕，每次调用间隔须小于
 *       2^32/SystemCoreClock秒；只允许单一上下文串行调用。
 */
uint64_t DWT_GetUs(void)
{
    uint32_t cycle_count = DWT->CYCCNT;

    if (cycle_count < last_cycle_count)
    {
        cycle_count_high += 0x100000000ULL;
    }

    last_cycle_count = cycle_count;

    return (cycle_count_high + cycle_count) / (SystemCoreClock / 1000000U);
}
