/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "tim.h"
#include "pin_configurator.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	MANUAL_CONTROL,
	READ_FROM_BITS,
} DisplayMode;

typedef enum {
	MS_DISPLAY,
	LS_DISPLAY
} ActiveDisplay;

typedef enum {
	BUTTON_IS_PRESSED,
	BUTTON_IS_RELEASED,
} ButtonPinState;

typedef struct {
	PinParams *pinParams;
	ButtonPinState isButtonPressed;
    uint32_t pressedMillis;
    uint8_t needToProcces;
} Button;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


DisplayMode displayMode;
ActiveDisplay activeDisplay = LS_DISPLAY;

PinParams* DisplayPins[] = {
	&OUTPUT_DISPLAY_A_PIN,
	&OUTPUT_DISPLAY_B_PIN,
	&OUTPUT_DISPLAY_C_PIN,
	&OUTPUT_DISPLAY_D_PIN,
	&OUTPUT_DISPLAY_E_PIN,
	&OUTPUT_DISPLAY_F_PIN,
	&OUTPUT_DISPLAY_G_PIN,
};

GPIO_PinState NumberToDisplaySegments[NUMBER_COUNT] = {
   // ABCDEFG
	0b1111110,  // 0
	0b0110000,  // 1
	0b1101101,  // 2
    0b1111001,  // 3
    0b0110011,  // 4
	0b1011011,  // 5
	0b1011111,  // 6
	0b1110000,  // 7
	0b1111111,  // 8
	0b1110011,  // 9
	0b1110111,  // A
	0b0011111,  // B
	0b1001110,  // C
	0b0111101,  // D
	0b1001111,  // E
	0b1000111   // F
};

Button buttons[] = {
	{&LS_INCREMENT_BUTTON_PIN, BUTTON_IS_RELEASED, 0, 0},
	{&LS_DECREMENT_BUTTON_PIN, BUTTON_IS_RELEASED, 0, 0},
	{&MS_INCREMENT_BUTTON_PIN, BUTTON_IS_RELEASED, 0, 0},
	{&MS_DECREMENT_BUTTON_PIN, BUTTON_IS_RELEASED, 0, 0},
};

size_t ButtonCount = sizeof(buttons) / sizeof(Button);

uint8_t lsNumber;
uint8_t msNumber;

void updateDisplayMode() {
	displayMode = (DisplayMode)HAL_GPIO_ReadPin(DISPLAY_MODE_PIN.gpio, DISPLAY_MODE_PIN.pin);
}

