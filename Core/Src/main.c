/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * @author Przemysław Jóźwik 300324
  * @date 30 January 2022
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
 /****************************************************************************
  *W projekcie będziemy realizować system automatycznego nawadniania roślin  *
  *doniczkowych. Do pobierania wody użyjemy pompki sterowanej przez 		 *
  *mikrokontroler, którą umieścimy w pojemniku na wodę. 				     *
  *Proces podlewania będzie cykliczny, załączany o pewnej porze, 			 *
  *ustawianej przez użytkownika. Możliwość zmiany ustawień będzie 			 *
  *zrealizowana za pomocą połączenia Bluetooth z urządzeniem 				 *
  *mobilnym lub też za pomocą wbudowanych w system przycisków. 				 *
  *Do obustronnego przesyłu informacji 										 *
  *użyjemy również interfejsu szeregowego UART. Urządzenie 					 *
  *ponadto będzie mierzyć wilgotność gleby oraz alarmować, 					 *
  *gdy braknie wody w pojemniku.											 *
  *																			 *
  *Autorzy:																	 *
  *Przemysław Jóźwik 300324													 *
  *Tomasz Petrzak 	 300344													 *
  ***************************************************************************/


/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD_HD44780.h"
#include "flower_data.h"
#include "buttons.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

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
struct lcd_display disp;
struct flower_data flowers[NUMBER_OF_FLOWERS];

RTC_TimeTypeDef Rtc_Time;
RTC_DateTypeDef Rtc_Date;
void(* buttonFun_ptr)(struct lcd_display *);

uint16_t sensor_data[2];
uint8_t watering_state = 0;
//uint8_t previous_button_state = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Received[10];
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
  flowersInit(flowers);
  flowers[0].sensor_data = &sensor_data[0];
  flowers[1].sensor_data = &sensor_data[1];
  dispInit(&disp);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_USART4_UART_Init();
  MX_TIM2_Init();
  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);
  HAL_ADC_Start_DMA(&hadc, (uint32_t *)sensor_data, 2);
  initUSART();
  __HAL_TIM_SET_COMPARE(&htim21, TIM_CHANNEL_1, 800);
  __HAL_TIM_SET_COMPARE(&htim21, TIM_CHANNEL_2, 800);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System
  */
  HAL_RCCEx_EnableLSECSS();
}

/* USER CODE BEGIN 4 */



/**
  * @brief RTC Alarm Callback (updating time and date with watering time checking every 1 s)
  * @retval None
  */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
	/** Date and time info stored in Rtc_Time and Rtc_Date global var
	  */
	HAL_RTC_GetTime(hrtc, &Rtc_Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &Rtc_Date, RTC_FORMAT_BIN);

	watering_state = 0;
	/** Checking if any of flowers watering time occured
		  */
	for(uint8_t i = 0; i<NUMBER_OF_FLOWERS; i++) {
		if((checkForWateringTime(&flowers[i], &Rtc_Time))) {
			watering_state = 1;
			changeDispState(&disp, 3);
			/** Changing the display state during watering time.
				  */
		}
	}
	if(!watering_state&&disp.disp_state==3){
		changeDispState(&disp, 0);
	}

}

/**
  * @brief Timers callback
  * @retval None
  */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	/** Timer for updating data
					  */
	if(htim->Instance == TIM6){
		updateDispData(&disp);
		HAL_TIM_Base_Start_IT(&htim7);
	}
	/** Timer for sending data to display
						  */
	if(htim->Instance == TIM7){ //Co 100us zostaje wysłana ramka do wysiwetlacza
		sendDataToDisp(&disp);
	}
	/** Timer for additional buttons functions (actually not in use)
						  */
	if(htim->Instance == TIM3){  //Na razie bezuzytczene (w zamyśle do pracy przycisków w trybie przytrzymywania)
		if(HAL_GPIO_ReadPin(LCD_Button1_GPIO_Port,LCD_Button1_Pin))
		HAL_TIM_Base_Stop_IT(&htim3);
	}
}

/**
  * @brief GPIO Callbacks
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if(GPIO_Pin == BLUE_BUTTON_Pin) {
		if(!HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO_Port, BLUE_BUTTON_Pin)) {
			BLUE_BUTTONFun();
		}
	}

	if(GPIO_Pin == LCD_Button1_Pin) {
		if(HAL_GPIO_ReadPin(LCD_Button1_GPIO_Port,LCD_Button1_Pin)) {
			LCD_Button1Fun();
		}
	}

	if(GPIO_Pin == LCD_Button2_Pin) {
		if(HAL_GPIO_ReadPin(LCD_Button2_GPIO_Port, LCD_Button2_Pin)) {
			LCD_Button2Fun();
		}
	}

}

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
  while (1)
  {
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

