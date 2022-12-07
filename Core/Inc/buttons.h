/*
 * buttons.h
 *
 *  Created on: Jan 8, 2022
 *      Author: jozwi
 */
/**
  ******************************************************************************
  * @file    buttons.h
  * @brief   This file contains all the function prototypes for
  *          the buttons.c file
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
#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_


#include "main.h"
#include "LCD_HD44780.h"
#include "rtc.h"

/** Blue pin resets RTC
						  	  */
void BLUE_BUTTONFun();
/** Button 1 changes display state
 	 	 	 	 	 	 	 */
void LCD_Button1Fun();
/** Button 2 changes flower to display
							*/
void LCD_Button2Fun();

#endif /* INC_BUTTONS_H_ */
