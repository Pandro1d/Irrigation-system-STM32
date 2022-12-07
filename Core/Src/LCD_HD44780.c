/*
 * LCD_HD44780.c
 *
 *  Created on: Jan 3, 2022
 *      Author: jozwi
 */

/**
  ******************************************************************************
  * @file    LCD_HD44780.c
  * @brief   This file provides code for the configuration
  *          of the LCD HD44780 display.
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
#include "LCD_HD44780.h"


#define SET_LCD_E HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET)
#define RESET_LCD_E HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET)

#define SET_LCD_RS HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET)
#define RESET_LCD_RS HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET)

#ifdef USE_RW
#define SET_LCD_RW HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_SET)
#define RESET_LCD_RW HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, GPIO_PIN_RESET)
#endif

/*
 *
 * 	INSIDE FUNCTIONS
 *
 */

//
//	Set data port
//
static inline void LCD_SetDataPort(uint8_t data)
{

#ifdef LCD_4BIT
	if(data & (1<<0))
		HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_RESET);

	if(data & (1<<1))
		HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_RESET);

	if(data & (1<<2))
		HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_RESET);

	if(data & (1<<3))
		HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_RESET);
#else
	if(data & (1<<0))
		HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, GPIO_PIN_RESET);

	if(data & (1<<1))
		HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, GPIO_PIN_RESET);

	if(data & (1<<2))
		HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, GPIO_PIN_RESET);

	if(data & (1<<3))
		HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, GPIO_PIN_RESET);

	if(data & (1<<4))
		HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_RESET);

	if(data & (1<<5))
		HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_RESET);

	if(data & (1<<6))
		HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_RESET);

	if(data & (1<<7))
		HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_RESET);
#endif
}

#ifdef USE_RW
static inline uint8_t LCD_GetDataPort()
{
	uint8_t result = 0;

#ifdef LCD_4BIT

	if(HAL_GPIO_ReadPin(LCD_D4_GPIO_Port, LCD_D4_Pin) == GPIO_PIN_SET) result |= (1<<0);
	if(HAL_GPIO_ReadPin(LCD_D5_GPIO_Port, LCD_D5_Pin) == GPIO_PIN_SET) result |= (1<<1);
	if(HAL_GPIO_ReadPin(LCD_D6_GPIO_Port, LCD_D6_Pin) == GPIO_PIN_SET) result |= (1<<2);
	if(HAL_GPIO_ReadPin(LCD_D7_GPIO_Port, LCD_D7_Pin) == GPIO_PIN_SET) result |= (1<<3);
#else
	if(HAL_GPIO_ReadPin(LCD_DB0_GPIO_Port, LCD_D0_Pin) == GPIO_PIN_SET) result |= (1<<0);
	if(HAL_GPIO_ReadPin(LCD_DB1_GPIO_Port, LCD_D1_Pin) == GPIO_PIN_SET) result |= (1<<1);
	if(HAL_GPIO_ReadPin(LCD_DB2_GPIO_Port, LCD_D2_Pin) == GPIO_PIN_SET) result |= (1<<2);
	if(HAL_GPIO_ReadPin(LCD_DB3_GPIO_Port, LCD_D3_Pin) == GPIO_PIN_SET) result |= (1<<3);
	if(HAL_GPIO_ReadPin(LCD_DB4_GPIO_Port, LCD_D4_Pin) == GPIO_PIN_SET) result |= (1<<4);
	if(HAL_GPIO_ReadPin(LCD_DB5_GPIO_Port, LCD_D5_Pin) == GPIO_PIN_SET) result |= (1<<5);
	if(HAL_GPIO_ReadPin(LCD_DB6_GPIO_Port, LCD_D6_Pin) == GPIO_PIN_SET) result |= (1<<6);
	if(HAL_GPIO_ReadPin(LCD_DB7_GPIO_Port, LCD_D7_Pin) == GPIO_PIN_SET) result |= (1<<7);
#endif

return result;
}
#endif

