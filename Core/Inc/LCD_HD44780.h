/*
 * LCD_HD44780.h
 *
 *  Created on: Jan 3, 2022
 *      Author: jozwi
 */
/**
  ******************************************************************************
  * @file    LCD_HD44780.h
  * @brief   This file contains all the function prototypes for
  *          the LCD_HD44780.c file
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
#ifndef LCD_HD44780_H_
#define LCD_HD44780_H_

#include "flower_data.h"
#include "main.h"
#include "tim.h"
#include "rtc.h"
#include "gpio.h"
#include "stm32l0xx_hal.h"
#include <string.h>
#include <stdio.h>

/** Defines the max rows number
			*/
#define LCD_Y 4
/** Defines the max columns number
			*/
#define LCD_X 20

/** Defines if the RW flag is used
			*/
#define USE_RW

/** Defines if the Display is in 4bit mode
			*/
#define LCD_4BIT

#ifndef LCD_4BIT
/** Defines if the Display is in 8bit mode
			*/
#define LCD_8BIT
#endif

/** Defines for LCD commands
			*/
#if ( (LCD_Y == 4) && (LCD_X == 16) )
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x28		// adres 1 znaku 2 wiersza
#define LCD_LINE3 0x14  	// adres 1 znaku 3 wiersza
#define LCD_LINE4 0x54  	// adres 1 znaku 4 wiersza
#else
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x40		// adres 1 znaku 2 wiersza
#define LCD_LINE3 0x14  	// adres 1 znaku 3 wiersza
#define LCD_LINE4 0x54  	// adres 1 znaku 4 wiersza
#endif

#define LCDC_CLS					0x01
#define LCDC_HOME					0x02
#define LCDC_ENTRY					0x04
#define LCDC_ENTRYR					0x02
#define LCDC_ENTRYL					0x00
#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
#define LCDC_DISPLAYON				0x04
#define LCDC_CURSORON				0x02
#define LCDC_CURSOROFF				0x00
#define LCDC_BLINKON				0x01
#define LCDC_SHIFT					0x10
#define LCDC_SHIFTDISP				0x08
#define LCDC_SHIFTR					0x04
#define LCDC_SHIFTL					0x00
#define LCDC_FUNC					0x20
#define LCDC_FUNC8B					0x10
#define LCDC_FUNC4B					0x00
#define LCDC_FUNC2L					0x08
#define LCDC_FUNC1L					0x00
#define LCDC_FUNC5x10				0x04
#define LCDC_FUNC5x7				0x00
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80

/*
 *
 * 	FUNCTIONS
 *
 */
/** LCD initialization.
			*/
void LCD_Init(void);
/** LCD clearance.
			*/
void LCD_Cls(void);
/** LCD setting cursor
 *  @param uint8_t x, uint8_t y Co-ordinates of the cursor to be set.
			*/
void LCD_Locate(uint8_t x, uint8_t y);
void LCD_Home();
/** LCD turning cursor off/on.
 *  @param uint8_t on_off 1 - cursor on, 0 - cursor off.
			*/
void LCD_Cursor(uint8_t on_off);
/** LCD turning blink off/on.
 *  @param uint8_t on_off 1 - blink on, 0 - blink off.
			*/
void LCD_Blink(uint8_t on_off);
/** Function to send char to LCD display.
 *  @param char c Char which will be sent
			*/
void LCD_Char(char c);
/** Function to send string to LCD display.
 *  @param char* str - String which will be sent
			*/
void LCD_String(char* str);

void LCD_Int(int value);
void LCD_Hex(int value, uint8_t upper_case);

void LCD_DefChar(uint8_t number, uint8_t *def_char);


/** LCD struct which contains display data.
			*/
struct lcd_display{
	/** Indicates which flower data has to be displayed.
				*/
	uint8_t flower_disp_state;
	/** Indicates which display state has to be displayed.
					*/
	uint8_t disp_state;
	/** Saves the previous display state.
					*/
	uint8_t previous_disp_state;
	/** Additional string to which we can upload data to be sent on display.
						*/
	char additionalDisplayData[LCD_X];
	/** Matrix of strings where each row contains particular display line data. There is LCD+1 to take into account NULL sign at the end.
						*/
	char lines[LCD_Y][LCD_X+1];

	/** Pointer to value of current RTC time.
						*/
	RTC_TimeTypeDef *currentRTCTime;
	/** Pointer to value of current RTC date.
							*/
	RTC_DateTypeDef *currentRTCDate;
	/** Tab of pointers to struct flower_data.
					*/
	struct flower_data *flowers[NUMBER_OF_FLOWERS];
	/** Pointer to function which forms relevant data to char lines[LCD_Y][LCD_X+1].
					*/
	void(* formDispData_ptr)();
};
/** External definition of struct lcd_display
				*/
extern struct lcd_display disp;

/** Function updates data to display
 * @param struct lcd_display * Pointer to display data struct.
				*/
void updateDispData(struct lcd_display *);
/** Function sends data directly to display.
 * @param struct lcd_display * Pointer to display data struct.
				*/
void sendDataToDisp(struct lcd_display *);
/** Function changes display state.
 * @param struct lcd_display *, uint8_t  state Pointer to display data struct, .
				*/
void changeDispState(struct lcd_display *, uint8_t );
/** Function forms display lines. Makes LCD to display actual time and watering times.
 * @param struct lcd_display * Pointer to display data struct.
				*/
void formDisp_TimeView(struct lcd_display *);
/** Function forms display lines. Makes LCD to display moisture of flower.
 * @param struct lcd_display * Pointer to display data struct.
				*/
void formDisp_MoistureView(struct lcd_display *);
/** Function forms display lines. Makes LCD to display the process of watering.
 * @param struct lcd_display * Pointer to display data struct.
				*/
void formDisp_WateringProcess(struct lcd_display *);
/** Function forms display lines. Makes LCD to display received data from UART.
 * @param struct lcd_display * Pointer to display data struct.
				*/
void formDisp_USART_RecieveDataView(struct lcd_display *);
/** Function cleans lines[LCD_Y][LCD_X+1].
 * @param struct lcd_display * Pointer to display data struct.
				*/
void cleanLines(struct lcd_display *);
/** Initialization of display struct.
 * @param struct lcd_display * Pointer to display data struct.
				*/
void dispInit(struct lcd_display *);
#endif /* INC_LCD_HD44780_H_ */
