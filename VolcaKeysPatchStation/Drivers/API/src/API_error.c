/*
 * API_error.c
 *
 *  Created on: 11 oct 2026
 *      Author: ianle
 */

#include "API_error.h"
#include "stm32f4xx_nucleo.h"
#include "cmsis_gcc.h"

/**
  * @brief Handler centralizado de errores para las APIs.
  *
  * Deshabilita las interrupciones globales, prende el LED2
  * de la placa y permanece en un bucle infinito.
  *
  * @retval None.
  *
  * @note La función no retorna. Se utiliza ante errores
  * irrecuperables detectados por los módulos de API.
  */
void apiErrorHandler(void) {
	BSP_LED_On(LED2);
	__disable_irq();
	while (1)  {
	}
}
