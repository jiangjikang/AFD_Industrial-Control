/*
 * valve.h
 *
 *  Created on: Oct 15, 2026
 *      Author: jiangjikang
 */

#include "main.h"

#ifndef INC_VALVE_H_
#define INC_VALVE_H_

// 打开或者关闭Y0标识的球阀
#define Y0BALLVALVE_OFF()	HAL_GPIO_WritePin(Y0_BallValve_GPIO_Port, Y0_BallValve_Pin, GPIO_PIN_RESET);
#define Y0BALLVALVE_ON()	HAL_GPIO_WritePin(Y0_BallValve_GPIO_Port, Y0_BallValve_Pin, GPIO_PIN_SET);

// 打开或者关闭气缸
#define AIRCYLINDER_OFF()	HAL_GPIO_WritePin(Y1_AirCylinder_GPIO_Port, Y1_AirCylinder_Pin, GPIO_PIN_RESET);
#define AIRCYLINDER_ON()	HAL_GPIO_WritePin(Y1_AirCylinder_GPIO_Port, Y1_AirCylinder_Pin, GPIO_PIN_SET);

// 打开或者关闭Y2角阀
#define Y2ANGLEVALVE_OFF()	HAL_GPIO_WritePin(Y2_AngleValve_GPIO_Port, Y2_AngleValve_Pin, GPIO_PIN_RESET);
#define Y2ANGLEVALVE_ON()	HAL_GPIO_WritePin(Y2_AngleValve_GPIO_Port, Y2_AngleValve_Pin, GPIO_PIN_SET);

// 打开或者关闭Y3角阀
#define Y3ANGLEVALVE_OFF()	HAL_GPIO_WritePin(Y3_AngleValve_GPIO_Port, Y3_AngleValve_Pin, GPIO_PIN_RESET);
#define Y3ANGLEVALVE_ON()	HAL_GPIO_WritePin(Y3_AngleValve_GPIO_Port, Y3_AngleValve_Pin, GPIO_PIN_SET);

// 打开或者关闭Y4标识的气动球阀
#define Y4BALLVALVE_OFF()	HAL_GPIO_WritePin(Y4_BallValve_GPIO_Port, Y4_BallValve_Pin, GPIO_PIN_RESET);
#define Y4BALLVALVE_ON()	HAL_GPIO_WritePin(Y4_BallValve_GPIO_Port, Y4_BallValve_Pin, GPIO_PIN_SET);




void open_valve(void);
void close_valve(void);








#endif /* INC_VALVE_H_ */
