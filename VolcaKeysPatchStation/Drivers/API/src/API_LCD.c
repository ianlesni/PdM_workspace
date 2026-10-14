/*
 * API_LCD.c
 *
 *  Created on: 20 sept 2026
 *      Author: ianle
 */
#include "API_LCD.h"
#include "API_error.h"

#define LCD_MAX_COL	20
#define LCD_MAX_ROW	4

#define DDRAM_ADDR_ROW_0	0x00
#define DDRAM_ADDR_ROW_1	0x40
#define DDRAM_ADDR_ROW_2	0x14
#define DDRAM_ADDR_ROW_3	0x54

static const uint8_t rowAddrsOffset[] = {DDRAM_ADDR_ROW_0, DDRAM_ADDR_ROW_1, DDRAM_ADDR_ROW_2, DDRAM_ADDR_ROW_3};

static void errorHandler(void);


void LCD_sendComand(uint8_t cmd) {
    uint8_t upperNibble = (cmd & 0xF0);
    uint8_t lowerNibble = ((cmd << 4) & 0xF0);

    uint8_t data[4];
    data[0] = upperNibble | 0x0C;   // EN=1, RS=0
    data[1] = upperNibble | 0x08;   // EN=0, RS=0
    data[2] = lowerNibble | 0x0C;   // EN=1, RS=0
    data[3] = lowerNibble | 0x08;   // EN=0, RS=0

    for (uint8_t dataIndex = 0; dataIndex < 4; dataIndex++) {
    	LCD_port_writeByte(data[dataIndex]);
    }
}

void LCD_sendData(uint8_t dat) {
    uint8_t upperNibble = (dat & 0xF0);
    uint8_t lowerNibble = ((dat << 4) & 0xF0);

    uint8_t data[4];
    data[0] = upperNibble | 0x0D;   // EN=1, RS=1
    data[1] = upperNibble | 0x09;   // EN=0, RS=1
    data[2] = lowerNibble | 0x0D;   // EN=1, RS=1
    data[3] = lowerNibble | 0x09;   // EN=0, RS=1

    for (uint8_t dataIndex = 0; dataIndex < 4; dataIndex++) {
    	LCD_port_writeByte(data[dataIndex]);
    }
}

void LCD_clearDisplay(void) {
	LCD_sendComand(0x01);
	LCD_port_delay(50);
}

void LCD_writeRow(uint8_t row, const char * str) {
	if (row < LCD_MAX_ROW && str != NULL) {
		LCD_setCursorPosition(row, 0x00);
		LCD_writeString(str);
	}
	else {
		errorHandler();
	}
}

void LCD_setCursorPosition(uint8_t row, uint8_t col) {
	if (row < LCD_MAX_ROW && col < LCD_MAX_COL) {
		col = col + rowAddrsOffset[row];
		LCD_sendComand(0x80 | col);
	}
	else {
		errorHandler();
	}
}

void LCD_writeString(const char * str) {
	if (str != NULL) {
		uint8_t strIndex = 0;
		while (str[strIndex] != '\0') {
			LCD_sendData(str[strIndex]);
			strIndex++;
		}
	}
	else {
		errorHandler();
	}
}

void LCD_writeCharAtPosition(uint8_t row, uint8_t col, char character) {
	if (row < LCD_MAX_ROW && col < LCD_MAX_COL) {
		LCD_setCursorPosition(row, col);
	    LCD_sendData(character);
	}
	else {
		errorHandler();
	}
}

void LCD_configureBlinkOfCursorPos(void) {
	LCD_sendComand(0x0D);
}

void LCD_init(void) {
	LCD_port_init();
	// >40 ms power on delay
	LCD_port_delay(200);
	LCD_sendComand(0x30);
	// >4,1 ms
	LCD_port_delay(5);
	LCD_sendComand(0x30);
	// > 100 us
	LCD_port_delay(1);
	LCD_sendComand(0x30);
	LCD_port_delay(10);
	// 4 bit mode
	LCD_sendComand(0x20);
	// 4 bit, 2 lineas, fuente 5x8
	LCD_sendComand(0x28);
	LCD_port_delay(1);
	// display off
	LCD_sendComand(0x08);
	LCD_port_delay(1);
	// clear display
	LCD_sendComand(0x01);
	LCD_port_delay(2);
	//entry mode: cursor increment, no shift
	LCD_sendComand(0x06);
	LCD_port_delay(1);
	// Display on, cursor of, blink off
	LCD_sendComand(0x0C);
	// clear display
	LCD_sendComand(0x01);
	LCD_port_delay(2);
}


/**
  * @brief  Esta función se ejecuta en caso de que haya un error.
  * @retval None
  */
static void errorHandler(void)
{
	apiErrorHandler();
}
