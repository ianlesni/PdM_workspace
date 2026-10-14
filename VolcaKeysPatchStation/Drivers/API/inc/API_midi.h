/*
 * API_midi.h
 *
 *  Created on: 3 oct 2026
 *      Author: ianle
 */

#ifndef INC_API_MIDI_H_
#define INC_API_MIDI_H_

#include "API_midi_port.h"

void midi_init(void);
bool sendControlChange (uint8_t channel, uint8_t controllerNumber, uint8_t value);

#endif /* INC_API_MIDI_H_ */