static void LCD_DataOut()
{
	  GPIO_InitTypeDef GPIO_InitStruct;
#ifdef LCD_4BIT
	  GPIO_InitStruct.Pin = LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
#else
	  GPIO_InitStruct.Pin = LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB3_Pin
	                          |LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin|LCD_DB7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
#endif
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

#ifdef USE_RW
static void LCD_DataIn()
{
	 GPIO_InitTypeDef GPIO_InitStruct;
#ifdef LCD_4BIT
	 GPIO_InitStruct.Pin = LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin;
	 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
#else
	 GPIO_InitStruct.Pin = LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB3_Pin
	 	                          |LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin|LCD_DB7_Pin;
	 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
#endif
	 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//
//	Write byte to LCD
//
uint8_t LCD_ReadByte(void)
{
	uint8_t result = 0;
	LCD_DataIn();

	SET_LCD_RW;
#ifdef LCD_4BIT
	SET_LCD_E;
	result = (LCD_GetDataPort() << 4);
	RESET_LCD_E;

	SET_LCD_E;
	result |= LCD_GetDataPort();
	RESET_LCD_E;
#else
	SET_LCD_E;
	result = LCD_GetDataPort();
	RESET_LCD_E;
#endif
	return result;
}

//
//	Check Busy Flag
//
uint8_t LCD_CheckBusyFlag()
{
	RESET_LCD_RS;
	return LCD_ReadByte();
}
#endif

//
//	Write byte to LCD
//
void LCD_WriteByte(uint8_t data)
{
#ifdef USE_RW // There is no need to change GPIO direction if RW is not used
	LCD_DataOut();

	RESET_LCD_RW;
#endif

#ifdef LCD_4BIT
	SET_LCD_E;
	LCD_SetDataPort(data >> 4);
	RESET_LCD_E;
#endif
	SET_LCD_E;
	LCD_SetDataPort(data);
	RESET_LCD_E;


#ifdef USE_RW
	//while((LCD_CheckBusyFlag() & (1<<7))); // Wait for data processing -
#else
	//HAL_Delay(1);
#endif
}

//
//	Write command to LCD
//
void LCD_WriteCmd(uint8_t cmd)
{
	RESET_LCD_RS;
	LCD_WriteByte(cmd);
#ifndef USE_RW
	//HAL_Delay(1); //<<--- wait for command processing
#endif
}

//
//	Write data to LCD
//
void LCD_WriteData(uint8_t data)
{
	SET_LCD_RS;
	LCD_WriteByte(data);
}

/*
 *
 * 	USER FUNCTIONS
 *
 */

//
//	Write one character to LCD
//
void LCD_Char(char c)
{
	LCD_WriteData(((c >= 0x80) && (c <= 0x87)) ? (c & 0x07) : c);
}

//
//	Write string to LCD
//
void LCD_String(char* str)
{
	char c;
	while((c = *(str++)))
		LCD_Char(c);
}

//
// Print integer on LCD
//
void LCD_Int(int value)
{
	char buf[LCD_X+1];
	snprintf(buf,sizeof(int), "%d", value);
	LCD_String(buf);
}

//
// Print hexadecimal on LCD
//
void LCD_Hex(int value, uint8_t upper_case)
{
	char buf[LCD_X+1];
	if(upper_case)
		snprintf(buf,sizeof(unsigned), "%X", (unsigned int)value);
	else
		snprintf(buf,sizeof(unsigned), "%x", (unsigned int)value);
	LCD_String(buf);
}

//
// Define custom char in LCD CGRAM in 'number' slot
//
void LCD_DefChar(uint8_t number, uint8_t *def_char)
{
	uint8_t i, c;
	LCD_WriteCmd(64+((number&0x7)*8));
	for(i = 0; i < 8; i++)
	{
		c = *(def_char++);
		LCD_WriteData(c);
	}
}

//
// Back to home position
//
void LCD_Home()
{
	LCD_WriteCmd(LCDC_CLS|LCDC_HOME);
}

//
// Control cursor visibility
//
void LCD_Cursor(uint8_t on_off)
{
	if(on_off == 0)
		LCD_WriteCmd(LCDC_ONOFF|LCDC_DISPLAYON);
	else
		LCD_WriteCmd(LCDC_ONOFF|LCDC_DISPLAYON|LCDC_CURSORON);
}

//
// Control cursor blinking
//
void LCD_Blink(uint8_t on_off)
{
	if(on_off == 0)
		LCD_WriteCmd(LCDC_ONOFF|LCDC_DISPLAYON);
	else
		LCD_WriteCmd(LCDC_ONOFF|LCDC_DISPLAYON|LCDC_CURSORON|LCDC_BLINKON);
}

//
// Set cursor for x-column, y-row
//
void LCD_Locate(uint8_t x, uint8_t y)
{
	switch(y)
	{
		case 0:
			y = LCD_LINE1;
			break;
#if (LCD_Y>1)
		case 1:
			y = LCD_LINE2;
			break;
#endif
#if (LCD_Y>2)
		case 2:
			y = LCD_LINE3;
			break;
#endif
#if (LCD_Y>3)
		case 3:
			y = LCD_LINE4;
			break;
#endif
	}

	LCD_WriteCmd((0x80 + y + x));
}

//
//	Clear LCD
//
void LCD_Cls(void)
{
	LCD_WriteCmd(LCDC_CLS);
}

//
//	Initialization
//
void LCD_Init(void)
{
	RESET_LCD_RS;
	RESET_LCD_E;
#ifdef USE_RW
	RESET_LCD_RW;
#endif
	LCD_DataOut();

	HAL_Delay(15);

	LCD_SetDataPort(LCDC_FUNC|LCDC_FUNC8B);
	HAL_Delay(5);
	LCD_SetDataPort(LCDC_FUNC|LCDC_FUNC8B);
	HAL_Delay(1);
#ifdef LCD_4BIT
	LCD_SetDataPort(LCDC_FUNC|LCDC_FUNC4B); //4-byte mode
	HAL_Delay(1);
	LCD_WriteCmd(LCDC_FUNC|LCDC_FUNC4B|LCDC_FUNC2L|LCDC_FUNC5x7); // 4-bit, 2 lanes, 5x7 chars
#else
	LCD_SetDataPort(LCDC_FUNC|LCDC_FUNC8B);
	HAL_Delay(1);
	LCD_WriteCmd(LCDC_FUNC|LCDC_FUNC8B|LCDC_FUNC2L|LCDC_FUNC5x7); // 4-bit, 2 lanes, 5x7 chars
	HAL_Delay(1);
#endif

	LCD_WriteCmd(LCDC_ONOFF|LCDC_CURSOROFF); // Cursor off
	HAL_Delay(1);
	LCD_WriteCmd(LCDC_ONOFF|LCDC_DISPLAYON); // LCD on
	HAL_Delay(1);
	LCD_WriteCmd(LCDC_ENTRY|LCDC_ENTRYR); // Data entry right
	HAL_Delay(1);
	LCD_Cls(); // Clear display
	HAL_Delay(1);
}

///Funkcje do sterowania wyswietlaczem
void sendDataToDisp(struct lcd_display *displ){

	static uint8_t char_itter = 0;
	static uint8_t line_itter = 0;
	static uint8_t current_state = 0;

	if(current_state == 0) { //stan czyszczenia
		if(!(LCD_CheckBusyFlag() & (1<<7))){ //sprawdzanie flagi zajetosci
			LCD_Cls();
			current_state = 1;
		}
	}
	else if(current_state == 1) { //stan ustawiania kursora
		if(!(LCD_CheckBusyFlag() & (1<<7))){ //sprawdzanie flagi zajetosci
			LCD_Locate(0,line_itter);
			current_state = 2;
		}
	}
	else if(current_state == 2){ //stan wyslania znakow
		if(displ->lines[line_itter][char_itter]) { //jesli dojdzie do konca linii
			if(!(LCD_CheckBusyFlag() & (1<<7))) LCD_Char(displ->lines[line_itter][char_itter++]);
		}
		else {
			current_state = 1;
			char_itter = 0;
			if(++line_itter>(LCD_Y-1)){
				line_itter = 0;
				current_state = 0;
				HAL_TIM_Base_Stop_IT(&htim7);
			}
		}
	}
}


void formDisp_TimeView(struct lcd_display *displ) {
	cleanLines(displ);
	snprintf((char*)displ->lines[0], (LCD_X+1)*sizeof(char), "Flower no. %i", displ->flowers[displ->flower_disp_state]->flower_id);
	snprintf((char*)displ->lines[1], (LCD_X+1)*sizeof(char), "Curr time: %02d:%02d:%02d",
			displ->currentRTCTime->Hours, displ->currentRTCTime->Minutes, displ->currentRTCTime->Seconds);
	snprintf((char*)displ->lines[2], (LCD_X+1)*sizeof(char), "Wat  time: %02d:%02d:%02d",
			displ->flowers[displ->flower_disp_state]->watering_time[0].Hours, displ->flowers[displ->flower_disp_state]->watering_time[0].Minutes, displ->flowers[displ->flower_disp_state]->watering_time[0].Seconds);
	if(displ->flowers[displ->flower_disp_state]->was_watered_flag)
		snprintf((char*)displ->lines[3], (LCD_X+1)*sizeof(char), "Lst Wat:   %02d:%02d:%02d",
				displ->flowers[displ->flower_disp_state]->last_watering_time.Hours, displ->flowers[displ->flower_disp_state]->last_watering_time.Minutes, displ->flowers[displ->flower_disp_state]->last_watering_time.Seconds);

}

void formDisp_MoistureView(struct lcd_display *displ){
	cleanLines(displ);
	snprintf((char*)displ->lines[0], (LCD_X+1)*sizeof(char), "Flower no. %i", displ->flowers[displ->flower_disp_state]->flower_id);
	snprintf((char*)displ->lines[1], (LCD_X+1)*sizeof(char), "Moisture: %i", displ->flowers[displ->flower_disp_state]->moisture);
	//snprintf((char*)disp->lines[2], LCD_X*sizeof(char), " ");
	//snprintf((char*)disp->lines[3], LCD_X*sizeof(char), " ");
}

void formDisp_USART_RecieveDataView(struct lcd_display *displ){
	cleanLines(displ);
	snprintf((char*)displ->lines[0], (LCD_X+1)*sizeof(char), "Received Data: ");
	snprintf((char*)displ->lines[1], (LCD_X+1)*sizeof(char), "%s", displ->additionalDisplayData);
	//snprintf((char*)disp->lines[2], LCD_X*sizeof(char), " ");
	//snprintf((char*)disp->lines[3], LCD_X*sizeof(char), " ");
}

void formDisp_WateringProcess(struct lcd_display *displ){
	cleanLines(displ);
	snprintf((char*)displ->lines[0], (LCD_X+1)*sizeof(char), "Watering process...");
	//snprintf((char*)displ->lines[1], LCD_X*sizeof(char), " ");
	//snprintf((char*)displ->lines[2], LCD_X*sizeof(char), " ");
	//snprintf((char*)displ->lines[3], LCD_X*sizeof(char), " ");
}




void updateDispData(struct lcd_display *displ) {
	for(int i = 0; i< NUMBER_OF_FLOWERS; i++) {
		rescaleSensorData(displ->flowers[i]);
	}
	if(displ->disp_state==0) {
		displ->formDispData_ptr = &formDisp_TimeView;
	}
	else if(disp.disp_state==1){
		displ->formDispData_ptr = &formDisp_MoistureView;
		//rescaleSensorData(displ->flowers[displ->flower_disp_state]);
	}
	else if(disp.disp_state==2){
		displ->formDispData_ptr = &formDisp_USART_RecieveDataView;
	}
	else if(disp.disp_state==3){
		displ->formDispData_ptr = &formDisp_WateringProcess;
	}
	(*(displ->formDispData_ptr))(displ);

}

void cleanLines(struct lcd_display *displ){
	memset(displ->lines,0,LCD_X*LCD_Y*sizeof(displ->lines[0][0]));
}

void changeDispState(struct lcd_display *displ, uint8_t state){
	displ->previous_disp_state = displ->disp_state;
	displ->disp_state = state;
}
void dispInit(struct lcd_display *displ){
	displ->currentRTCTime = &Rtc_Time;
	displ->currentRTCDate = &Rtc_Date;
	displ->flowers[0] = &flowers[0];
	displ->flowers[1] = &flowers[1];
	displ->formDispData_ptr = &formDisp_TimeView;
	displ->flower_disp_state = 0;
	displ->disp_state = 0;
}
