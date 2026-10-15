/*
 * API_patchLoader.c
 *
 *  Created on: 2 oct 2026
 *      Author: ianle
 */

#include "API_patchManager.h"
#include "API_rotaryEncoder.h"
#include "API_LCD.h"
#include "API_midi.h"
#include "API_patchPreset.h"
#include "API_delay.h"

/*
 * Mensajes de display creados utilizando
 * https://avtanski.net/projects/lcd/
*/

/*--------------------------------------------------*/
#define MIDI_PATCH_CHANN		0x02					/**< Canal MIDI destino del Volca Keys (canal 2 contando desde 0). */
#define NULL_PREV_SCREEN_INDX	0xFF					/**< Valor por defecto inicial: fuerza la primer actualización de pantalla. */
#define NULL_PREV_ROW_INDX		NULL_PREV_SCREEN_INDX	/**< Ídem pantalla, para la fila. */

typedef enum{
	INIT = 0,
	PRESET_NAVIGATION,
	PRESET_PREVIEW,
	MIDI_SEND,
} fsm_state_t;

static fsm_state_t fsmState;
static void fsmInit(void);
static void goToState(fsm_state_t nextState);
static bool stateIn;
static bool stateOut;
static delay_t fsmDelay;
/*--------------------------------------------------*/
static uint8_t presetIndex;		/**< Preset seleccionado. */
static int32_t rotationCnt;		/**< Clicks acumulados del encoder. */
static midiPatch_t * preset;	/**< Arreglo de presets precargados. */

/** @brief Última pantalla/fila dibujada. se cachean para no redibujar de más. */
static uint8_t prevScreenIndex;
static uint8_t prevRowIndex;
static void updateScreen(uint8_t index);

#define MAX_OPTIONS		4								/**< Presets mostrados por pantalla (filas del LCD). */
#define PRESET_SCREENS ((MAX_PRESETS/MAX_OPTIONS)+1)	/**< Pantallas necesarias para mostrar todos los presets. */

/**
  * @brief Inicialización del gestor de patches.
  *
  * Inicializa la máquina de estados encargada de la navegación,
  * previsualización y envío de patches MIDI al Volca Keys.
  *
  * @retval None.
  */
void patchManager_init(void) {
	fsmInit();
	presetIndex = 0;
	prevScreenIndex = NULL_PREV_SCREEN_INDX;
	prevRowIndex = NULL_PREV_ROW_INDX;
	rotationCnt = 0;
}

/**
  * @brief Handler del gestor de patches.
  *
  * Debe ser invocado desde el bucle principal para ejecutar
  * la máquina de estados, actualizar la interfaz LCD y gestionar
  * la interacción con el encoder rotativo.
  *
  * @retval None.
  */
