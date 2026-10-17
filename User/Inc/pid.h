//
// Created by Jack on 2026/6/15.
//

#ifndef AFU1_CAIL_BOARD_PID_H
#define AFU1_CAIL_BOARD_PID_H

#include <stdint.h>

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float Sp;

    uint64_t Last_T;
    float Last_E;
    float Last_I;
    uint8_t Initialized;

    float UpperLimit;
    float LowerLimit;
    float IntegralUpperLimit;
    float IntegralLowerLimit;
} PID_TypeDef;

void PID_Init(PID_TypeDef *PID, float Kp, float Ki, float Kd);
void PID_ChangeSP(PID_TypeDef *PID, float SP);
float PID_Compute(PID_TypeDef *PID, float FB);
void PID_LimitConfig(PID_TypeDef *PID, float Upper, float Lower);
void PID_Reset(PID_TypeDef *PID);

#endif // AFU1_CAIL_BOARD_PID_H
