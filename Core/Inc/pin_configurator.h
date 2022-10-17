#define GPIO_COUNT 5

typedef enum {
	GPIO_A_INDEX,
	GPIO_B_INDEX,
	GPIO_C_INDEX,
	GPIO_D_INDEX,
	GPIO_F_INDEX
} GpioIndex;

typedef enum {
	INPUT,
	OUTPUT
} PinMode;

typedef struct {
	 GPIO_TypeDef *gpio;
	 uint16_t pin;
	 PinMode mode;
} PinParams;

typedef enum {
	HEX_TO_BIN_MODE,
	BIN_TO_HEX_MODE,
} BoardMode;

PinParams BOARD_MODE_PIN = {GPIOB, GPIO_PIN_6, INPUT};

PinParams DISPLAY_SWITCH_PIN;
PinParams OUTPUT_DISPLAY_A_PIN;
PinParams OUTPUT_DISPLAY_B_PIN;
PinParams OUTPUT_DISPLAY_C_PIN;
PinParams OUTPUT_DISPLAY_D_PIN;
PinParams OUTPUT_DISPLAY_E_PIN;
PinParams OUTPUT_DISPLAY_F_PIN;
PinParams OUTPUT_DISPLAY_G_PIN;

PinParams MS_INCREMENT_BUTTON_PIN;
PinParams MS_DECREMENT_BUTTON_PIN;
PinParams LS_INCREMENT_BUTTON_PIN;
PinParams LS_DECREMENT_BUTTON_PIN;

PinParams MS_BINARY_1_PIN;
PinParams MS_BINARY_2_PIN;
PinParams MS_BINARY_4_PIN;
PinParams MS_BINARY_8_PIN;
PinParams LS_BINARY_1_PIN;
PinParams LS_BINARY_8_PIN;
PinParams LS_BINARY_2_PIN;
PinParams LS_BINARY_4_PIN;

PinParams DISPLAY_MODE_PIN;
PinParams INPUT_DISPLAY_A_PIN;
PinParams INPUT_DISPLAY_B_PIN;
PinParams INPUT_DISPLAY_C_PIN;
PinParams INPUT_DISPLAY_D_PIN;
PinParams INPUT_DISPLAY_E_PIN;
PinParams INPUT_DISPLAY_F_PIN;
PinParams INPUT_DISPLAY_G_PIN;
PinParams LS_DISPLAY_DOT_PIN;

BoardMode boardMode;

void initPortClocks(void) {
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
}

void initConfigurationPin(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = (uint32_t)BOARD_MODE_PIN.pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOARD_MODE_PIN.gpio, &GPIO_InitStruct);
}

void readConfigurationPin() {
	boardMode = HAL_GPIO_ReadPin(BOARD_MODE_PIN.gpio, BOARD_MODE_PIN.pin);
}

GpioIndex getIndexFromGpio(GPIO_TypeDef *gpio) {
	if(gpio == GPIOA)
		return GPIO_A_INDEX;
	if(gpio == GPIOB)
		return GPIO_B_INDEX;
	if(gpio == GPIOC)
		return GPIO_C_INDEX;
	if(gpio == GPIOD)
		return GPIO_D_INDEX;
	if(gpio == GPIOF)
		return GPIO_F_INDEX;

	return GPIO_A_INDEX;
}

GPIO_TypeDef* getGpioFromIndex(GpioIndex gpioIndex) {
	if(gpioIndex == GPIO_A_INDEX)
		return GPIOA;
	if(gpioIndex == GPIO_B_INDEX)
		return GPIOB;
	if(gpioIndex == GPIO_C_INDEX)
		return GPIOC;
	if(gpioIndex == GPIO_D_INDEX)
		return GPIOD;
	if(gpioIndex == GPIO_F_INDEX)
		return GPIOF;

	return GPIOA;
}

