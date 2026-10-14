/*
 * API_midi_port.h
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */

#ifndef INC_API_MIDI_PORT_H_
#define INC_API_MIDI_PORT_H_

#include "usart.h"
#include <stdbool.h>
#include <stdint.h>

void midi_port_init(void);
bool midi_port_send(uint8_t * data, uint8_t size);

#endif /* INC_API_MIDI_PORT_H_ */
