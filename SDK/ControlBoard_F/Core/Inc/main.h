/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

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
#define Vin_Pin GPIO_PIN_0
#define Vin_GPIO_Port GPIOC
#define Vout_Pin GPIO_PIN_1
#define Vout_GPIO_Port GPIOC
#define IL_Pin GPIO_PIN_3
#define IL_GPIO_Port GPIOC
#define PWMBL_Pin GPIO_PIN_10
#define PWMBL_GPIO_Port GPIOE
#define PWMBH_Pin GPIO_PIN_11
#define PWMBH_GPIO_Port GPIOE
#define Iin_Pin GPIO_PIN_2
#define Iin_GPIO_Port GPIOA
#define PWMAL_Pin GPIO_PIN_8
#define PWMAL_GPIO_Port GPIOE
#define Iout_Pin GPIO_PIN_3
#define Iout_GPIO_Port GPIOA
#define PWMAH_Pin GPIO_PIN_9
#define PWMAH_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
