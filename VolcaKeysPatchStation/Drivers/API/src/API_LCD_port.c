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

void LCD_port_writeByte(uint8_t data) {

	if (i2cInstance != NULL) {
		HAL_I2C_Master_Transmit(i2cInstance, LCD_ADDR, &data, sizeof(data), LCD_TRANSMISION_TIMEOUT);
	}
	else {
		errorHandler();
	}
}


void LCD_port_delay(uint32_t delay) {
	if (delay != 0) {
		HAL_Delay(delay);
	}
	else {
		errorHandler();
	}

}

static void errorHandler (void) {
	apiErrorHandler();
}

