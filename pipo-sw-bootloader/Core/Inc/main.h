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
#include "stm32c0xx_hal.h"

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
#define MUX1_OUT_Pin GPIO_PIN_0
#define MUX1_OUT_GPIO_Port GPIOA
#define MUX0_OUT_Pin GPIO_PIN_1
#define MUX0_OUT_GPIO_Port GPIOA
#define SD_OUT_VSENSE_Pin GPIO_PIN_2
#define SD_OUT_VSENSE_GPIO_Port GPIOA
#define ASMS_VSENSE_Pin GPIO_PIN_3
#define ASMS_VSENSE_GPIO_Port GPIOA
#define AS_VSENSE_Pin GPIO_PIN_4
#define AS_VSENSE_GPIO_Port GPIOA
#define HP_VSENSE_Pin GPIO_PIN_5
#define HP_VSENSE_GPIO_Port GPIOA
#define RES_GO_VSENSE_Pin GPIO_PIN_6
#define RES_GO_VSENSE_GPIO_Port GPIOA
#define SD_HVD_VSENSE_Pin GPIO_PIN_7
#define SD_HVD_VSENSE_GPIO_Port GPIOA
#define SD_BSPD_VSENSE_Pin GPIO_PIN_2
#define SD_BSPD_VSENSE_GPIO_Port GPIOB
#define SD_TSMS_VSENSE_Pin GPIO_PIN_8
#define SD_TSMS_VSENSE_GPIO_Port GPIOA
#define MUX_A1_Pin GPIO_PIN_12
#define MUX_A1_GPIO_Port GPIOA
#define STATUS_1_Pin GPIO_PIN_15
#define STATUS_1_GPIO_Port GPIOA
#define STATUS_2_Pin GPIO_PIN_3
#define STATUS_2_GPIO_Port GPIOB
#define STATUS_3_Pin GPIO_PIN_4
#define STATUS_3_GPIO_Port GPIOB
#define MUX_A0_Pin GPIO_PIN_5
#define MUX_A0_GPIO_Port GPIOB
#define MUX_A2_Pin GPIO_PIN_7
#define MUX_A2_GPIO_Port GPIOB
#define MUX_A3_Pin GPIO_PIN_8
#define MUX_A3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
