/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

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
void updateDisplay();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DISPLAY_SWITCH_Pin GPIO_PIN_0
#define DISPLAY_SWITCH_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_A_Pin GPIO_PIN_1
#define OUTPUT_DISPLAY_A_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_B_Pin GPIO_PIN_2
#define OUTPUT_DISPLAY_B_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_C_Pin GPIO_PIN_3
#define OUTPUT_DISPLAY_C_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_D_Pin GPIO_PIN_4
#define OUTPUT_DISPLAY_D_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_E_Pin GPIO_PIN_5
#define OUTPUT_DISPLAY_E_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_F_Pin GPIO_PIN_6
#define OUTPUT_DISPLAY_F_GPIO_Port GPIOA
#define OUTPUT_DISPLAY_G_Pin GPIO_PIN_7
#define OUTPUT_DISPLAY_G_GPIO_Port GPIOA
#define MS_INCREMENT_BUTTON_Pin GPIO_PIN_0
#define MS_INCREMENT_BUTTON_GPIO_Port GPIOB
#define MS_DECREMENT_BUTTON_Pin GPIO_PIN_1
#define MS_DECREMENT_BUTTON_GPIO_Port GPIOB
#define LS_INCREMENT_BUTTON_Pin GPIO_PIN_2
#define LS_INCREMENT_BUTTON_GPIO_Port GPIOB
#define INPUT_DISPLAY_D_Pin GPIO_PIN_10
#define INPUT_DISPLAY_D_GPIO_Port GPIOB
#define INPUT_DISPLAY_E_Pin GPIO_PIN_11
#define INPUT_DISPLAY_E_GPIO_Port GPIOB
#define INPUT_DISPLAY_F_Pin GPIO_PIN_12
#define INPUT_DISPLAY_F_GPIO_Port GPIOB
#define INPUT_DISPLAY_G_Pin GPIO_PIN_13
#define INPUT_DISPLAY_G_GPIO_Port GPIOB
#define DISPLAY_MODE_Pin GPIO_PIN_15
#define DISPLAY_MODE_GPIO_Port GPIOB
#define LS_BINARY_8_Pin GPIO_PIN_8
#define LS_BINARY_8_GPIO_Port GPIOA
#define LS_BINARY_2_Pin GPIO_PIN_9
#define LS_BINARY_2_GPIO_Port GPIOA
#define LS_BINARY_4_Pin GPIO_PIN_10
#define LS_BINARY_4_GPIO_Port GPIOA
#define MS_BINARY_2_Pin GPIO_PIN_11
#define MS_BINARY_2_GPIO_Port GPIOA
#define MS_BINARY_8_Pin GPIO_PIN_12
#define MS_BINARY_8_GPIO_Port GPIOA
#define MS_BINARY_1_Pin GPIO_PIN_15
#define MS_BINARY_1_GPIO_Port GPIOA
#define LS_DECREMENT_BUTTON_Pin GPIO_PIN_3
#define LS_DECREMENT_BUTTON_GPIO_Port GPIOB
#define LS_BINARY_1_Pin GPIO_PIN_4
#define LS_BINARY_1_GPIO_Port GPIOB
#define MS_BINARY_4_Pin GPIO_PIN_5
#define MS_BINARY_4_GPIO_Port GPIOB
#define BOARD_MODE_Pin GPIO_PIN_6
#define BOARD_MODE_GPIO_Port GPIOB
#define INPUT_DISPLAY_A_Pin GPIO_PIN_7
#define INPUT_DISPLAY_A_GPIO_Port GPIOB
#define INPUT_DISPLAY_B_Pin GPIO_PIN_8
#define INPUT_DISPLAY_B_GPIO_Port GPIOB
#define INPUT_DISPLAY_C_Pin GPIO_PIN_9
#define INPUT_DISPLAY_C_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define LS_DISPLAY_DOT_Pin MS_INCREMENT_BUTTON_Pin
#define DISPLAY_SEGMENT_COUNT 7

#define MIN_NUMBER 0
#define MAX_NUMBER 15
#define NUMBER_COUNT 16

#define BUTTON_DEBOUNCE_MILLIS 275
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