void updateDisplay() {
	ActiveDisplay notActiveDisplay = activeDisplay == MS_DISPLAY ? LS_DISPLAY : MS_DISPLAY;

	HAL_GPIO_WritePin(DISPLAY_SWITCH_PIN.gpio, DISPLAY_SWITCH_PIN.pin, notActiveDisplay);
	for (uint8_t i = 0; i < DISPLAY_SEGMENT_COUNT; i++) {
	    PinParams *displayPinParams = DisplayPins[i];
	    HAL_GPIO_WritePin(displayPinParams->gpio, displayPinParams->pin, GPIO_PIN_RESET);

	    if(boardMode == BIN_TO_HEX_MODE && notActiveDisplay == LS_DISPLAY && HAL_GPIO_ReadPin(LS_DISPLAY_DOT_PIN.gpio, LS_DISPLAY_DOT_PIN.pin))
			HAL_GPIO_WritePin(LS_DISPLAY_DOT_PIN.gpio, LS_DISPLAY_DOT_PIN.pin, GPIO_PIN_RESET);
	}

	HAL_GPIO_WritePin(DISPLAY_SWITCH_PIN.gpio, DISPLAY_SWITCH_PIN.pin, activeDisplay);

	if(boardMode == HEX_TO_BIN_MODE || (boardMode == BIN_TO_HEX_MODE && displayMode == READ_FROM_BITS)) {
		uint8_t number = activeDisplay == MS_DISPLAY ? msNumber : lsNumber;

		for (uint8_t i = 0; i < DISPLAY_SEGMENT_COUNT; i++) {
		    PinParams *displayPinParams = DisplayPins[i];
		    HAL_GPIO_WritePin(displayPinParams->gpio, displayPinParams->pin, NumberToDisplaySegments[number] << i & 0x40);
		}
	} else {
		if(activeDisplay == LS_DISPLAY) {
			HAL_GPIO_WritePin(LS_DISPLAY_DOT_PIN.gpio, LS_DISPLAY_DOT_PIN.pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_A_PIN.gpio, OUTPUT_DISPLAY_A_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_A_PIN.gpio, INPUT_DISPLAY_A_PIN.pin));
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_B_PIN.gpio, OUTPUT_DISPLAY_B_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_B_PIN.gpio, INPUT_DISPLAY_B_PIN.pin));
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_C_PIN.gpio, OUTPUT_DISPLAY_C_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_C_PIN.gpio, INPUT_DISPLAY_C_PIN.pin));
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_D_PIN.gpio, OUTPUT_DISPLAY_D_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_D_PIN.gpio, INPUT_DISPLAY_D_PIN.pin));
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_E_PIN.gpio, OUTPUT_DISPLAY_E_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_E_PIN.gpio, INPUT_DISPLAY_E_PIN.pin));
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_F_PIN.gpio, OUTPUT_DISPLAY_F_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_F_PIN.gpio, INPUT_DISPLAY_F_PIN.pin));
			HAL_GPIO_WritePin(OUTPUT_DISPLAY_G_PIN.gpio, OUTPUT_DISPLAY_G_PIN.pin, HAL_GPIO_ReadPin(INPUT_DISPLAY_G_PIN.gpio, INPUT_DISPLAY_G_PIN.pin));
		} else
			for (uint8_t i = 0; i < DISPLAY_SEGMENT_COUNT; i++) {
			    PinParams *displayPinParams = DisplayPins[i];
			    HAL_GPIO_WritePin(displayPinParams->gpio, displayPinParams->pin, NumberToDisplaySegments[msNumber] << i & 0x40);
			}
	}

	activeDisplay = notActiveDisplay;
}

void updateButton(Button *button) {
	if((ButtonPinState)HAL_GPIO_ReadPin(button->pinParams->gpio, button->pinParams->pin) == BUTTON_IS_PRESSED && button->isButtonPressed) {
		button->isButtonPressed = 0;
		button->needToProcces = 1;
		button->pressedMillis = HAL_GetTick();
	}

	if(!button->isButtonPressed && (HAL_GetTick() - button->pressedMillis) > BUTTON_DEBOUNCE_MILLIS)
		button->isButtonPressed = 1;
}

uint8_t getIncrementedNumber(uint8_t number) {
	return number == MAX_NUMBER ? MIN_NUMBER : number + 1;
}

uint8_t getDecrementedNumber(uint8_t number) {
	return number == MIN_NUMBER ? MAX_NUMBER : number - 1;
}

void proccesButton(PinParams *buttonPinParams) {
	if(buttonPinParams->gpio == MS_INCREMENT_BUTTON_PIN.gpio && buttonPinParams->pin == MS_INCREMENT_BUTTON_PIN.pin)
		msNumber = getIncrementedNumber(msNumber);

	if(buttonPinParams->gpio == MS_DECREMENT_BUTTON_PIN.gpio && buttonPinParams->pin == MS_DECREMENT_BUTTON_PIN.pin)
		msNumber = getDecrementedNumber(msNumber);

	if(buttonPinParams->gpio == LS_INCREMENT_BUTTON_PIN.gpio && buttonPinParams->pin == LS_INCREMENT_BUTTON_PIN.pin)
		lsNumber = getIncrementedNumber(lsNumber);

	if(buttonPinParams->gpio == LS_DECREMENT_BUTTON_PIN.gpio && buttonPinParams->pin == LS_DECREMENT_BUTTON_PIN.pin)
		lsNumber = getDecrementedNumber(lsNumber);
}

