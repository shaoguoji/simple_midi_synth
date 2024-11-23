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
#include "stm32f4xx_hal.h"

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
#define USART_DEBUG_TX_Pin GPIO_PIN_2
#define USART_DEBUG_TX_GPIO_Port GPIOA
#define USART_DEBUG_RX_Pin GPIO_PIN_3
#define USART_DEBUG_RX_GPIO_Port GPIOA
#define I2S_CODEC_WS_Pin GPIO_PIN_4
#define I2S_CODEC_WS_GPIO_Port GPIOA
#define USART_MIDI_TX_Pin GPIO_PIN_8
#define USART_MIDI_TX_GPIO_Port GPIOD
#define USART_MIDI_RX_Pin GPIO_PIN_9
#define USART_MIDI_RX_GPIO_Port GPIOD
#define LED_GREEN_Pin GPIO_PIN_12
#define LED_GREEN_GPIO_Port GPIOD
#define LED_ORANGE_Pin GPIO_PIN_13
#define LED_ORANGE_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOD
#define LED_BLUE_Pin GPIO_PIN_15
#define LED_BLUE_GPIO_Port GPIOD
#define I2S_CODEC_MCK_Pin GPIO_PIN_7
#define I2S_CODEC_MCK_GPIO_Port GPIOC
#define I2S_CODEC_SCK_Pin GPIO_PIN_10
#define I2S_CODEC_SCK_GPIO_Port GPIOC
#define I2S_CODEC_SD_Pin GPIO_PIN_12
#define I2S_CODEC_SD_GPIO_Port GPIOC
#define CODEC_RST_Pin GPIO_PIN_4
#define CODEC_RST_GPIO_Port GPIOD
#define I2C_CODEC_SCL_Pin GPIO_PIN_6
#define I2C_CODEC_SCL_GPIO_Port GPIOB
#define I2C_CODEC_SDA_Pin GPIO_PIN_9
#define I2C_CODEC_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern I2C_HandleTypeDef hi2c1;
extern I2S_HandleTypeDef hi2s3;
extern DMA_HandleTypeDef hdma_spi3_tx;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
