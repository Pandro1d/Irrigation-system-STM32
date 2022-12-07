/*
 * Flower_Data.c
 *
 *  Created on: Jan 6, 2022
 *      Author: jozwi
 */
/**
  ******************************************************************************
  * @file    flower_data.c
  * @brief   This file provides code for the configuration
  *          of the flower data struct instances.
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
#include "flower_data.h"
void flowersInit(struct flower_data flowers[]){
	/** Default values
								  */
	flowers[0].Pump_GPIO_PORT = PUMP1_GPIO_Port;
	flowers[0].Pump_GPIO_Pin = PUMP1_Pin;
	flowers[0].watering_time[0].Hours = 0;
	flowers[0].watering_time[0].Minutes = 0;
	flowers[0].watering_time[0].Seconds = 5;
	flowers[0].watering_duration = 5;
	flowers[0].was_watered_flag = 0;
	flowers[0].watering_flag = 0;
	flowers[0].watering_itter = 0;
	flowers[0].flower_id = 1;
	flowers[0].max_sensor_data = 193;
	flowers[0].min_sensor_data = 76;
	flowers[0].PWMchannel = TIM_CHANNEL_1;
	flowers[0].PWMtimer = &htim21;

	flowers[1].Pump_GPIO_PORT = PUMP2_GPIO_Port;
	flowers[1].Pump_GPIO_Pin = PUMP2_Pin;
	flowers[1].watering_time[0].Hours = 0;
	flowers[1].watering_time[0].Minutes = 0;
	flowers[1].watering_time[0].Seconds = 15;
	flowers[1].watering_duration = 8;
	flowers[1].was_watered_flag = 0;
	flowers[1].watering_flag = 0;
	flowers[1].watering_itter = 0;
	flowers[1].flower_id = 2;
	flowers[1].max_sensor_data = 193;
	flowers[1].min_sensor_data = 76;
	flowers[1].PWMchannel = TIM_CHANNEL_2;
	flowers[1].PWMtimer = &htim21;

}

void recalibrateSensorData(struct flower_data* flower){
	if(flower->max_sensor_data<*(flower->sensor_data)&&*(flower->sensor_data)<70)  flower->max_sensor_data = *(flower->sensor_data);
	if(flower->min_sensor_data>*(flower->sensor_data)&&*(flower->sensor_data)>26)  flower->min_sensor_data = *(flower->sensor_data);
}
void rescaleSensorData(struct flower_data* flower){
	//recalibrateSensorData(flower);
	//flower->moisture = (float)*(flower->sensor_data);
	if(*(flower->sensor_data)>flower->max_sensor_data) flower->moisture=flower->max_sensor_data; /// Aby nie przekroczyc wartosci maks i min
	else if(*(flower->sensor_data)<flower->min_sensor_data)flower->moisture=flower->min_sensor_data;
	else flower->moisture = *(flower->sensor_data);
	flower->moisture = 100*(flower->max_sensor_data-flower->moisture)/(flower->max_sensor_data-flower->min_sensor_data);
}

uint8_t checkForWateringTime(struct flower_data* flower, RTC_TimeTypeDef* curr_time){
	if((flower->watering_time[0].Seconds==curr_time->Seconds)&&(flower->watering_time[0].Minutes==curr_time->Minutes)&&(flower->watering_time[0].Hours==curr_time->Hours))flower->watering_flag = 1;
	if((flower->watering_flag)&&(flower->watering_itter < flower->watering_duration)) {
		flower->was_watered_flag=1;
		//HAL_TIM_PWM_Start(flower->PWMtimer, flower->PWMchannel);
		HAL_GPIO_WritePin((GPIO_TypeDef *)flower->Pump_GPIO_PORT, flower->Pump_GPIO_Pin, GPIO_PIN_SET);
		flower->last_watering_time.Hours = curr_time->Hours;
		flower->last_watering_time.Minutes = curr_time->Hours;
		flower->last_watering_time.Seconds = curr_time->Seconds;
		flower->watering_itter++;
	}else if(flower->watering_itter>=flower->watering_duration){
		//HAL_TIM_PWM_Stop(flower->PWMtimer, flower->PWMchannel);
		HAL_GPIO_WritePin((GPIO_TypeDef *)flower->Pump_GPIO_PORT, flower->Pump_GPIO_Pin, GPIO_PIN_RESET);
		flower->watering_itter = 0;
		flower->watering_flag = 0;
	}
	return flower->watering_flag;
}