void initPins(PinParams pins[], uint8_t pinCount) {
	uint32_t inputPins[GPIO_COUNT] = {0, 0, 0, 0, 0};
	uint32_t outputPins[GPIO_COUNT] = {0, 0, 0, 0, 0};

	for (uint8_t i = 0; i < pinCount; ++i) {
		PinParams pin = pins[i];
		GpioIndex gpioindex = getIndexFromGpio(pin.gpio);
		if(pin.mode == INPUT)
			inputPins[gpioindex] |= pin.pin;
		 else {
			HAL_GPIO_WritePin(pin.gpio, pin.pin, GPIO_PIN_RESET);
			outputPins[gpioindex] |= pin.pin;
		 }
	}

	for (uint8_t i = 0; i < GPIO_COUNT; ++i) {
		uint32_t pins = outputPins[i];
		if(pins != 0) {
			GPIO_InitTypeDef initStruct = {0};
			initStruct.Pin = pins;
			initStruct.Mode = GPIO_MODE_OUTPUT_PP;
			initStruct.Pull = GPIO_NOPULL;
			initStruct.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(getGpioFromIndex(i), &initStruct);
		}
	}

	for (uint8_t i = 0; i < GPIO_COUNT; ++i) {
		uint32_t pins = inputPins[i];
		if(pins != 0) {
			GPIO_InitTypeDef initStruct = {0};
			initStruct.Pin = pins;
			initStruct.Mode = GPIO_MODE_INPUT;
			initStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(getGpioFromIndex(i), &initStruct);
		}
	}
}

