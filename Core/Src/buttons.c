/*
 * buttons.c
 *
 *  Created on: Jan 8, 2022
 *      Author: jozwi
 */
/**
  ******************************************************************************
  * @file    buttons.c
  * @brief   This file provides code for buttons functions.
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
#include "buttons.h"


void BLUE_BUTTONFun(){
	Reset_Time(&hrtc, disp.currentRTCTime);
}

void LCD_Button1Fun(){
	if(++(disp.disp_state)>1) {
		changeDispState(&disp, 0);
	}

}
void LCD_Button2Fun(){
	if(++(disp.flower_disp_state)>1) disp.flower_disp_state = 0;
}
