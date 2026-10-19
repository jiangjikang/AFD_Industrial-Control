/*
 * valve.h
 *
 *  Created on: Oct 15, 2026
 *      Author: jiangjikang
 */

#include <stdbool.h>

#include "main.h"

#ifndef INC_VALVE_H_
#define INC_VALVE_H_

typedef struct
{
    float flow_value;
    bool valve_state;
    bool air_valve_state;
} frock_state;


// 打开或者关闭Y0标识的球阀
#define Y0BALLVALVE_OFF() \
    HAL_GPIO_WritePin(Y0_BallValve_GPIO_Port, Y0_BallValve_Pin, GPIO_PIN_RESET)

#define Y0BALLVALVE_ON() \
    HAL_GPIO_WritePin(Y0_BallValve_GPIO_Port, Y0_BallValve_Pin, GPIO_PIN_SET)

// 打开或者关闭气缸
#define AIRCYLINDER_OFF() \
    HAL_GPIO_WritePin(Y1_AirCylinder_GPIO_Port, Y1_AirCylinder_Pin, GPIO_PIN_RESET)
#define AIRCYLINDER_ON() \
    HAL_GPIO_WritePin(Y1_AirCylinder_GPIO_Port, Y1_AirCylinder_Pin, GPIO_PIN_SET)

// 打开或者关闭Y2角阀
#define Y2ANGLEVALVE_OFF() \
    HAL_GPIO_WritePin(Y2_AngleValve_GPIO_Port, Y2_AngleValve_Pin, GPIO_PIN_RESET)

#define Y2ANGLEVALVE_ON() \
    HAL_GPIO_WritePin(Y2_AngleValve_GPIO_Port, Y2_AngleValve_Pin, GPIO_PIN_SET)

// 打开或者关闭Y3角阀
#define Y3ANGLEVALVE_OFF() \
       HAL_GPIO_WritePin(Y3_AngleValve_GPIO_Port, Y3_AngleValve_Pin, GPIO_PIN_RESET)
#define Y3ANGLEVALVE_ON() \
    HAL_GPIO_WritePin(Y3_AngleValve_GPIO_Port, Y3_AngleValve_Pin, GPIO_PIN_SET)

// 打开或者关闭Y4标识的气动球阀
#define Y4BALLVALVE_OFF() \
    HAL_GPIO_WritePin(Y4_BallValve_GPIO_Port, Y4_BallValve_Pin, GPIO_PIN_RESET)

#define Y4BALLVALVE_ON() \
    HAL_GPIO_WritePin(Y4_BallValve_GPIO_Port, Y4_BallValve_Pin, GPIO_PIN_SET)

// 读取屏幕引脚变化
#define DN15_X0()           HAL_GPIO_ReadPin(DN15_X0_GPIO_Port, DN15_X0_Pin)
#define DN15_X1()           HAL_GPIO_ReadPin(DN15_X1_GPIO_Port, DN15_X1_Pin)

#define DN20_X2()           HAL_GPIO_ReadPin(DN20_X2_GPIO_Port, DN20_X2_Pin)
#define DN20_X3()           HAL_GPIO_ReadPin(DN20_X3_GPIO_Port, DN20_X3_Pin)

#define DN25_X4()           HAL_GPIO_ReadPin(DN25_X4_GPIO_Port, DN25_X4_Pin)
#define DN25_X5()           HAL_GPIO_ReadPin(DN25_X5_GPIO_Port, DN25_X5_Pin)





void open_valve(void);
void close_valve(void);
void angle_valve_blow(void);









#endif /* INC_VALVE_H_ */
