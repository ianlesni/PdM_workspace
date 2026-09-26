/*
 * API_cmdparser.c
 *
 *  Created on: 26 sept 2026
 *      Author: ianle
 */
#include "API_cmdparser.h"
#include "API_uart.h"
#include <stdbool.h>


typedef bool bool_t;


typedef enum {
	CMD_IDLE = 0,
	CMD_RECEIVING,
	CMD_ERROR,
	CMD_PROCESS,
	CMD_EXEC
}parseState_t;

char* errorMessage;

const char errorLineToLong [] = "ERROR: line too long\r\n";
const char errorUnknownCommand [] = "ERROR: unknown command\r\n";
const char errorbadArguments [] = "ERROR: bad arguments\r\n";

static parseState_t fsmState;
static void fsmInit(void);
static void goToState(parseState_t nextState);
static bool stateIn;
static bool stateOut;

void cmdParserInit(void)
{
	fsmState = CMD_IDLE;
	fsmInit();
}

void cmdPoll(void)
{
	//TODO: leer comando

	switch(fsmState)
	{
	case CMD_IDLE:
		if (stateIn)
		{
			stateIn = false;
			stateOut = false;

			// Espera el primer caracter no terminador
		}
		/********************/
		goToState(CMD_RECEIVING);
		/********************/
		if (stateOut)
		{
			stateOut = false;
			stateIn = true;
		}
		break;

	case CMD_RECEIVING:
		if (stateIn)
		{
			stateIn = false;
			stateOut = false;

			// Acumula caracateres en el buffer
		}
		/********************/
		// Recibio \r o \n
		goToState(CMD_PROCESS);
		// Condición de error
		goToState(CMD_ERROR);
		/********************/
		if (stateOut)
		{
			stateOut = false;
			stateIn = true;
		}
		break;

	case CMD_PROCESS:
		if (stateIn)
		{
			stateIn = false;
			stateOut = false;

			// Tokeniza, valida comando y argumentos
		}
		/********************/
		goToState(CMD_EXEC);
		// Condición de error
		goToState(CMD_ERROR);
		/********************/
		if (stateOut)
		{
			stateOut = false;
			stateIn = true;
		}
		break;

	case CMD_EXEC:
		if (stateIn)
		{
			stateIn = false;
			stateOut = false;

			// Ejecuta la acción y vuelve a CMD_IDLE
		}
		/********************/
		goToState(CMD_IDLE);
		/********************/
		if (stateOut)
		{
			stateOut = false;
			stateIn = true;
		}
		break;

	case CMD_ERROR:
		if (stateIn)
		{
			stateIn = false;
			stateOut = false;

			// Imprime mensaje de error y vuelve a CMD_IDLE
			uartSendString(errorMessage);
		}
		/********************/
		goToState(CMD_IDLE);
		/********************/
		if (stateOut)
		{
			stateOut = false;
			stateIn = true;
		}
		break;

	default:
		break;
	}
}


void cmdPrintHelp(void)
{
	uartSendString("\r\nComandos disponibles:\r\n");
	uartSendString("\r\nHELP:\r\n");
	uartSendString("\r\LED ON/LED OFF/LED TOGGLE:\r\n");
	uartSendString("\r\STATUS:\r\n");
	uartSendString("\r\BAUD?\r\n");
}

/**
  * @brief Inicializacion de la fsm
  *
  * @retval none
  *
  */
static void fsmInit(void)
{
	stateIn = true;
	stateOut = false;
}


/**
  * @brief Cambio de estados de la fsm
  *
  * Modifica el estado de la fsm y prepara los flags de
  * entrada y salida del estado.
  *
  * @retval none
  *
  */
static void goToState(parseState_t nextState)
{
	fsmState = nextState;
	stateIn = false;
	stateOut = true;
}
