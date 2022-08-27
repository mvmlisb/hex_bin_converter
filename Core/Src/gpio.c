/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  MX_GPIO_InitConfigurationPin();
}

/* USER CODE BEGIN 2 */
void MX_GPIO_InitConfigurationPin() {
  /* Init PIN of configuration mode */
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = CONFIGURATION_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void MX_GPIO_ReinitInBinToHexMode(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SWITCH_DISPLAY_Pin|DISPLAY_A_Pin|DISPLAY_B_Pin|DISPLAY_C_Pin
                          |DISPLAY_D_Pin|DISPLAY_E_Pin|DISPLAY_F_Pin|DISPLAY_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin PAPin PAPin PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = SWITCH_DISPLAY_Pin|DISPLAY_A_Pin|DISPLAY_B_Pin|DISPLAY_C_Pin
                          |DISPLAY_D_Pin|DISPLAY_E_Pin|DISPLAY_F_Pin|DISPLAY_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = MS_BINARY_1_Pin|MS_BINARY_2_Pin|MS_BINARY_4_Pin|MS_BINARY_8_Pin|LS_BINARY_1_Pin|LS_BINARY_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = LS_BINARY_2_Pin|LS_BINARY_4_Pin|CONFIGURATION_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void MX_GPIO_RenitInHexToBinMode(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SWITCH_DISPLAY_Pin|DISPLAY_A_Pin|DISPLAY_B_Pin|DISPLAY_C_Pin
                          |DISPLAY_D_Pin|DISPLAY_E_Pin|DISPLAY_F_Pin|DISPLAY_G_Pin
                          |MS_BINARY_1_Pin|MS_BINARY_2_Pin|MS_BINARY_4_Pin|MS_BINARY_8_Pin
                          |LS_BINARY_1_Pin|LS_BINARY_8_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LS_BINARY_2_Pin|LS_BINARY_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin
                           PAPin PAPin */
  GPIO_InitStruct.Pin = SWITCH_DISPLAY_Pin|DISPLAY_A_Pin|DISPLAY_B_Pin|DISPLAY_C_Pin
                          |DISPLAY_D_Pin|DISPLAY_E_Pin|DISPLAY_F_Pin|DISPLAY_G_Pin
                          |MS_BINARY_1_Pin|MS_BINARY_2_Pin|MS_BINARY_4_Pin|MS_BINARY_8_Pin
                          |LS_BINARY_1_Pin|LS_BINARY_8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  /*Configure GPIO pins : PBPin PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = MS_INCREMENT_BUTTON_Pin|MS_DECREMENT_BUTTON_Pin|LS_INCREMENT_BUTTON_Pin|LS_DECREMENT_BUTTON_Pin
                          |CONFIGURATION_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = LS_BINARY_2_Pin|LS_BINARY_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE END 2 */