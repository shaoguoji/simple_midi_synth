/**
  * @file    synth.h
  * @brief   波表合成器头文件
  */

#ifndef __SYNTH_H
#define __SYNTH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>
#include <math.h>

/* Defines -------------------------------------------------------------------*/
#define SYNTH_WAVETABLE_SIZE   256     // 波表大小
#define SYNTH_BUFFER_SIZE      512     // DMA缓冲区大小(双缓冲)
#define SYNTH_SAMPLE_RATE      48000   // 采样率
#define SYNTH_TEST_FREQ        440     // 测试音频率(Hz)

/* Function prototypes -------------------------------------------------------*/
void synth_init(void);
void synth_start(void);
void synth_stop(void);
void synth_update(void);

/* Callback prototypes ------------------------------------------------------*/
void synth_tx_complete_callback(void);
void synth_tx_half_complete_callback(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYNTH_H */ 