void initPinsDependsOnBoardMode(void) {
	DISPLAY_SWITCH_PIN = (PinParams) {GPIOA, GPIO_PIN_0, OUTPUT};
	OUTPUT_DISPLAY_A_PIN = (PinParams) {GPIOA, GPIO_PIN_1, OUTPUT};
	OUTPUT_DISPLAY_B_PIN = (PinParams) {GPIOA, GPIO_PIN_2, OUTPUT};
	OUTPUT_DISPLAY_C_PIN = (PinParams) {GPIOA, GPIO_PIN_3, OUTPUT};
	OUTPUT_DISPLAY_D_PIN = (PinParams) {GPIOA, GPIO_PIN_4, OUTPUT};
	OUTPUT_DISPLAY_E_PIN = (PinParams) {GPIOA, GPIO_PIN_5, OUTPUT};
	OUTPUT_DISPLAY_F_PIN = (PinParams) {GPIOA, GPIO_PIN_6, OUTPUT};
	OUTPUT_DISPLAY_G_PIN = (PinParams) {GPIOA, GPIO_PIN_7, OUTPUT};

	MS_INCREMENT_BUTTON_PIN = (PinParams) {GPIOB, GPIO_PIN_0, INPUT};
	MS_DECREMENT_BUTTON_PIN = (PinParams) {GPIOB, GPIO_PIN_1, INPUT};
	LS_INCREMENT_BUTTON_PIN = (PinParams) {GPIOB, GPIO_PIN_2, INPUT};
	LS_DECREMENT_BUTTON_PIN = (PinParams) {GPIOB, GPIO_PIN_3, INPUT};

	DISPLAY_MODE_PIN = (PinParams) {GPIOB, GPIO_PIN_15, INPUT};
	INPUT_DISPLAY_A_PIN = (PinParams) {GPIOB, GPIO_PIN_7, INPUT};
	INPUT_DISPLAY_B_PIN = (PinParams) {GPIOB, GPIO_PIN_8, INPUT};
	INPUT_DISPLAY_C_PIN = (PinParams) {GPIOB, GPIO_PIN_9, INPUT};
	INPUT_DISPLAY_D_PIN = (PinParams) {GPIOB, GPIO_PIN_10, INPUT};
	INPUT_DISPLAY_E_PIN = (PinParams) {GPIOB, GPIO_PIN_11, INPUT};
	INPUT_DISPLAY_F_PIN = (PinParams) {GPIOB, GPIO_PIN_12, INPUT};
	INPUT_DISPLAY_G_PIN = (PinParams) {GPIOB, GPIO_PIN_13, INPUT};
	LS_DISPLAY_DOT_PIN = (PinParams) {GPIOB, GPIO_PIN_0, OUTPUT};

	if(boardMode == HEX_TO_BIN_MODE) {
		MS_BINARY_1_PIN = (PinParams) {GPIOA, GPIO_PIN_15, OUTPUT};
		MS_BINARY_2_PIN = (PinParams) {GPIOA, GPIO_PIN_11, OUTPUT};
		MS_BINARY_4_PIN = (PinParams) {GPIOB, GPIO_PIN_5, OUTPUT};
		MS_BINARY_8_PIN = (PinParams) {GPIOA, GPIO_PIN_12, OUTPUT};
		LS_BINARY_1_PIN = (PinParams) {GPIOB, GPIO_PIN_4, OUTPUT};
		LS_BINARY_2_PIN = (PinParams) {GPIOA, GPIO_PIN_9, OUTPUT};
		LS_BINARY_4_PIN = (PinParams) {GPIOA, GPIO_PIN_10, OUTPUT};
		LS_BINARY_8_PIN = (PinParams) {GPIOA, GPIO_PIN_8, OUTPUT};
	} else {
		MS_BINARY_1_PIN = (PinParams) {GPIOA, GPIO_PIN_8, INPUT};
		MS_BINARY_2_PIN = (PinParams) {GPIOA, GPIO_PIN_9, INPUT};
		MS_BINARY_4_PIN = (PinParams) {GPIOA, GPIO_PIN_10, INPUT};
		MS_BINARY_8_PIN = (PinParams) {GPIOA, GPIO_PIN_11, INPUT};
		LS_BINARY_1_PIN = (PinParams) {GPIOA, GPIO_PIN_12, INPUT};
		LS_BINARY_2_PIN = (PinParams) {GPIOB, GPIO_PIN_4, INPUT};
		LS_BINARY_4_PIN = (PinParams) {GPIOB, GPIO_PIN_5, INPUT};
		LS_BINARY_8_PIN = (PinParams) {GPIOA, GPIO_PIN_15, INPUT};
	}

	if(boardMode == HEX_TO_BIN_MODE) {
		PinParams pins[] = {
				DISPLAY_SWITCH_PIN,
				OUTPUT_DISPLAY_A_PIN,
				OUTPUT_DISPLAY_B_PIN,
				OUTPUT_DISPLAY_C_PIN,
				OUTPUT_DISPLAY_D_PIN,
				OUTPUT_DISPLAY_E_PIN,
				OUTPUT_DISPLAY_F_PIN,
				OUTPUT_DISPLAY_G_PIN,
				MS_INCREMENT_BUTTON_PIN,
				MS_DECREMENT_BUTTON_PIN,
				LS_INCREMENT_BUTTON_PIN,
				LS_DECREMENT_BUTTON_PIN,
				MS_BINARY_1_PIN,
				MS_BINARY_2_PIN,
				MS_BINARY_4_PIN,
				MS_BINARY_8_PIN,
				LS_BINARY_1_PIN,
				LS_BINARY_2_PIN,
				LS_BINARY_4_PIN,
				LS_BINARY_8_PIN
		};
		size_t pinCount = sizeof(pins) / sizeof(PinParams);
		initPins(pins, pinCount);
	} else {
		PinParams pins[] = {
				DISPLAY_SWITCH_PIN,
				OUTPUT_DISPLAY_A_PIN,
				OUTPUT_DISPLAY_B_PIN,
				OUTPUT_DISPLAY_C_PIN,
				OUTPUT_DISPLAY_D_PIN,
				OUTPUT_DISPLAY_E_PIN,
				OUTPUT_DISPLAY_F_PIN,
				OUTPUT_DISPLAY_G_PIN,
				MS_BINARY_1_PIN,
				MS_BINARY_2_PIN,
				MS_BINARY_4_PIN,
				MS_BINARY_8_PIN,
				LS_BINARY_1_PIN,
				LS_BINARY_2_PIN,
				LS_BINARY_4_PIN,
				LS_BINARY_8_PIN,
				DISPLAY_MODE_PIN,
				INPUT_DISPLAY_A_PIN,
				INPUT_DISPLAY_B_PIN,
				INPUT_DISPLAY_C_PIN,
				INPUT_DISPLAY_D_PIN,
				INPUT_DISPLAY_E_PIN,
				INPUT_DISPLAY_F_PIN,
				INPUT_DISPLAY_G_PIN,
				LS_DISPLAY_DOT_PIN,
		};
		size_t pinCount = sizeof(pins) / sizeof(PinParams);
		initPins(pins, pinCount);
	}
}

void initGpio() {
	initPortClocks();
	initConfigurationPin();
	readConfigurationPin();
	initPinsDependsOnBoardMode();
}
