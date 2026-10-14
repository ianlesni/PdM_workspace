/*
 * API_midi_port.c
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */

#include "API_midi_port.h"
#include "API_error.h"

#define UART_TIMEOUT	100

UART_HandleTypeDef* midiUart;

static void errorHandler(void);

void midi_port_init(void) {
	UART_HandleTypeDef* inst;

	inst = MX_UART_GetInstance();

	if (inst != NULL) {
		midiUart = inst;
	}
	else {
		errorHandler();
	}
}

bool midi_port_send(uint8_t * data, uint8_t size) {
	if (midiUart != NULL) {
		if (data != NULL && size > 0) {
			if (HAL_UART_Transmit(midiUart, data, size, UART_TIMEOUT) != HAL_OK) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			errorHandler();
		}
	}
	else {
		errorHandler();
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
