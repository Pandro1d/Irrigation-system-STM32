/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLUE_BUTTON_Pin GPIO_PIN_13
#define BLUE_BUTTON_GPIO_Port GPIOC
#define BLUE_BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define LCD_E_Pin GPIO_PIN_0
#define LCD_E_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_1
#define LCD_RS_GPIO_Port GPIOC
#define LCD_RW_Pin GPIO_PIN_3
#define LCD_RW_GPIO_Port GPIOC
#define MoistureSensor1_Pin GPIO_PIN_0
#define MoistureSensor1_GPIO_Port GPIOA
#define MoistureSensor2_Pin GPIO_PIN_1
#define MoistureSensor2_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define PUMP2DC_Pin GPIO_PIN_13
#define PUMP2DC_GPIO_Port GPIOB
#define PUMP1DC_Pin GPIO_PIN_14
#define PUMP1DC_GPIO_Port GPIOB
#define LCD_Button2_Pin GPIO_PIN_6
#define LCD_Button2_GPIO_Port GPIOC
#define LCD_Button2_EXTI_IRQn EXTI4_15_IRQn
#define LCD_Button1_Pin GPIO_PIN_8
#define LCD_Button1_GPIO_Port GPIOC
#define LCD_Button1_EXTI_IRQn EXTI4_15_IRQn
#define PUMP2_Pin GPIO_PIN_8
#define PUMP2_GPIO_Port GPIOA
#define PUMP1_Pin GPIO_PIN_9
#define PUMP1_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_7
#define LCD_D7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
