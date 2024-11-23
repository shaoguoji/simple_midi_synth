/**
  * @file    synth.c
  * @brief   波表合成器源文件
  */

#include "synth.h"

/* Private defines ----------------------------------------------------------*/
#define PI 3.14159265359f

/* Private variables -------------------------------------------------------*/
static int16_t wavetable[SYNTH_WAVETABLE_SIZE];  // 波表
static int16_t audio_buffer[SYNTH_BUFFER_SIZE];   // 音频缓冲区
static uint32_t phase_acc = 0;                    // 相位累加器
static uint32_t phase_inc;                        // 相位增量

/* Private function prototypes ---------------------------------------------*/
static void generate_sine_wavetable(void);
static void fill_audio_buffer(int16_t* buffer, uint16_t size);

/* Public functions -------------------------------------------------------*/
/**
  * @brief  初始化合成器
  * @param  None
  * @retval None
  */
void synth_init(void)
{
    // 生成正弦波表
    generate_sine_wavetable();
    
    // 计算相位增量
    // phase_inc = (freq * wavetable_size * 2^32) / sample_rate
    phase_inc = (uint32_t)((float)SYNTH_TEST_FREQ * SYNTH_WAVETABLE_SIZE / SYNTH_SAMPLE_RATE);
    
    // 初始化音频缓冲区
    fill_audio_buffer(audio_buffer, SYNTH_BUFFER_SIZE);
}

/**
  * @brief  开始音频输出
  * @param  None
  * @retval None
  */
void synth_start(void)
{
    // 启动I2S DMA传输
    HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t*)audio_buffer, SYNTH_BUFFER_SIZE);
}

/**
  * @brief  停止音频输出
  * @param  None
  * @retval None
  */
void synth_stop(void)
{
    HAL_I2S_DMAStop(&hi2s3);
}

/**
  * @brief  更新合成器状态
  * @param  None
  * @retval None
  */
void synth_update(void)
{
    // 在这里可以添加实时参数更新的代码
}

/* Private functions ------------------------------------------------------*/
/**
  * @brief  生成正弦波表
  * @param  None
  * @retval None
  */
static void generate_sine_wavetable(void)
{
    for (int i = 0; i < SYNTH_WAVETABLE_SIZE; i++) {
        float angle = (2.0f * PI * i) / SYNTH_WAVETABLE_SIZE;
        wavetable[i] = (int16_t)(32767.0f * sinf(angle));
    }
}

/**
  * @brief  填充音频缓冲区
  * @param  buffer: 缓冲区指针
  * @param  size: 缓冲区大小
  * @retval None
  */
static void fill_audio_buffer(int16_t* buffer, uint16_t size)
{
    for (uint16_t i = 0; i < size; i += 2) {  // 注意这里步进为2
        // 获取波表索引(使用相位累加器的高8位)
        uint8_t index = phase_acc;
        
        // 获取波表值并写入左右声道
        buffer[i] = wavetable[index];      // 左声道
        buffer[i+1] = wavetable[index];    // 右声道
        
        // 更新相位累加器
        phase_acc += phase_inc;
    }
}

/* Callbacks --------------------------------------------------------------*/
/**
  * @brief  I2S DMA 传输完成回调
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if(hi2s->Instance == SPI3)
    {
        // 填充后半部分缓冲区
        fill_audio_buffer(&audio_buffer[SYNTH_BUFFER_SIZE/2], SYNTH_BUFFER_SIZE/2);
    }
}

/**
  * @brief  I2S DMA 传输半完成回调
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if(hi2s->Instance == SPI3)
    {
        // 填充前半部分缓冲区
        fill_audio_buffer(audio_buffer, SYNTH_BUFFER_SIZE/2);
    }
} 