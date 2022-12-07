/*
 * UART_message_parser.h
 *
 *  Created on: Jan 24, 2022
 *      Author: jozwi
 */
/**
  ******************************************************************************
  * @file    UART_message_parser.h
  * @brief   This file contains all the function prototypes for
  *          the UART_message_parser.c file
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
#ifndef INC_UART_MESSAGE_PARSER_H_
#define INC_UART_MESSAGE_PARSER_H_

#include "flower_data.h"
#include "LCD_HD44780.h"
#include "usart.h"
#include "main.h"
#include "rtc.h"
#include <string.h>
#include <stdlib.h>


/**
 * Function parses data from UART instance and calling another function suitable for each command
 * @param struct uart_struct * Pointer to instance of UART struct
 * @return 1 if parse succeed 0 if there is no suitable command.
 *
 Available commands:

!setCurrTime 12:30:05/  |
!setWatTime 1 12:24:10/ |
!setDurTime 1 4/        |
!startWat 1/            |
!info/                  |
*/


uint8_t parseData(struct uart_struct *);

#endif /* INC_UART_MESSAGE_PARSER_H_ */
