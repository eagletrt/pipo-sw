/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

#include "usart.h"

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void) {

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, MUX_A1_Pin | STATUS_1_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, STATUS_2_Pin | STATUS_3_Pin | MUX_A0_Pin | MUX_A2_Pin | MUX_A3_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : MUX_A1_Pin STATUS_1_Pin */
    GPIO_InitStruct.Pin = MUX_A1_Pin | STATUS_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : STATUS_2_Pin STATUS_3_Pin MUX_A0_Pin MUX_A2_Pin
                           MUX_A3_Pin */
    GPIO_InitStruct.Pin = STATUS_2_Pin | STATUS_3_Pin | MUX_A0_Pin | MUX_A2_Pin | MUX_A3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 2 */

void led_write_bitmap(status_led_bitmap bitmap) {

    GPIO_TypeDef *leds_gpios[] = {
        STATUS_1_GPIO_Port,
        STATUS_2_GPIO_Port,
        STATUS_3_GPIO_Port,
    };

    uint16_t leds_pins[] = {
        STATUS_1_Pin,
        STATUS_2_Pin,
        STATUS_3_Pin,
    };

    for (size_t i = 0; i < sizeof(leds_gpios) / sizeof(GPIO_TypeDef *); i++) {
        if (((bitmap >> i) & 1) == 1) {
            HAL_GPIO_WritePin(leds_gpios[i], leds_pins[i], GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(leds_gpios[i], leds_pins[i], GPIO_PIN_RESET);
        }
    }
}

/* USER CODE END 2 */
