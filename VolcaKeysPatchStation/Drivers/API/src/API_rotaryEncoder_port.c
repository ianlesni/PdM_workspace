/*
 * API_rotaryEncoder_port.c
 *
 *  Created on: 2 oct 2026
 *      Author: ianle
 */
#include "API_rotaryEncoder_port.h"
#include "tim.h"
#include "API_error.h"

#define BUTTON_Pin 			ROTENCBUTT_Pin
#define BUTTON_GPIO_Port 	ROTENCBUTT_GPIO_Port

static void errorHandler(void);

static TIM_HandleTypeDef* timerInstance;


/**
  * @brief Inicialización del port del encoder rotativo.
  *
  * Obtiene la instancia de tiemr configurada para el encoder rotativo
  * y la almacena internamente para su posterior uso.
  *
  * @retval None.
  *
  * @note Si la instancia timer obtenida es NULL, la función
  * llama al handler de error.
  */

void rotaryEncoder_port_init(void) {
	TIM_HandleTypeDef* inst;

	inst = MX_TIM2_getInstance();

	if (inst != NULL) {
		timerInstance = inst;
	}
	else {
		errorHandler();
	}
}

/**
  * @brief Obtiene el valor actual del contador de rotación del encoder.
  *
  * Retorna el conteo actual del temporizador configurado
  * en modo encoder mediante __HAL_TIM_GET_COUNTER().
  *
  * @retval uint32_t Valor actual del contador de rotación.
  *
  * @note Si el puerto no fue inicializado correctamente,
  * la función llama al handler de error.
  */
uint32_t rotaryEncoder_port_getRotationCount(void) {
	if (timerInstance != NULL) {
		return __HAL_TIM_GET_COUNTER(timerInstance);
	}
	else {
		errorHandler();
	}
}

/**
  * @brief Obtiene el estado del pulsador del encoder rotativo.
  *
  * Lee el estado del GPIO asociado al pulsador del encoder rotativo.
  * Se considera pulsado cuando el nivel es bajo (active-low).
  *
  * @retval true  Pulsador presionado.
  * @retval false Pulsador liberado.
  */
bool rotaryEncoder_port_getButtonState(void) {
	if (!HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin))
	{
		return true;
	}
	else
	{
		return false;
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
