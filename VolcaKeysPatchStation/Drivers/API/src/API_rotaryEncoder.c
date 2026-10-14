/*
 * API_rotaryEncoder.c
 *
 *  Created on: 2 oct 2026
 *      Author: ianle
 */

#include "API_rotaryEncoder.h"
#include "tim.h"
#include "API_delay.h"

/**********************************************************/
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


static bool buttonPressedEvent;
static delay_t debounceDelay;

#define ENCODER_COUNTS_PER_CLICK	4

static int32_t  rotationCount;     // clicks acumulados con signo
static uint32_t lastRawRotationCount;
static uint32_t timerPeriod;
static void updateRotationCount(void);

static void debounceFSM_init(void);
static void debounceFSM_update(void);
static bool isButtonPressed(void);



void rotaryEncoder_init(void) {
	rotaryEncoder_port_init();
	buttonPressedEvent = false;
	debounceFSM_init();
	rotationCount = 0;
	lastRawRotationCount = rotaryEncoder_port_getRotationCount();
	timerPeriod = MX_TIM2_getTimerPeriod() + 1;
}

void rotaryEncoder_handler(void) {
	updateRotationCount();
	debounceFSM_update();
}

int32_t rotaryEncoder_getRotationCount(void) {
    return rotationCount/ENCODER_COUNTS_PER_CLICK;
}

bool rotaryEncoder_buttonPressed(void) {
	bool retval;
	retval = buttonPressedEvent;
	if (buttonPressedEvent) {
		buttonPressedEvent = false;
	}
	return retval;
}

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
static void debounceFSM_init(void)
{
	fsmState = BUTTON_UP;
	buttonPressedEvent = false;
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
static void debounceFSM_update(void)
{

	switch (fsmState)
	{
		case BUTTON_UP:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				buttonPressedEvent = false;
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

				buttonPressedEvent = true;
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
  * @brief Lectura del estado del pulsador real
  *
  * Consulta el estado actual del pin asociado al pulsador
  *
  * @retval true es presionado
  * @retval false No es presionado
  *
  */
static bool isButtonPressed(void)
{
	return rotaryEncoder_port_getButtonState();
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

static void updateRotationCount(void) {
    uint32_t now = rotaryEncoder_port_getRotationCount();
    int32_t  delta = (int32_t)(now - lastRawRotationCount);

    //Corrige la vuelta del contador acotado [0, ARR]
    if (delta > (int32_t)(timerPeriod / 2)) {
    	delta = delta - (int32_t)timerPeriod;
    }
    else if (delta < -(int32_t)(timerPeriod / 2)) {
        delta = delta + (int32_t)timerPeriod;
    }

    rotationCount += delta;
    lastRawRotationCount = now;
}