void patchManager_handler(void) {

	rotaryEncoder_handler();

	switch (fsmState)
	{
		case INIT:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				LCD_clearDisplay();

				patchPreset_init();

				preset = patchPreset_getPresets();

				LCD_writeRow(0,"     Volca keys");
				LCD_writeRow(1,"       Patch");
				LCD_writeRow(2,"      Station");
				LCD_writeRow(3,"       v.0.1");

				delayInit(&fsmDelay, 2000);
			}
			/********************/
			if (delayRead(&fsmDelay)) {
				goToState(PRESET_NAVIGATION);
			}
			/********************/
			if (stateOut)
			{
				stateOut = false;
				stateIn = true;
			}
			break;

		case PRESET_NAVIGATION:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				LCD_clearDisplay();

				presetIndex = 0;
				prevScreenIndex = NULL_PREV_SCREEN_INDX;
				prevRowIndex = NULL_PREV_ROW_INDX;
			}
			/********************/
			rotationCnt = rotaryEncoder_getRotationCount();
			presetIndex = (uint8_t)(((rotationCnt % MAX_PRESETS) + MAX_PRESETS) % MAX_PRESETS);
			updateScreen(presetIndex % MAX_PRESETS);
			if (rotaryEncoder_buttonPressed()) {
				goToState(PRESET_PREVIEW);
			}
			/********************/
			if (stateOut)
			{
				stateOut = false;
				stateIn = true;
			}
			break;

		case PRESET_PREVIEW:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				LCD_clearDisplay();

				LCD_writeRow(0,"Enviando Patch:");
				LCD_writeRow(2, preset[presetIndex % MAX_PRESETS].name);
				delayInit(&fsmDelay, 50);

			}
			/********************/
			if (delayRead(&fsmDelay)) {
				goToState(MIDI_SEND);
			}
			/********************/
			if (stateOut)
			{
				stateOut = false;
				stateIn = true;
			}
			break;

		case MIDI_SEND:
			if (stateIn)
			{
				stateIn = false;
				stateOut = false;

				for (uint8_t paramIndex = 0; paramIndex < MAX_PARAMENTERS; paramIndex++ ) {

					uint8_t ctrlNum = preset[presetIndex % MAX_PRESETS].param[paramIndex].ctrlNum;
					uint8_t value = preset[presetIndex % MAX_PRESETS].param[paramIndex].value;

					if (sendControlChange(MIDI_PATCH_CHANN, ctrlNum, value) != true) {

						LCD_clearDisplay();

						LCD_writeRow(0,"!!!!!!!!!!!!!!!!!!!!");
						LCD_writeRow(1,"       ERROR");
						LCD_writeRow(2,"     ENVIO MIDI");
						LCD_writeRow(3,"!!!!!!!!!!!!!!!!!!!!");
						break;
					}
				}
				delayInit(&fsmDelay, 1500);
			}
			/********************/
			if (delayRead(&fsmDelay)) {
				goToState(PRESET_NAVIGATION);
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
  * @brief Actualiza la pantalla de navegación de presets.
  *
  * Muestra el listado de presets correspondiente a la pantalla
  * actual y marca con '>' el preset seleccionado.
  *
  * @param index Índice absoluto del preset seleccionado.
  *
  * @retval None.
  */
static void updateScreen(uint8_t index) {
	uint8_t newScreen;
	uint8_t optionRow;

	newScreen = index / MAX_OPTIONS;
	optionRow = index % MAX_OPTIONS;

	if (prevRowIndex != optionRow) {
		for (uint8_t rowIndex = 0; rowIndex < MAX_OPTIONS; rowIndex++) {
			// Borra el señalador anterior
			LCD_writeCharAtPosition(rowIndex, 2, ' ');
		}
		LCD_writeCharAtPosition(optionRow, 2, '>');
		LCD_setCursorPosition(optionRow, 0);

		prevRowIndex = optionRow;
	}

	if (newScreen != prevScreenIndex) {
		// Limpia la pantalla anterior
		for (uint8_t rowIndex = 0; rowIndex < MAX_OPTIONS; rowIndex++) {
			uint8_t prsetIndex;
			prsetIndex = rowIndex + newScreen*MAX_OPTIONS;
			LCD_setCursorPosition(rowIndex, 3);
			LCD_writeString("                 ");

			if (prsetIndex < MAX_PRESETS) {
				LCD_writeCharAtPosition(rowIndex, 0, (prsetIndex/10) + '0');
				LCD_writeCharAtPosition(rowIndex, 1, (prsetIndex%10) + '0');
				LCD_setCursorPosition(rowIndex, 3);
				LCD_writeString(preset[prsetIndex].name);
			}
			else {
				LCD_setCursorPosition(rowIndex, 0);
				LCD_writeString("                    ");
			}
		}
		prevScreenIndex = newScreen;
	}

}

/**
  * @brief Inicialización de la máquina de estados.
  *
  * @retval None.
  */
static void fsmInit(void)
{
	stateIn = true;
	stateOut = false;
}

/**
  * @brief Transición hacia un nuevo estado de la MEF.
  *
  * @param nextState Estado destino.
  *
  * @retval None.
  */
static void goToState(fsm_state_t nextState)
{
	fsmState = nextState;
	stateIn = false;
	stateOut = true;
}
