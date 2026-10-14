/*
 * API_rotaryEncoder_port.h
 *
 *  Created on: 2 oct 2026
 *      Author: ianle
 */

#ifndef INC_API_ROTARYENCODER_PORT_H_
#define INC_API_ROTARYENCODER_PORT_H_

#include "tim.h"
#include <stdint.h>
#include <stdbool.h>

void rotaryEncoder_port_init(void);
uint32_t rotaryEncoder_port_getRotationCount(void);
bool rotaryEncoder_port_getButtonState(void);

#endif /* INC_API_ROTARYENCODER_PORT_H_ */
