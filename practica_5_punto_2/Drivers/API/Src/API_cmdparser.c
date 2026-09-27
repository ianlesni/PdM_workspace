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

typedef enum {
	CMD_NONE = 0,
	CMD_HELP,
	CMD_LED_ON,
	CMD_LED_OFF,
	CMD_LED_TOGGLE,
	CMD_STATUS
}commands_t;

typedef enum {
	cmdLine_unk_err = 0,
	cmdLine_arg_err,
	cmdLine_ok
}commandLineStaus_t;

static char* errorMessage;
static uint8_t cmdReceptionBuffer[CMD_MAX_LINE];
static uint8_t receptionIndex;

static char errorLineToLong [] = "\r\nERROR: line too long\r\n";
static char errorUnknownCommand [] = "\r\nERROR: unknown command\r\n";
static char errorbadArguments [] = "\r\nERROR: bad arguments\r\n";

static uint8_t * tokens[CMD_MAX_TOKENS];

static commands_t currentCmd;
static commandLineStaus_t cmdProcessLine(void);
static void cleanReceptionBuffer(void);
static bool startReceivingCondition(char caract);
static char toUpper(char caract);
static bool isCmdMatch(uint8_t * cmdReceptBuff, char * cmd);

static parseState_t fsmState;
static void fsmInit(void);
static void goToState(parseState_t nextState);
static bool stateIn;
static bool stateOut;

void cmdParserInit(void)
{
	fsmState = CMD_IDLE;
	fsmInit();
	cleanReceptionBuffer();
	receptionIndex = 0;
	currentCmd = CMD_NONE;
}

void cmdPoll(void)
{
	switch(fsmState)
	{
		case CMD_IDLE:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				// Espera el primer caracter no terminador
				cleanReceptionBuffer();
				receptionIndex = 0;
			}
			/********************/
			if (uartReceiveStringSize(cmdReceptionBuffer, 1))
			{
				if (startReceivingCondition(cmdReceptionBuffer[0]))
				{
					goToState(CMD_RECEIVING);
				}
				else
				{
					cleanReceptionBuffer();
				}
			}
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
				// Se coloca un offset para el buffer de recepción
				// porque el primer caracter se obtuvo en el estado anterior
				receptionIndex = 1;
			}
			/********************/
			if (uartReceiveStringSize(&cmdReceptionBuffer[receptionIndex], 1))
			{
				if (receptionIndex > CMD_MAX_LINE - 1)
				{
					// Error por overflow
					errorMessage = errorLineToLong;
					goToState(CMD_ERROR);
				}
				else if (cmdReceptionBuffer[receptionIndex] == '\r' || cmdReceptionBuffer[receptionIndex] == '\n' || cmdReceptionBuffer[receptionIndex] == '\0' )
				{
					// Recibio \r o \n
					goToState(CMD_PROCESS);
				}
				else
				{
					// Se pasa a mayuscula cualquier caracter alfabetico recibido, el resto
					// se almacena tal cual llegó
					cmdReceptionBuffer[receptionIndex] = toUpper(cmdReceptionBuffer[receptionIndex]);
					receptionIndex++;
				}
			}
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
			if (cmdReceptionBuffer[0] == '#' || (cmdReceptionBuffer[0] == '/' && cmdReceptionBuffer[1] == '/'))
			{
				// Ignora las lineas de comentario que comienzan con # o con //
				goToState(CMD_IDLE);
			}
			else
			{
				commandLineStaus_t cmdLineResult;
				cmdLineResult = cmdProcessLine();

				switch (cmdLineResult)
				{
					case cmdLine_ok:
						// Es un comando valido
						goToState(CMD_EXEC);
						break;
					case cmdLine_unk_err:
						// Es un comando desconocido
						errorMessage = errorUnknownCommand;
						goToState(CMD_ERROR);
						break;
					case cmdLine_arg_err:
						// Es un comando desconocido
						errorMessage = errorbadArguments;
						goToState(CMD_ERROR);
						break;
					default:
						break;
				}
			}
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
			switch (currentCmd)
			{
				case CMD_HELP:
					cmdPrintHelp();
					break;

				case CMD_LED_ON:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
					uartSendString((uint8_t *)"Turned On\r\n");
					break;

				case CMD_LED_OFF:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					uartSendString((uint8_t *)"Turned Off\r\n");
					break;

				case CMD_LED_TOGGLE:
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
					uartSendString((uint8_t *)"Toggled\r\n");
					break;

				case CMD_STATUS :
					if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET)
					{
						uartSendString((uint8_t *)"LED is ON\r\n");
					}
					else
					{
						uartSendString((uint8_t *)"LED is OFF\r\n");
					}
					break;

				default:
					break;
			}
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
				uartSendString((uint8_t *)errorMessage);
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
	uartSendString((uint8_t *)"\r\nComandos disponibles:\r\n");
	uartSendString((uint8_t *)"HELP: muestra comandos disponibles\r\n");
	uartSendString((uint8_t *)"LED ON: enciende el LED\r\n");
	uartSendString((uint8_t *)"LED OFF: apaga el LED\r\n");
	uartSendString((uint8_t *)"LED TOGGLE: invierte el estado del LED\r\n");
	uartSendString((uint8_t *)"STATUS: informa el estado del LED\r\n");
}


