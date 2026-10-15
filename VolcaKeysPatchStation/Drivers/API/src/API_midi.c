/*
 * API_midi.c
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */

#include "API_midi.h"
#include "API_error.h"

#define CONTROL_CHANGE 		0xB		/**< Command code MIDI,nibble alto, para Control Change. */
#define MAX_MIDI_CHANNEL	16		/**< Cantidad de canales MIDI. El canal válido es 0..15. */
#define MIN_MIDI_CC_NUM		0		/**< Minimo número de controlador CC. */
#define MAX_MIDI_CC_NUM		120		/**< Máximo número de controlador CC. */
#define MAX_MIDI_CC_VAL		127		/**< Valor máximo de un dato MIDI (7 bits). */

static void errorHandler(void);

/**
  * @brief Inicialización de la API MIDI.
  *
  * Inicializa el puerto UART utilizado para la transmisión
  * de mensajes MIDI.
  *
  * @retval None.
  */
void midi_init(void) {
	midi_port_init();
}

/**
  * @brief Transmite un mensaje MIDI Control Change (CC).
  *
  * Construye y envía un mensaje MIDI de tipo Control Change
  * (Status Byte: 0xB0 | canal, Data Byte 1: número de CC,
  * Data Byte 2: valor del CC).
  *
  * @param channel Número de canal MIDI.
  * @param controllerNumber Número de controlador CC.
  * @param value Valor del controlador CC.
  *
  * @retval true  Mensaje MIDI transmitido correctamente.
  * @retval false Fallo en la transmisión del mensaje MIDI.
  *
  * @note Si algún parámetro es inválido, la función llama
  * al handler de error.
  */
bool sendControlChange (uint8_t channel, uint8_t controllerNumber, uint8_t value) {
	if (channel < MAX_MIDI_CHANNEL && (controllerNumber >= MIN_MIDI_CC_NUM && controllerNumber < MAX_MIDI_CC_NUM) && value <= MAX_MIDI_CC_VAL) {
		uint8_t data[3];
		// 1° byte de status
		// Parámetro de control en canal
		// Primer nibble es el command code 0XB
		// Segundo nibble es el canal
		data[0] = (CONTROL_CHANGE << 4) | channel;
		// 2° Byte de data
		// Número de control change
		data[1] = controllerNumber;
		// 3° Byte de data
		// Valor de control change
		data[2] = value;

		if (midi_port_send(data, sizeof(data)) == true) {
			return true;
		}
		else {
			return false;
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
