/*
 * API_debounce.c
 *
 *  Created on: Sep 17, 2026
 *      Author: ianle
 */
#include <API_debounce.h>
#include <API_delay.h>

#define BUTTON_Pin GPIO_PIN_13
#define BUTTON_GPIO_Port GPIOC

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static const uint8_t debounceTimeout = 40;

static debounceState_t fsmState;
static void fsmInit(void);
static void goToState(debounceState_t nextState);
static bool stateIn;
static bool stateOut;


static bool_t keyPressed;
static delay_t debounceDelay;

static bool_t isButtonPressed(void);

/**
  * @brief Inicialización de la FSM de debounce
  *
  * Establece el estado inicial de la fsm y configura
  * las variables de control de estado para ingresar
  * y salir correctamente.
  *
  * @retval None.
  *
  */
void debounceFSM_init(void)
{
	fsmState = BUTTON_UP;
	keyPressed = false;
	fsmInit();
}

/**
  * @brief Maquina de estados para gestionar el debounce
  *
  * Modifica el valor del flag keyPressed aplicando el algoritmo
  * antirebote para que pueda consultarse el estado del
  * pulsador sin errores.
  *
  * @retval None.
  *
  */
void debounceFSM_update(void)
{

	switch (fsmState)
	{
		case BUTTON_UP:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				keyPressed = false;
			}
			/********************/
			if (isButtonPressed())
			{
				goToState(BUTTON_FALLING);
			}
			/********************/
			if (stateOut)
			{
				stateOut = false;
				stateIn = true;
			}
			break;

		case BUTTON_FALLING:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				delayInit(&debounceDelay, debounceTimeout);
			}
			/********************/
			if (delayRead(&debounceDelay))
			{
				if (isButtonPressed())
				{
					goToState(BUTTON_DOWN);
				}
				else
				{
					goToState(BUTTON_UP);
				}
			}
			/********************/
			if (stateOut)
			{
				stateOut = false;
				stateIn = true;
			}
			break;

		case BUTTON_DOWN:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				keyPressed = true;
			}
			/********************/
			if (!isButtonPressed())
			{
				goToState(BUTTON_RAISING);
			}
			/********************/
			if (stateOut)
			{
				stateOut = false;
				stateIn = true;
			}
			break;

		case BUTTON_RAISING:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				delayInit(&debounceDelay, debounceTimeout);
			}
			/********************/
			if (delayRead(&debounceDelay))
			{
				if (!isButtonPressed())
				{
					goToState(BUTTON_UP);
				}
				else
				{
					goToState(BUTTON_DOWN);
				}
			}
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


/**
  * @brief Lectura del flag de pulsador presionado
  *
  * Consulta si el pulsador fue presionada o no. En caso
  * de haber sido presionada, se limpia el flag keyPressed
  *
  * @retval true Fue presionado
  * @retval false No fue presionado
  *
  */
bool_t readKey(void)
{
	if (keyPressed)
	{
		keyPressed = false;
		return true;
	}
	else
	{
		return false;
	}
}


/**
  * @brief Lectura del estado del pulsador real
  *
  * Consulta el estado actual del pin asociado al pulsador
  *
  * @retval true es presionado
  * @retval false No es presionado
  *
  */
static bool_t isButtonPressed(void)
{
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
static void goToState(debounceState_t nextState)
{
	fsmState = nextState;
	stateIn = false;
	stateOut = true;
}
