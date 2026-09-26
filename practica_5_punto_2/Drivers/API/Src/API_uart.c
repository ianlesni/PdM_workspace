/*
 * API_uart.c
 *
 *  Created on: 24 sept 2026
 *      Author: ianle
 */
#include "API_uart.h"


UART_HandleTypeDef huart2;
#define UART_TRANSMISION_TIMEOUT 200
#define UART_RESEPTION_TIMEOUT 200
#define UART_STRING_MIN_SIZE	1
#define UART_STRING_MAX_SIZE	256

static void errorHandler (void);

bool_t uartInit()
{
	  huart2.Instance = USART2;
	  huart2.Init.BaudRate = 115200;
	  huart2.Init.WordLength = UART_WORDLENGTH_8B;
	  huart2.Init.StopBits = UART_STOPBITS_1;
	  huart2.Init.Parity = UART_PARITY_NONE;
	  huart2.Init.Mode = UART_MODE_TX_RX;
	  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		return false;
	}
	uartSendString("\r\nUART Configuration:\r\n");
	uartSendString("USART2\r\n");
	uartSendString("115200\r\n");
	uartSendString("UART_WORDLENGTH_8B\r\n");
	uartSendString("UART_STOPBITS_1\r\n");
	uartSendString("UART_PARITY_NONE\r\n");
	uartSendString("UART_MODE_TX_RX\r\n");
	uartSendString("UART_HWCONTROL_NONE\r\n");
	uartSendString("UART_OVERSAMPLING_16\r\n");

	return true;

}

void uartSendString(uint8_t * pstring)
{
	if (pstring != NULL)
	{
		uint16_t stringIndex = 0;

		while (pstring[stringIndex] != '\0') {

			if (HAL_UART_Transmit(&huart2, &pstring[stringIndex], 1, UART_TRANSMISION_TIMEOUT) != HAL_OK)
			{
				break;
			}

			stringIndex++;
			if (stringIndex > UART_STRING_MAX_SIZE) {
				break;
			}
		}
	}
}

void uartSendStringSize(uint8_t * pstring, uint16_t size)
{
	if (pstring != NULL && (size >= UART_STRING_MIN_SIZE && size <= UART_STRING_MAX_SIZE)) {

		uint16_t stringIndex = 0;
		uint16_t stringSize = 0;

		while (pstring[stringIndex] != '\0') {
			stringIndex++;
			stringSize++;
		}

		if (size <= stringSize)
		{
			for (stringIndex = 0; stringIndex < size; stringIndex++)
			{
				if (HAL_UART_Transmit(&huart2, &pstring[stringIndex], 1, UART_TRANSMISION_TIMEOUT) != HAL_OK)
				{
					break;
				}
			}
		}
	}
}


void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
	HAL_UART_Receive(&huart2, pstring, size, UART_RESEPTION_TIMEOUT);
}


static void errorHandler (void)
{
	while (1)
	{
	}
}
