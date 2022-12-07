/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
struct uart_struct uartBT;
struct uart_struct uartPC;

/* USER CODE END 0 */

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart4;

/* USART2 init function */

void MX_USART2_UART_Init(void)
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
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
/* USART4 init function */

void MX_USART4_UART_Init(void)
{

  /* USER CODE BEGIN USART4_Init 0 */

  /* USER CODE END USART4_Init 0 */

  /* USER CODE BEGIN USART4_Init 1 */

  /* USER CODE END USART4_Init 1 */
  huart4.Instance = USART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART4_Init 2 */

  /* USER CODE END USART4_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART4)
  {
  /* USER CODE BEGIN USART4_MspInit 0 */

  /* USER CODE END USART4_MspInit 0 */
    /* USART4 clock enable */
    __HAL_RCC_USART4_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART4 GPIO Configuration
    PC10     ------> USART4_TX
    PC11     ------> USART4_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_USART4;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART4 interrupt Init */
    HAL_NVIC_SetPriority(USART4_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART4_5_IRQn);
  /* USER CODE BEGIN USART4_MspInit 1 */

  /* USER CODE END USART4_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART4)
  {
  /* USER CODE BEGIN USART4_MspDeInit 0 */

  /* USER CODE END USART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART4_CLK_DISABLE();

    /**USART4 GPIO Configuration
    PC10     ------> USART4_TX
    PC11     ------> USART4_RX
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

    /* USART4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART4_5_IRQn);
  /* USER CODE BEGIN USART4_MspDeInit 1 */

  /* USER CODE END USART4_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void initUSART(){
	uartPC.receive_itter = 0;
	uartPC.start_reading_flag = 0;
	uartPC.received_sign = 0;
	uartPC.sending_data_flag = 0;
	memset(uartPC.UART_data_buff, '\0', RECEIVE_BUFFOR_SIZE);
	uartBT.receive_itter = 0;
	uartBT.start_reading_flag = 0;
	uartBT.received_sign = 0;
	uartBT.sending_data_flag = 0;
	memset(uartBT.UART_data_buff, '\0', RECEIVE_BUFFOR_SIZE);
	HAL_UART_Receive_IT(&huart2, &uartPC.received_sign, 1);
	HAL_UART_Receive_IT(&huart4, &uartBT.received_sign, 1);
}

void receiveData(UART_HandleTypeDef *huart, struct uart_struct *uart_str) {
	if(uart_str->received_sign == (uint8_t)'!') {
		uart_str->receive_itter = 0;
		uart_str->start_reading_flag = 1;
		memset(uart_str->UART_data_buff, 0, RECEIVE_BUFFOR_SIZE);
		return;
	}
	if(uart_str->start_reading_flag) {
		if(uart_str->receive_itter < RECEIVE_BUFFOR_SIZE) { //Przepełnienie bufora
			uart_str->UART_data_buff[uart_str->receive_itter] = uart_str->received_sign;
			uart_str->receive_itter++;
			if((uart_str->received_sign==(uint8_t)'/')){
				uart_str->UART_data_buff[uart_str->receive_itter] = uart_str->received_sign;
				if(parseData(uart_str)) HAL_UART_Transmit_IT(huart, (uint8_t*)"OK\r\n", strlen("OK\r\n"));
				else HAL_UART_Transmit_IT(huart, (uint8_t*)"NOK\r\n", strlen("NOK\r\n"));

				uart_str->start_reading_flag = 0;
			}
		}
	}else memset(uart_str->UART_data_buff, 0, RECEIVE_BUFFOR_SIZE);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){

		receiveData(huart, &uartPC);
		HAL_UART_Receive_IT(huart, &(uartPC.received_sign), 1);
	} else if(huart->Instance == USART4){

		receiveData(huart, &uartBT);
		HAL_UART_Receive_IT(huart,&(uartBT.received_sign), 1);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		if(uartPC.sending_data_flag){
			send_data_to_uart(&huart2);
			uartPC.sending_data_flag = 0;
		}
	}else if(huart->Instance == USART4){
		if(uartBT.sending_data_flag){
			send_data_to_uart(&huart4);
			uartBT.sending_data_flag = 0;
		}
	}
}

void send_data_to_uart(UART_HandleTypeDef *huart){
	char sending_buff[300];
	char word_buff[120];

	memset(sending_buff, '\0', sizeof(sending_buff));

	snprintf(word_buff, sizeof(word_buff),"\r\nCurr time: %02d:%02d:%02d\n\r", disp.currentRTCTime->Hours,disp.currentRTCTime->Minutes,disp.currentRTCTime->Seconds);
	strcat(sending_buff, word_buff);

	for(uint8_t i = 0 ; i<NUMBER_OF_FLOWERS; i++){
		memset(word_buff, '\0', sizeof(word_buff));
		snprintf(word_buff, sizeof(word_buff),"\n\rFlower nr %i\r\nMoisture: %i\r\nWatering time: %02d:%02d:%02d\r\nLst watering time: %02d:%02d:%02d\r\nWatering dur: %i\r\n",
				flowers[i].flower_id,flowers[i].moisture,flowers[i].watering_time[0].Hours, flowers[i].watering_time[0].Minutes,flowers[i].watering_time[0].Seconds, flowers[i].last_watering_time.Hours,flowers[i].last_watering_time.Minutes,flowers[i].last_watering_time.Seconds,flowers[i].watering_duration);
		strcat(sending_buff,word_buff);
	}
	HAL_UART_Transmit_IT(huart, (uint8_t*)sending_buff, strlen(sending_buff));
}

/* USER CODE END 1 */
