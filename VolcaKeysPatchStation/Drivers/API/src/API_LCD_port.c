/*
 * API_LCD_port.c
 *
 *  Created on: 20 sept 2026
 *      Author: ianle
 */
#include "API_LCD_port.h"
#include "API_error.h"

static I2C_HandleTypeDef* i2cInstance;

#define LCD_ADDR (0x27 << 1)
#define LCD_TRANSMISION_TIMEOUT 100

static void errorHandler (void);

/**
  * @brief Inicialización de port I2C para el LCD.
  *
  * Obtiene la instancia I2C configurada y la almacena internamente
  * para su uso por las funciones de escritura.
  *
  * @retval None.
  *
  * @note Si la instancia obtenida es NULL, la función
  * llama al handler de error.
  */
void LCD_port_init(void) {
	I2C_HandleTypeDef* inst;

	inst = MX_I2C1_GetInstance();

	if (inst != NULL) {
		i2cInstance = inst;
	}
	else {
		errorHandler();
	}
}


/**
  * @brief Escritura de un byte por I2C.
  *
  * Transmite un byte de datos al controlador del LCD.
  *
  * @param data Byte a transmitir.
  *
  * @retval None.
  *
  * @note Si el puerto I2C no fue inicializado, la función
  * llama al handler de error.
  */
void LCD_port_writeByte(uint8_t data) {

	if (i2cInstance != NULL) {
		HAL_I2C_Master_Transmit(i2cInstance, LCD_ADDR, &data, sizeof(data), LCD_TRANSMISION_TIMEOUT);
	}
	else {
		errorHandler();
	}
}

/**
  * @brief Retardo bloqueante utilizado por el driver de LCD.
  *
  * Ejecuta un retardo bloqueante mediante HAL_Delay() para
  * cumplir con los tiempos requeridos por el controlador LCD.
  * Se acepta el uso del retardo bloqueante para la incialización
  * dado que es un costo bajo tener el flujo bloqueado en esa instancia.
  *
  * @param delay Retardo en milisegundos.
  *
  * @retval None.
  *
  * @note Si delay es 0, la función llama al handler de error.
  */
void LCD_port_delay(uint32_t delay) {
	if (delay != 0) {
		HAL_Delay(delay);
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
static void errorHandler (void) {
	apiErrorHandler();
}

