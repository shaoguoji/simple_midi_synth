/**
  * @file    drv_uart.h
  * @brief   串口驱动头文件
  */

#ifndef __DRV_UART_H
#define __DRV_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/* Defines -------------------------------------------------------------------*/
#define UART_DEBUG_BUFFER_SIZE     256     // 调试串口缓冲区大小
#define UART_MIDI_BUFFER_SIZE      256      // MIDI串口缓冲区大小

/* Function prototypes -------------------------------------------------------*/
void drv_uart_init(void);
uint32_t drv_uart_debug_write(uint8_t *data, uint16_t size);
uint32_t drv_uart_debug_read(uint8_t *data, uint16_t size);
uint32_t drv_uart_debug_available(void);
uint32_t drv_uart_midi_read(uint8_t *data, uint16_t size);
uint32_t drv_uart_midi_available(void);
void drv_uart_idle_callback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_UART_H */ 