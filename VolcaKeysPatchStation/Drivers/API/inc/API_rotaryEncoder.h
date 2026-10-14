/*
 * API_rotaryEncoder.h
 *
 *  Created on: 2 oct 2026
 *      Author: ianle
 */

#ifndef INC_API_ROTARYENCODER_H_
#define INC_API_ROTARYENCODER_H_

#include "API_rotaryEncoder_port.h"

void rotaryEncoder_init(void);
void rotaryEncoder_handler(void);
int32_t rotaryEncoder_getRotationCount(void);
bool rotaryEncoder_buttonPressed(void);

#endif /* INC_API_ROTARYENCODER_H_ */
