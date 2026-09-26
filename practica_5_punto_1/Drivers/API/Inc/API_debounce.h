/*
 * API_debounce.h
 *
 *  Created on: Sep 17, 2026
 *      Author: ianle
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;

void debounceFSM_init(void);
void debounceFSM_update(void);
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