uint8_t getInvertedBit(uint8_t number, uint8_t bitPosition) {
	return ~number >> bitPosition & 1;
}

void writeBinaryRepresention() {
	HAL_GPIO_WritePin(MS_BINARY_1_PIN.gpio, MS_BINARY_1_PIN.pin, getInvertedBit(msNumber, 0));
	HAL_GPIO_WritePin(MS_BINARY_2_PIN.gpio, MS_BINARY_2_PIN.pin, getInvertedBit(msNumber, 1));
	HAL_GPIO_WritePin(MS_BINARY_4_PIN.gpio, MS_BINARY_4_PIN.pin, getInvertedBit(msNumber, 2));
	HAL_GPIO_WritePin(MS_BINARY_8_PIN.gpio, MS_BINARY_8_PIN.pin, getInvertedBit(msNumber, 3));

	HAL_GPIO_WritePin(LS_BINARY_1_PIN.gpio, LS_BINARY_1_PIN.pin, getInvertedBit(lsNumber, 0));
	HAL_GPIO_WritePin(LS_BINARY_2_PIN.gpio, LS_BINARY_2_PIN.pin, getInvertedBit(lsNumber, 1));
	HAL_GPIO_WritePin(LS_BINARY_4_PIN.gpio, LS_BINARY_4_PIN.pin, getInvertedBit(lsNumber, 2));
	HAL_GPIO_WritePin(LS_BINARY_8_PIN.gpio, LS_BINARY_8_PIN.pin, getInvertedBit(lsNumber, 3));
}

void pollAndProcessButtons() {
	for (uint8_t i = 0; i < ButtonCount; i++)
		updateButton(&buttons[i]);

	uint8_t updateBinaryRepresentation = 0;

	for (uint8_t i = 0; i < ButtonCount; i++) {
		Button *button = &buttons[i];
		if(button->needToProcces) {
			proccesButton(button->pinParams);
			button->needToProcces = 0;

			updateBinaryRepresentation = 1;
		}
	}

	if(updateBinaryRepresentation)
		writeBinaryRepresention();
}

uint8_t getNumberFromInvertedBits(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3) {
	uint8_t res = 0;

	res|= bit0;
	res|= bit1 << 1;
	res|= bit2 << 2;
	res|= bit3 << 3;

	return ~res & 0xF;
}

void readBinaryRepresention() {
	msNumber = getNumberFromInvertedBits(
		HAL_GPIO_ReadPin(MS_BINARY_1_PIN.gpio, MS_BINARY_1_PIN.pin),
		HAL_GPIO_ReadPin(MS_BINARY_2_PIN.gpio, MS_BINARY_2_PIN.pin),
		HAL_GPIO_ReadPin(MS_BINARY_4_PIN.gpio, MS_BINARY_4_PIN.pin),
		HAL_GPIO_ReadPin(MS_BINARY_8_PIN.gpio, MS_BINARY_8_PIN.pin)
	);
	lsNumber = getNumberFromInvertedBits(
		HAL_GPIO_ReadPin(LS_BINARY_1_PIN.gpio, LS_BINARY_1_PIN.pin),
		HAL_GPIO_ReadPin(LS_BINARY_2_PIN.gpio, LS_BINARY_2_PIN.pin),
		HAL_GPIO_ReadPin(LS_BINARY_4_PIN.gpio, LS_BINARY_4_PIN.pin),
		HAL_GPIO_ReadPin(LS_BINARY_8_PIN.gpio, LS_BINARY_8_PIN.pin)
	);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  initGpio();

  HAL_TIM_Base_Start_IT(&htim14);

  if(boardMode == HEX_TO_BIN_MODE)
	  writeBinaryRepresention();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(boardMode == HEX_TO_BIN_MODE)
		  pollAndProcessButtons();
	  else{
		  updateDisplayMode();
		  readBinaryRepresention();
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
