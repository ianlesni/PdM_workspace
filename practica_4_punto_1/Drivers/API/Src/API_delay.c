/*
 * API_delay.c
 *
 *  Created on: 10 sept 2026
 *      Author: ilesnianski
 */
#include<API_delay.h>


static void delayErrorHandler(void);

/**
  * @brief Inicialización del delay no bloqueante.
  *
  * Inicializa las variables del delay y establece la duración.
  * El delay queda detenido y listo para comenzar a utilizarse
  * mediante delayRead().
  *
  * @param delay Puntero al delay que se inicializa.
  * @param duration Duración del delay en milisegundos.
  *
  * @retval None.
  *
  * @note Si el delay es NULL o la duración es nula, la función
  * llama al handler de error.
  */
void delayInit(delay_t * delay, tick_t duration)
{
	if (delay != NULL && duration > 0)
	{
		delay->running = false;
		delay->duration = duration;
		delay->startTime = 0;
	}
	else
	{
		delayErrorHandler();
	}
}

/**
  * @brief Consulta el estado del delay no bloqueante.
  *
  * En la primera llamada inicializa la temporización y en
  * las siguientes llamadas verifica si transcurrió el tiempo
  * configurado.
  *
  * Una vez que transcurrió el tiempo, detiene el delay.
  *
  * @param delay Puntero al delay cuyo estado quiere conocerse.
  * @retval true Transcurrió el tiempo configurado.
  * @retval false Continua su ejecución (o el delay es NULL).
  *
  * @note Si el delay es NULL, la función
  * no hace nada.
  */
bool_t delayRead(delay_t * delay)
{
	if (delay != NULL)
	{
		if (!delay->running)
		{
			delay->startTime = HAL_GetTick();
			delay->running = true;
			return false;
		}
		else
		{
			if ((HAL_GetTick()- delay->startTime) >= delay->duration)
			{
				delay->running = false;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		delayErrorHandler();
	}
}


/**
  * @brief Modificación de la duración del delay no bloqueante.
  *
  * Actualiza la duración configurada del delay. Si el delay
  * está corriendo, la modifiacion se aplica sobre la temporizacion actual
  * sin reiniciar el conteo.
  *
  * @param delay puntero al delay que se modifica.
  * @param duration Duración de la demora en milisegundos.
  *
  * @retval None.
  *
  * @note Si el delay es NULL o la duración es nula, la función
  * llama al handler de errores.
  */
void delayWrite(delay_t * delay, tick_t duration)
{
	if (delay != NULL && duration > 0)
	{
		delay->duration = duration;
	}
	else
	{
		delayErrorHandler();
	}
}


/**
  * @brief Consulta si el delay no bloqueante está corriendo.
  *
  * @param delay puntero al delay que se consulta.
  * @retval ture el delay está corriendo
  * @retval false el delay no está corriendo
  *
  *
  * @note Si el delay es NULL, la función
  * llama al handler de errores.
  */
bool_t delayIsRunning(delay_t * delay)
{
	if (delay != NULL)
	{
		return delay->running;
	}
	else
	{
		delayErrorHandler();
	}
}



/**
  * @brief  Esta función se ejecuta en caso de que haya un error.
  * @retval None
  */
static void delayErrorHandler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
