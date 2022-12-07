/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  *
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "flower_data.h"
#include "LCD_HD44780.h"
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;

/* USER CODE BEGIN Private defines */
/** Defines max UART buffor size
								  */
#define RECEIVE_BUFFOR_SIZE 30


/** Struct which contains data for UART instances.
								  */
//Struktura przechowująca dane dla danej instancji UART (BT, PC)
struct uart_struct {
	/** UART data buffor.
									  */
	uint8_t UART_data_buff[RECEIVE_BUFFOR_SIZE];
	/** Array which indicates current UART data index
										  */
	uint8_t receive_itter;
	/** Flag which indicates whenever the UART received first proper letter for reading command.
										  */
	uint8_t start_reading_flag;
	/** Value which stores single sign from UART Receive function
										  */
	uint8_t received_sign;

	/** Flag which indicates if data should be sent to UART.
										  */
	uint8_t sending_data_flag;
};
/* USER CODE END Private defines */

void MX_USART2_UART_Init(void);
void MX_USART4_UART_Init(void);

/* USER CODE BEGIN Prototypes */
/**  External definition of instance of UART struct (used for PC connection).
									  */
extern struct uart_struct uartBT;
/**  External definition of instance of UART struct (used for BT connection).
									  */
extern struct uart_struct uartPC;
/**  UART struct initialization (with default values).
									  */
void initUSART();
/**  Function to send data to UART instance.
									  */
void send_data_to_uart(UART_HandleTypeDef *);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

