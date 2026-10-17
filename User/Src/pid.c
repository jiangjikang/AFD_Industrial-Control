//
// Created by Jack on 2026/6/15.
//

#include "../Inc/pid.h"
#include "dwt.h"

#define PID_DEFAULT_LIMIT       3.4e+38f
#define PID_MIN_DELTA_TIME_S    1.0e-6f
#define PID_MAX_DELTA_TIME_S    1.0f

/**
 * @brief 将数值限制在指定上下限之间。
 * @param value 待限制的数值。
 * @param upper 上限，调用者须保证不小于lower。
 * @param lower 下限。
 * @return 限幅后的数值；范围内的数值保持不变。
 */
static float PID_Clamp(float value, float upper, float lower)
{
    if (value > upper)
    {
        return upper;
    }

    if (value < lower)
    {
        return lower;
    }

    return value;
}

/**
 * @brief 设置PID系数，清零目标与历史状态，并恢复默认限幅。
 * @param PID PID实例指针，必须有效。
 * @param Kp 比例系数。
 * @param Ki 积分系数，计算时乘以误差对时间的积分。
 * @param Kd 微分系数，计算时乘以误差变化率；为0时使用PI。
 * @return 无。
 * @note 默认输出范围接近float范围，使用前应调用PID_LimitConfig。
 *       本函数不初始化DWT，也不操作DAC或其他执行器。
 */
void PID_Init(PID_TypeDef *PID, float Kp, float Ki, float Kd)
{
    PID->Kp = Kp;
    PID->Ki = Ki;
    PID->Kd = Kd;
    PID->Sp = 0.0f;

    PID->Last_T = 0;
    PID->Last_E = 0.0f;
    PID->Last_I = 0.0f;
    PID->Initialized = 0;

    PID->UpperLimit = PID_DEFAULT_LIMIT;
    PID->LowerLimit = -PID_DEFAULT_LIMIT;
    PID->IntegralUpperLimit = PID_DEFAULT_LIMIT;
    PID->IntegralLowerLimit = -PID_DEFAULT_LIMIT;
}

/**
 * @brief 修改PID目标值，不清除已有的积分和历史误差。
 * @param PID 已初始化且有效的PID实例指针。
 * @param SP 新目标，与反馈值使用相同的物理单位。
 * @return 无。
 * @note 目标合法性和量程由调用者检查；需要清除历史状态时调用PID_Reset。
 */
void PID_ChangeSP(PID_TypeDef *PID, float SP)
{
    PID->Sp = SP;
}

/**
 * @brief 根据当前反馈执行一次位置式PID计算，并更新历史状态。
 * @param PID 已初始化且有效的PID实例指针。
 * @param FB 当前有效反馈值，单位与目标Sp一致。
 * @return 经输出限幅的控制量，单位由PID系数及应用约定决定。
 * @note 使用DWT_GetUs计算秒单位的时间间隔，梯形积分并限制积分范围。
 *       首次计算不累加积分、不计算微分；后续时间间隔限制为1us至1s。
 *       调用者须保证目标、反馈及系数为有效有限值，并串行访问实例。
 */
float PID_Compute(PID_TypeDef *PID, float FB)
{
    float now_E = PID->Sp - FB;
    uint64_t now_T = DWT_GetUs();

    if (!PID->Initialized)
    {
        PID->Last_T = now_T;
        PID->Last_E = now_E;
        PID->Initialized = 1;
        return PID_Clamp(PID->Kp * now_E + PID->Ki * PID->Last_I,
                         PID->UpperLimit,
                         PID->LowerLimit);
    }

    float deltaT = (float)(now_T - PID->Last_T) * 1.0e-6f;
    if (deltaT < PID_MIN_DELTA_TIME_S)
    {
        deltaT = PID_MIN_DELTA_TIME_S;
    }
    else if (deltaT > PID_MAX_DELTA_TIME_S)
    {
        deltaT = PID_MAX_DELTA_TIME_S;
    }

    float dev_E = (now_E - PID->Last_E) / deltaT;
    float int_E = PID->Last_I + (now_E + PID->Last_E) * deltaT * 0.5f;
    int_E = PID_Clamp(int_E, PID->IntegralUpperLimit, PID->IntegralLowerLimit);

    float CO = PID->Kp * now_E + PID->Ki * int_E + PID->Kd * dev_E;
    CO = PID_Clamp(CO, PID->UpperLimit, PID->LowerLimit);

    PID->Last_T = now_T;
    PID->Last_E = now_E;
    PID->Last_I = int_E;

    return CO;
}

/**
 * @brief 设置输出限幅，并根据当前Ki设置积分状态的限幅。
 * @param PID 已初始化且有效的PID实例指针。
 * @param Upper 输出上限。
 * @param Lower 输出下限；若大于Upper，函数自动交换上下限。
 * @return 无。
 * @note Ki大于0时，积分状态上下限为输出上下限除以Ki；
 *       Ki不大于0时使用默认积分范围。本函数仅限幅，不是条件积分抗饱和。
 *       后续修改Ki后，应重新配置限幅。
 */
void PID_LimitConfig(PID_TypeDef *PID, float Upper, float Lower)
{
    if (Upper < Lower)
    {
        float temp = Upper;
        Upper = Lower;
        Lower = temp;
    }

    PID->UpperLimit = Upper;
    PID->LowerLimit = Lower;

    if (PID->Ki > 0.0f)
    {
        PID->IntegralUpperLimit = Upper / PID->Ki;
        PID->IntegralLowerLimit = Lower / PID->Ki;
    }
    else
    {
        PID->IntegralUpperLimit = PID_DEFAULT_LIMIT;
        PID->IntegralLowerLimit = -PID_DEFAULT_LIMIT;
    }

    PID->Last_I = PID_Clamp(PID->Last_I,
                            PID->IntegralUpperLimit,
                            PID->IntegralLowerLimit);
}

/**
 * @brief 清零PID计时、误差和积分历史，使下次计算按首次调用处理。
 * @param PID 有效的PID实例指针。
 * @return 无。
 * @note 保留目标Sp、PID系数及限幅配置；不会停止设备或改变DAC输出。
 */
void PID_Reset(PID_TypeDef *PID)
{
    PID->Last_T = 0;
    PID->Last_E = 0.0f;
    PID->Last_I = 0.0f;
    PID->Initialized = 0;
}
