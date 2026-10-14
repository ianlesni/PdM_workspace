/*
 * API_LCD_port.h
 *
 *  Created on: 20 sept 2026
 *      Author: ianle
 */

#ifndef INC_API_LCD_PORT_H_
#define INC_API_LCD_PORT_H_

#include <stdint.h>
#include "i2c.h"


void LCD_port_writeByte(uint8_t data);
void LCD_port_init(void);
void LCD_port_delay(uint32_t delay);


#endif /* INC_API_LCD_PORT_H_ */
