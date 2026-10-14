/*
 * API_midi.c
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */

#include "API_midi.h"
#include "API_error.h"

#define CONTROL_CHANGE 		0xB
#define MAX_MIDI_CHANNEL	16
#define MIN_MIDI_CC_NUM		0
#define MAX_MIDI_CC_NUM		120
#define MAX_MIDI_CC_VAL		127

static void errorHandler(void);

void midi_init(void) {
	midi_port_init();
}

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
  * @brief  Esta función se ejecuta en caso de que haya un error.
  * @retval None
  */
static void errorHandler(void)
{
	apiErrorHandler();
}
