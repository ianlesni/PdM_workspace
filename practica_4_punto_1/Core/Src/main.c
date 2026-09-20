/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include <API_delay.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
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


static delay_t debounceDelay;

static void debounceFSM_init(void);
static void debounceFSM_update(void);

static bool_t isButtonPressed(void);
static void buttonReleased(void);
static void buttonPressed(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  debounceFSM_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	debounceFSM_update();
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
void debounceFSM_init(void)
{
	fsmState = BUTTON_UP;
	fsmInit();
}

/**
  * @brief Maquina de estados para gestionar el debounce
  *
  * Aplica el algoritmo antirebote para
  * controlar con el pulsador de la placa el encendido del LED.
  * Se enciende al presionar y se apaga al soltar el pulsador.
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

				buttonReleased();
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

				buttonPressed();
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
  * @brief Enciende el LED
  *
  *	@retval None
  */
static void buttonPressed(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}

/**
  * @brief Apaga el LED
  *
  *	@retval None
  */
static void buttonReleased(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
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
	if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
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
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
