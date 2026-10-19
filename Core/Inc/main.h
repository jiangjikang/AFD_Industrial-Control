/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DN15_X0_Pin GPIO_PIN_0
#define DN15_X0_GPIO_Port GPIOA
#define DN15_X1_Pin GPIO_PIN_1
#define DN15_X1_GPIO_Port GPIOA
#define Relay_Pin GPIO_PIN_5
#define Relay_GPIO_Port GPIOA
#define Y0_BallValve_Pin GPIO_PIN_6
#define Y0_BallValve_GPIO_Port GPIOA
#define DN25_X5_Pin GPIO_PIN_11
#define DN25_X5_GPIO_Port GPIOE
#define DN20_X2_Pin GPIO_PIN_13
#define DN20_X2_GPIO_Port GPIOB
#define Y1_AirCylinder_Pin GPIO_PIN_6
#define Y1_AirCylinder_GPIO_Port GPIOC
#define Y2_AngleValve_Pin GPIO_PIN_7
#define Y2_AngleValve_GPIO_Port GPIOC
#define Y3_AngleValve_Pin GPIO_PIN_8
#define Y3_AngleValve_GPIO_Port GPIOA
#define DN20_X3_Pin GPIO_PIN_15
#define DN20_X3_GPIO_Port GPIOA
#define RS485D_Pin GPIO_PIN_4
#define RS485D_GPIO_Port GPIOD
#define Y4_BallValve_Pin GPIO_PIN_7
#define Y4_BallValve_GPIO_Port GPIOD
#define DN25_X4_Pin GPIO_PIN_3
#define DN25_X4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
