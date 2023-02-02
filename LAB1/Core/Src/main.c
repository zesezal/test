/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

//L1 = PC10
//L2 = PC11
//L3 = PC12
//L4 = PD2

//R1 = PC9
//R2 = PC8
//R3 = PB8
//R4 = PC6
static int keep_button[16];
static int assign_button[16];
static int state = 0;

static int current_button;
static int last_button;

//check state changing
static int error_count;
int last_state;

typedef struct test {
	char GPIO[20];
	char GPIO_PIN[20];
} Tester;


///tester Key_R1 = { GPIOC, GPIO_PIN_9 };
//tester Key_R2 = { GPIOC, GPIO_PIN_8 };
//tester Key_R3 = { GPIOB, GPIO_PIN_8 };
//tester Key_R4 = { GPIOC, GPIO_PIN_6 };
void assign(){
	for(int var = 0; var < 16; var++){
		assign_button[var] = keep_button[var];
	}
}


void set(char GPIO[], int GPIO_PIN) {
	GPIO_PinState HIGH = 1;
	HAL_GPIO_WritePin(GPIO, GPIO_PIN, HIGH);
}

void reset(char GPIO[], int GPIO_PIN) {
	GPIO_PinState LOW = 0;
	HAL_GPIO_WritePin(GPIO, GPIO_PIN, LOW);
}

void get_val(int case_num) {

	current_button = 0;

	keep_button[case_num * 4] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
	keep_button[case_num * 4 + 1] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
	keep_button[case_num * 4 + 2] = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
	keep_button[case_num * 4 + 3] = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);


	for(int var = 0;var < case_num * 4 + 4;var++){
		if(keep_button[var] == 0){
			current_button = 1;
			break;
		}
	}

}

int see_val() {
	for (int var = 0; var < 16; ++var) {
		if (assign_button[var] == 0) {
			return var+1;
		}
	}
}

void light_an_led() {
	GPIO_PinState HIGH = 1;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, HIGH);
}

void lid_an_led(){
	GPIO_PinState LOW = 0;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, LOW);
}

void check_it(){
	static int check = 0;
//	GPIO_PinState Debug = 1;
	switch (check) {
		case 0:
			last_state = 0;
			if (see_val() == 10) {
				check += 1; //6
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 10){
				check = 99;
				error_count++;
			}
			break;
		case 1:
			last_state = 1;
			if (see_val() == 2) {
				check += 1; //64
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 2){
				check = 99;
				error_count++;
			}
			break;
		case 2:
		    last_state = 2;
			if (see_val() == 11) {
				check += 1; //643
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 11){
				check = 99;
				error_count++;
			}
			break;
		case 3:
			last_state = 3;
			if (see_val() == 2) {
				check += 1; //6434
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 2){
				check = 99;
				error_count++;
			}
			break;
		case 4:
			last_state = 4;
			if (see_val() == 4) {
				check += 1; //64340
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 4){
				check = 99;
				error_count++;
			}
			break;
		case 5:
			last_state = 5;
			if (see_val() == 6) {
				check += 1; //643405
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 6){
				check = 99;
				error_count++;
			}
			break;
		case 6:
			last_state = 6;
			if (see_val() == 4) {
				check += 1; //6434050
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 4){
				check = 99;
				error_count++;
			}
			break;
		case 7:
			last_state = 7;
			if (see_val() == 4) {
				check += 1; //64340500
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 4){
				check = 99;
				error_count++;
			}
			break;
		case 8:
			last_state = 8;
			if (see_val() == 4) {
				check += 1; //643405000
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 4){
				check = 99;
				error_count++;
			}
			break;
		case 9:
			last_state = 9;
			if (see_val() == 6) {
				check += 1; //6434050005
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 6){
				check = 99;
				error_count++;
			}
			break;
		case 10:
			last_state = 10;
			if (see_val() == 6) {
				check += 1; //64340500055
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 5){
				check = 99;
				error_count++;
			}
			break;
		case 11:
			last_state = 11;
			if (see_val() == 16) {
				light_an_led();
				check = 12 ; //OK
			} else if (see_val() == 13) {
				check = 0;
			} else if (see_val() != 16){
				check = 99;
				error_count++;
			}
			break;
		case 12:
			last_state = 12;
			if (see_val() == 13){
				lid_an_led();
				check = 0;
			} else if(see_val() != 13){
				check = 99;
				error_count++;
			}
		break;
		case 99:
			if(see_val() == 14){
				error_count -= 1;
			}
			if(error_count <= 0){
				check = last_state;
			}
			else if(see_val() == 13){
				check = 0;
			}
			else if(see_val() != 14){
				error_count++;
			}
		break;
		}

//	else if (see_val() != 10){
//					check = 99;
//					error_count++;
//				}

}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		static uint32_t timestamp1 = 10;
		GPIO_PinState HIGH = 1;
		GPIO_PinState LOW = 0;

		if (timestamp1 <= HAL_GetTick()){
			timestamp1 = HAL_GetTick() + 10;



			switch(state) {
			case 0:
					//reset(tester[0], tester[2]);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, LOW);
					get_val(state);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, HIGH);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, LOW);
					state++;

					//set(tester[0], tester[2]);

			break;
			case 1:
	//				reset(tester[0], tester[3]);
					get_val(state);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, HIGH);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, LOW);
					state++;

	//				set(tester[0], tester[3]);



			break;
			case 2:
	//				reset(tester[1], tester[3]);
					get_val(state);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, HIGH);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, LOW);
					state++;

	//				set(tester[1], tester[3]);



			break;
			case 3:
	//				reset(tester[0], tester[4]);
					get_val(state);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, HIGH);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, LOW);
	//				set(tester[0], tester[4]);

					if(current_button == 1){
						assign();
					}
					if (last_button == 1 && current_button == 0){
						check_it();
					}

				last_button = current_button;
				state = 0;
				break;

			}

		}


  /* USER CODE END 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
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
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
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

  /*Configure GPIO pins : PC6 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
				/* User can add his own implementation to report the HAL error return state */
				__disable_irq();
				while (1) {

				}

  /* USER CODE END Error_Handler_Debug */
}

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
