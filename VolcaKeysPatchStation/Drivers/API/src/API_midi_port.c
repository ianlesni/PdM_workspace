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


/**
  * @brief Inicialización del port para MIDI.
  *
  * Obtiene la instancia UART configurada y la almacena internamente
  * para su uso por las funciones de transmisión.
  *
  * @retval None.
  *
  * @note Si la instancia obtenida es NULL, la función
  * llama al handler de error.
  */
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

/**
  * @brief Transmisión de datos MIDI por UART.
  *
  * Transmite el buffer indicado mediante HAL_UART_Transmit
  * utilizando la instancia UART previamente inicializada.
  *
  * @param data Puntero al buffer de datos a transmitir.
  * @param size Cantidad de bytes a transmitir.
  *
  * @retval true  Transmisión exitosa.
  * @retval false Fallo en la transmisión.
  *
  * @note Si el puerto UART no fue inicializado, o si data es NULL
  * o size es 0, la función llama al handler de error.
  */
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
  * @brief Wrap al handler central de errores.
  *
  * @retval None.
  */
static void errorHandler(void)
{
	apiErrorHandler();
}
