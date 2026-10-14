/*
 * API_rotaryEncoder_port.c
 *
 *  Created on: 2 oct 2026
 *      Author: ianle
 */
#include "API_rotaryEncoder_port.h"
#include "tim.h"
#include "API_error.h"

#define BUTTON_Pin 			ROTENCBUTT_Pin
#define BUTTON_GPIO_Port 	ROTENCBUTT_GPIO_Port

static void errorHandler(void);

TIM_HandleTypeDef* timerInstance;

void rotaryEncoder_port_init(void) {
	TIM_HandleTypeDef* inst;

	inst = MX_TIM2_getInstance();

	if (inst != NULL) {
		timerInstance = inst;
	}
	else {
		errorHandler();
	}
}

uint32_t rotaryEncoder_port_getRotationCount(void) {
	if (timerInstance != NULL) {
		return __HAL_TIM_GET_COUNTER(timerInstance);
	}
	else {
		errorHandler();
	}
}

bool rotaryEncoder_port_getButtonState(void) {
	if (!HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
  * @brief  Esta función se ejecuta en caso de que haya un error.
  * @retval None
  */
static void errorHandler(void)
{
	apiErrorHandler();
}
