/*
 * API_LCD.h
 *
 *  Created on: 20 sept 2026
 *      Author: ianle
 */

#ifndef INC_API_LCD_H_
#define INC_API_LCD_H_

#include "API_LCD_port.h"

void LCD_clearDisplay(void);
void LCD_writeRow(uint8_t row, const char * str);
void LCD_setCursorPosition(uint8_t row, uint8_t col);
void LCD_writeString(const char * str);
void LCD_writeCharAtPosition(uint8_t row, uint8_t col, char character);
void LCD_init(void);

#endif /* INC_API_LCD_H_ */
