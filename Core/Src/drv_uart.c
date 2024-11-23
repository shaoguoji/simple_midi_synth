/**
  * @file    drv_uart.c
  * @brief   串口驱动文件
  */

#include "drv_uart.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct {
    uint8_t buffer[UART_DEBUG_BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} uart_buffer_t;

/* Private variables --------------------------------------------------------*/
static uart_buffer_t debug_rx_buffer = {0};
static uart_buffer_t debug_tx_buffer = {0};
static uart_buffer_t midi_rx_buffer = {0};

static uint8_t debug_dma_buffer[UART_DEBUG_BUFFER_SIZE];
static uint8_t midi_dma_buffer[UART_MIDI_BUFFER_SIZE];

extern UART_HandleTypeDef huart2;  // Debug UART
extern UART_HandleTypeDef huart3;  // MIDI UART

/* Private function prototypes -----------------------------------------------*/
static void buffer_write(uart_buffer_t *buffer, uint8_t *data, uint16_t size);
static uint16_t buffer_read(uart_buffer_t *buffer, uint8_t *data, uint16_t size);
static uint16_t buffer_available(uart_buffer_t *buffer);

/* Public functions ---------------------------------------------------------*/
void drv_uart_init(void)
{
    // 使能IDLE中断
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
    
    // 启动Debug串口DMA接收
    HAL_UART_Receive_DMA(&huart2, debug_dma_buffer, UART_DEBUG_BUFFER_SIZE);
    
    // 启动MIDI串口DMA接收
    HAL_UART_Receive_DMA(&huart3, midi_dma_buffer, UART_MIDI_BUFFER_SIZE);
}

uint32_t drv_uart_debug_write(uint8_t *data, uint16_t size)
{
    HAL_UART_Transmit_DMA(&huart2, data, size);
    return size;
}

uint32_t drv_uart_debug_read(uint8_t *data, uint16_t size)
{
    return buffer_read(&debug_rx_buffer, data, size);
}

uint32_t drv_uart_debug_available(void)
{
    return buffer_available(&debug_rx_buffer);
}

uint32_t drv_uart_midi_read(uint8_t *data, uint16_t size)
{
    return buffer_read(&midi_rx_buffer, data, size);
}

uint32_t drv_uart_midi_available(void)
{
    return buffer_available(&midi_rx_buffer);
}

void drv_uart_idle_callback(UART_HandleTypeDef *huart)
{
    uint16_t recv_size;
    
    if (huart == &huart2) {
        // 停止DMA传输
        HAL_UART_DMAStop(huart);
        
        // 计算接收到的数据长度
        recv_size = UART_DEBUG_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
        if (recv_size > 0) {
            // 将数据写入缓冲区
            buffer_write(&debug_rx_buffer, debug_dma_buffer, recv_size);
        }
        
        // 重新启动DMA接收
        HAL_UART_Receive_DMA(huart, debug_dma_buffer, UART_DEBUG_BUFFER_SIZE);
    }
    else if (huart == &huart3) {
        // 停止DMA传输
        HAL_UART_DMAStop(huart);
        
        // 计算接收到的数据长度
        recv_size = UART_MIDI_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
        if (recv_size > 0) {
            // 将数据写入缓冲区
            buffer_write(&midi_rx_buffer, midi_dma_buffer, recv_size);
        }
        
        // 重新启动DMA接收
        HAL_UART_Receive_DMA(huart, midi_dma_buffer, UART_MIDI_BUFFER_SIZE);
    }
}

/* Private functions --------------------------------------------------------*/
static void buffer_write(uart_buffer_t *buffer, uint8_t *data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++) {
        buffer->buffer[buffer->head] = data[i];
        buffer->head = (buffer->head + 1) % UART_DEBUG_BUFFER_SIZE;
        if (buffer->count < UART_DEBUG_BUFFER_SIZE) {
            buffer->count++;
        } else {
            buffer->tail = (buffer->tail + 1) % UART_DEBUG_BUFFER_SIZE;
        }
    }
}

static uint16_t buffer_read(uart_buffer_t *buffer, uint8_t *data, uint16_t size)
{
    uint16_t read_size = 0;
    
    while (buffer->count > 0 && read_size < size) {
        data[read_size++] = buffer->buffer[buffer->tail];
        buffer->tail = (buffer->tail + 1) % UART_DEBUG_BUFFER_SIZE;
        buffer->count--;
    }
    
    return read_size;
}

static uint16_t buffer_available(uart_buffer_t *buffer)
{
    return buffer->count;
}
  