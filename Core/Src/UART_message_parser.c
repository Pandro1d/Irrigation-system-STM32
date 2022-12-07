/*
 * UART_message_parser.c
 *
 *  Created on: Jan 24, 2022
 *      Author: jozwi
 */

/**
  ******************************************************************************
  * @file    UART_message_parser.c
  * @brief   This file provides code for UART parser functions
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
#include "UART_message_parser.h"

uint8_t parseData(struct uart_struct *uart_str) {
	char buff[uart_str->receive_itter];

	memset(buff, 0, uart_str->receive_itter);
	uint8_t buff_iter = 0;
	uint8_t time_get_state =0;

	uint8_t flower_id = 0;

	for(uint8_t parse_iter =0; parse_iter < uart_str->receive_itter; parse_iter++) {
	     if (uart_str->UART_data_buff[parse_iter] == ' '||uart_str->UART_data_buff[parse_iter] == '/') {
	            parse_iter++;

	            if (!strcmp(buff, "setCurrTime")) {

	                memset(buff, 0, uart_str->receive_itter);
	                while (parse_iter < uart_str->receive_itter) {
	                    if (uart_str->UART_data_buff[parse_iter] == ':') {
	                        if (!time_get_state) {

	                        	Rtc_Time.Hours = (uint8_t) atoi(buff);
	                            memset(buff, 0, uart_str->receive_itter);
	                            buff_iter = 0;
	                            parse_iter++;
	                            time_get_state = 1;
	                        } else if (time_get_state) {

	                        	Rtc_Time.Minutes = (uint8_t) atoi(buff);
	                            memset(buff, 0, uart_str->receive_itter);
	                            buff_iter = 0;
	                            parse_iter++;
	                            time_get_state = 0;
	                        }
	                    } else if (uart_str->UART_data_buff[parse_iter] == '/') {
	                    	Rtc_Time.Seconds = (uint8_t) atoi(buff);
	                    	HAL_RTC_SetTime(&hrtc, &Rtc_Time, RTC_FORMAT_BIN);

	                        return 1;
	                    } else buff[buff_iter++] = uart_str->UART_data_buff[parse_iter++];
	                }

	            } else if (!strcmp(buff, "setWatTime")) {

	                memset(buff, 0, uart_str->receive_itter);
	                while (parse_iter < uart_str->receive_itter && uart_str->UART_data_buff[parse_iter] != ' ') {
	                    buff[buff_iter++] = uart_str->UART_data_buff[parse_iter++];
	                }

	                flower_id = (int)atof(buff);
	                if(flower_id > NUMBER_OF_FLOWERS||flower_id==0) return 0;

	                buff_iter = 0;
	                memset(buff, 0, uart_str->receive_itter);
	                parse_iter++;
	                while (parse_iter < uart_str->receive_itter) {
	                    if (uart_str->UART_data_buff[parse_iter] == ':') {
	                        if (!time_get_state) {
	                            flowers[flower_id-1].watering_time[0].Hours = (int) atoi(buff);
	                            memset(buff, 0, uart_str->receive_itter);
	                            buff_iter = 0;
	                            parse_iter++;
	                            time_get_state = 1;
	                        } else if (time_get_state) {
	                        	flowers[flower_id-1].watering_time[0].Minutes = (int) atoi(buff);
	                            memset(buff, 0, uart_str->receive_itter);
	                            buff_iter = 0;
	                            parse_iter++;
	                            time_get_state = 0;
	                        }
	                    } else if (uart_str->UART_data_buff[parse_iter] == '/') {
	                    	flowers[flower_id-1].watering_time[0].Seconds = (int) atoi(buff);
	                        return 1;
	                    } else buff[buff_iter++] = uart_str->UART_data_buff[parse_iter++];
	                }

	            } else if (!strcmp(buff, "setDurTime")) {

	                memset(buff, 0, uart_str->receive_itter);
	                while (parse_iter < uart_str->receive_itter && uart_str->UART_data_buff[parse_iter] != ' ') {
	                    buff[buff_iter++] = uart_str->UART_data_buff[parse_iter++];
	                }
	                flower_id = (int)atof(buff);
	                if(flower_id > NUMBER_OF_FLOWERS||flower_id<=0) return 0;

	                buff_iter = 0;
	                memset(buff, 0, uart_str->receive_itter);
	                parse_iter++;
	                memset(buff, 0, uart_str->receive_itter);
	                while (parse_iter < uart_str->receive_itter && uart_str->UART_data_buff[parse_iter] != '/') {
	                    buff[buff_iter++] = uart_str->UART_data_buff[parse_iter++];
	                }
	                flowers[flower_id-1].watering_duration = (int)atof(buff);
	                return 1;

	            } else if (!strcmp(buff, "startWat")) {

	                memset(buff, 0, uart_str->receive_itter);
	                while (parse_iter < uart_str->receive_itter && uart_str->UART_data_buff[parse_iter] != ' ') {
	                    buff[buff_iter++] = uart_str->UART_data_buff[parse_iter++];
	                }
	                flower_id = (int)atof(buff);

	                if(flower_id > NUMBER_OF_FLOWERS||flower_id<=0)return 0;
	                else {
	                	flowers[flower_id-1].watering_flag = 1;
	                	return 1;
	                }


	            } else if (!strcmp(buff, "info")) {

	            	uart_str->sending_data_flag = 1;
	            	return 1;

	            } else {

	            	return 0;
	            }

	        }
	        buff[parse_iter] = uart_str->UART_data_buff[parse_iter];
	    }
	return 0;
}



