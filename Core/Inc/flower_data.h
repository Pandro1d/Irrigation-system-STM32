/*
 * Flower_Data.h
 *
 *  Created on: Jan 6, 2022
 *      Author: jozwi
 */
/**
  ******************************************************************************
  * @file    flower_data.h
  * @brief   This file contains all the function prototypes for
  *          the flower_data.c file
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
#ifndef INC_FLOWER_DATA_H_
#define INC_FLOWER_DATA_H_

#include "main.h"
#include "tim.h"
#include <string.h>

/** Defines max watering time for each flower.
								  */
#define MAX_WATERING_TIMES 2
/** Defines max number of flowers.
								  */
#define NUMBER_OF_FLOWERS 2

/** Struct which contains flower data.
								  */
struct flower_data {
	/** Flower Id.
									  */
	uint8_t flower_id;
	/** Flag which indicates if flower was watered.
									  */
	uint8_t was_watered_flag;
	/** Value is current watering duration.
									  */
	uint8_t watering_itter;

	/** Flag which indicates if flower is being actually watering.
									  */
	uint8_t watering_flag;

	/** Pointer which contains address of sensor data.
									  */
	uint16_t *sensor_data;

	/** Max value which sensor can reach (used for calibration).
									  */
	uint16_t max_sensor_data;
	/** Min value which sensor can reach (used for calibration).
										  */
	uint16_t min_sensor_data;

	/** Moisture of flower expressed as a percentage.
										  */
	uint8_t moisture;

	/** PWM timer handler used for controlling the pumps.
										  */
	TIM_HandleTypeDef *PWMtimer;
	/** PWM timer channel
										  */
	uint32_t PWMchannel;

	/** GPIO pin number used for controlling the pumps.
										  */
	uint16_t Pump_GPIO_Pin;
	/** GPIO port number
											  */
	GPIO_TypeDef *Pump_GPIO_PORT;
	/** Duration of watering (in seconds)
											  */
	uint16_t watering_duration;

	/** RTC table of structures which contains watering times.
												  */
	RTC_TimeTypeDef watering_time[MAX_WATERING_TIMES];
	/** RTC structure which contains last watering time.
												  */
	RTC_TimeTypeDef last_watering_time;
};
/** Definition of external struct flower_data.
											  */
extern struct flower_data flowers[NUMBER_OF_FLOWERS];
/** Function to calibrate the sensor data.
											  */
void recalibrateSensorData(struct flower_data*);
/** Function which rescales sensor data from ADC value to percentage of moisture.
*	@param struct flower_data * Pointer to flower data struct.
											  */
void rescaleSensorData(struct flower_data*);

/** Struct flower_data init with default values
 * @param struct flower_data [] Tab of flower data struct.
											  */
void flowersInit(struct flower_data []);

/** Function is checking if actual time is equal to watering time and changes watering_flag
 * @param struct flower_data *,RTC_TimeTypeDef * Pointer to flower data and pointer to actual time
 * @return watering_flag
											  */
uint8_t checkForWateringTime(struct flower_data *,RTC_TimeTypeDef *);
#endif /* INC_FLOWER_DATA_H_ */