static commandLineStaus_t cmdProcessLine(void)
{
	uint8_t buffIndex = 0;
	// Ej:
	//"LED    ON\r\0"
	//"LED    ON\n\0"
	//"LED    ON\r\n\0"
	// Pasa a ser "LED    ON\0"

	while (cmdReceptionBuffer[buffIndex] != '\0')
	{
		if (cmdReceptionBuffer[buffIndex] == '\r' || cmdReceptionBuffer[buffIndex] == '\n')
		{
			cmdReceptionBuffer[buffIndex] = '\0';
		}
		buffIndex ++;
	}

	uint8_t tokenCounter = 0;
	buffIndex = 0;
	//"LED    ON\0"
	//"LED\0   ON\0"
	// ^       ^
	// T[0]    T[1]

	while (cmdReceptionBuffer[buffIndex] != '\0' && tokenCounter < CMD_MAX_TOKENS)
	{
		while (cmdReceptionBuffer[buffIndex] == ' ' || cmdReceptionBuffer[buffIndex] == '\t')
		{
			buffIndex ++;
		}

		if (cmdReceptionBuffer[buffIndex] == '\0')
		{
			break;
		}

		tokens[tokenCounter] = &cmdReceptionBuffer[buffIndex];
		tokenCounter ++;

		while (cmdReceptionBuffer[buffIndex] != '\0' && cmdReceptionBuffer[buffIndex] != ' ' && cmdReceptionBuffer[buffIndex] != '\t')
		{
			buffIndex ++;
		}

		if (cmdReceptionBuffer[buffIndex] != '\0')
		{
			cmdReceptionBuffer[buffIndex] = '\0';
			buffIndex ++;
		}

	}

	if (tokenCounter == 0)
	{
		return cmdLine_unk_err;
	}
	else if (tokenCounter == 1)
	{
		// Comandos de un solo token
		if (isCmdMatch(tokens[0], "HELP"))
		{
			currentCmd = CMD_HELP;
			return cmdLine_ok;
		}
		else if (isCmdMatch(tokens[0], "STATUS"))
		{
			currentCmd = CMD_STATUS;
			return cmdLine_ok;
		}
		else
		{
			// Comando desconocido
			return cmdLine_unk_err;
		}

	}
	else if (tokenCounter == 2)
	{
		//Comandos con dos tokens
		if (isCmdMatch(tokens[0], "LED"))
		{
			if (isCmdMatch(tokens[1], "ON"))
			{
				currentCmd = CMD_LED_ON;
				return cmdLine_ok;
			}
			else if (isCmdMatch(tokens[1], "OFF"))
			{
				currentCmd = CMD_LED_OFF;
				return cmdLine_ok;
			}
			else if (isCmdMatch(tokens[1], "TOGGLE"))
			{
				currentCmd = CMD_LED_TOGGLE;
				return cmdLine_ok;
			}
			else
			{
				// Error de parámetros
				return cmdLine_arg_err;
			}
		}
		else
		{
			// Comando desconocido
			return cmdLine_unk_err;
		}
	}
}

static bool isCmdMatch(uint8_t * cmdReceptBuff, char * cmd)
{
	uint8_t buffIndex = 0;

	while (cmd[buffIndex] != '\0')
	{
		if (cmdReceptBuff[buffIndex] == cmd[buffIndex])
		{
			buffIndex ++;
		}
		else
		{
			return false;
		}
	}

	return true;
}

static void cleanReceptionBuffer(void)
{
	for (uint8_t buffIndex = 0; buffIndex < CMD_MAX_LINE; buffIndex ++)
	{
		cmdReceptionBuffer[buffIndex] = 0x00;
	}
}

static bool startReceivingCondition(char caract)
{
	if (caract == '\n' || caract == '\r' || caract == '\0')
	{
		return false;
	}
	else
	{
		return true;
	}
}

static char toUpper(char caract)
{
    if (caract >= 'a' && caract <= 'z')
    {
        caract = caract - ('a' - 'A');
    }
    return caract;
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
