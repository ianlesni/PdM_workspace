/*
 * API_error.c
 *
 *  Created on: 11 oct 2026
 *      Author: ianle
 */

#include "API_error.h"
#include "stm32f4xx_nucleo.h"
#include "cmsis_gcc.h"

void apiErrorHandler(void) {
	BSP_LED_On(LED2);
	__disable_irq();
	while (1)  {
	}
}
