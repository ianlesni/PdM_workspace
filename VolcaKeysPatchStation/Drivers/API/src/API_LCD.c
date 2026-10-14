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

static void LCD_sendComand(uint8_t cmd);
static void LCD_sendData(uint8_t dat);
static void errorHandler(void);



/**
  * @brief Limpia el contenido completo del display LCD.
  *
  * Envía el comando de borrado y espera el tiempo necesario
  * para que la operación finalice.
  *
  * @retval None.
  */
void LCD_clearDisplay(void) {
	LCD_sendComand(0x01);
	LCD_port_delay(50);
}


/**
  * @brief Escribe una cadena de caracteres en una fila completa del LCD.
  *
  * Posiciona el cursor al inicio de la fila indicada y escribe
  * la cadena hasta encontrar el caracter nulo.
  *
  * @param row Fila destino.
  * @param str Puntero a la cadena de caracteres a escribir.
  *
  * @retval None.
  *
  * @note Si row es inválido o str es NULL, la función
  * llama al handler de error.
  */
void LCD_writeRow(uint8_t row, const char * str) {
	if (row < LCD_MAX_ROW && str != NULL) {
		LCD_setCursorPosition(row, 0x00);
		LCD_writeString(str);
	}
	else {
		errorHandler();
	}
}

/**
  * @brief Establece la posición del cursor en el display LCD.
  *
  * Calcula la dirección DDRAM correspondiente a (fila, columna)
  * y envía el comando de set cursor.
  *
  * @param row Fila.
  * @param col Columna.
  *
  * @retval None.
  *
  * @note Si row o col son inválidos, la función
  * llama al handler de error.
  */
void LCD_setCursorPosition(uint8_t row, uint8_t col) {
	if (row < LCD_MAX_ROW && col < LCD_MAX_COL) {
		col = col + rowAddrsOffset[row];
		LCD_sendComand(0x80 | col);
	}
	else {
		errorHandler();
	}
}

/**
  * @brief Escribe una cadena de caracteres desde la posición actual.
  *
  * Escribe carácter a carácter hasta encontrar el fin de cadena.
  *
  * @param str Puntero a la cadena de caracteres a escribir.
  *
  * @retval None.
  *
  * @note Si str es NULL, la función llama al handler de error.
  */
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

/**
  * @brief Escribe un carácter en una posición específica del LCD.
  *
  * Posiciona el cursor en (row, col) y envía el carácter indicado.
  *
  * @param row Fila destino.
  * @param col Columna destino.
  * @param character Carácter a escribir.
  *
  * @retval None.
  *
  * @note Si row o col son inválidos, la función
  * llama al handler de error.
  */
void LCD_writeCharAtPosition(uint8_t row, uint8_t col, char character) {
	if (row < LCD_MAX_ROW && col < LCD_MAX_COL) {
		LCD_setCursorPosition(row, col);
	    LCD_sendData(character);
	}
	else {
		errorHandler();
	}
}


/**
  * @brief Inicialización del display LCD en modo 4 bits.
  *
  * Realiza la secuencia de inicialización por software del LCD.
  *
  * @retval None.
  */
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
  * @brief Envía un comando al controlador HD44780 en modo 4 bits.
  *
  * Genera y transmite las cuatro transiciones necesarias
  * para enviar un byte de comando.
  *
  * @param cmd Comando a enviar.
  *
  * @retval None.
  */
static void LCD_sendComand(uint8_t cmd) {
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

/**
  * @brief Envía un dato al controlador HD44780 en modo 4 bits.
  *
  * Genera y transmite las cuatro transiciones necesarias
  * para enviar un byte de dato.
  *
  * @param dat Dato a enviar.
  *
  * @retval None.
  */
static void LCD_sendData(uint8_t dat) {
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

/**
  * @brief Wrap al handler central de errores.
  *
  * @retval None.
  */
static void errorHandler(void)
{
	apiErrorHandler();
}
