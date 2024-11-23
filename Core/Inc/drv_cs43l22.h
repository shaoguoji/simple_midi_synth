/**
  * @file    drv_cs43l22.h
  * @brief   CS43L22 codec驱动头文件
  */

#ifndef __DRV_CS43L22_H
#define __DRV_CS43L22_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/
#define CS43L22_I2C_ADDR                 0x94  // 0x4A << 1

/* CS43L22 寄存器地址 */
#define CS43L22_REG_ID                   0x01  // Chip ID
#define CS43L22_REG_POWER_CTL1           0x02  // Power Control 1
#define CS43L22_REG_POWER_CTL2           0x04  // Power Control 2
#define CS43L22_REG_CLOCKING_CTL         0x05  // Clocking Control
#define CS43L22_REG_INTERFACE_CTL1       0x06  // Interface Control 1
#define CS43L22_REG_INTERFACE_CTL2       0x07  // Interface Control 2
#define CS43L22_REG_PASSTHR_A_SELECT     0x08  // Passthrough A Select
#define CS43L22_REG_PASSTHR_B_SELECT     0x09  // Passthrough B Select
#define CS43L22_REG_ANALOG_ZC_SR         0x0A  // Analog ZC and SR Settings
#define CS43L22_REG_PASSTHR_GANG_CTL     0x0C  // Passthrough Gang Control
#define CS43L22_REG_PLAYBACK_CTL1        0x0D  // Playback Control 1
#define CS43L22_REG_MISC_CTL             0x0E  // Miscellaneous Controls
#define CS43L22_REG_PLAYBACK_CTL2        0x0F  // Playback Control 2
#define CS43L22_REG_PCMA_VOL            0x1A  // PCM A Volume
#define CS43L22_REG_PCMB_VOL            0x1B  // PCM B Volume
#define CS43L22_REG_BEEP_FREQ_ON_TIME    0x1C  // BEEP Frequency and On Time
#define CS43L22_REG_BEEP_VOL_OFF_TIME    0x1D  // BEEP Volume and Off Time
#define CS43L22_REG_BEEP_TONE_CFG        0x1E  // BEEP Tone Configuration
#define CS43L22_REG_TONE_CTL             0x1F  // Tone Control
#define CS43L22_REG_MASTER_A_VOL         0x20  // Master A Volume
#define CS43L22_REG_MASTER_B_VOL         0x21  // Master B Volume
#define CS43L22_REG_HP_A_VOL             0x22  // Headphone A Volume
#define CS43L22_REG_HP_B_VOL             0x23  // Headphone B Volume
#define CS43L22_REG_SPEAKER_A_VOL        0x24  // Speaker A Volume
#define CS43L22_REG_SPEAKER_B_VOL        0x25  // Speaker B Volume
#define CS43L22_REG_CH_MIXER_SWAP        0x26  // Channel Mixer and Swap
#define CS43L22_REG_LIMIT_CTL1           0x27  // Limit Control 1
#define CS43L22_REG_LIMIT_CTL2           0x28  // Limit Control 2
#define CS43L22_REG_LIMIT_ATTACK_RATE    0x29  // Limiter Attack Rate
#define CS43L22_REG_STATUS               0x2E  // Status
#define CS43L22_REG_BATTERY_COMP         0x2F  // Battery Compensation
#define CS43L22_REG_VP_BATTERY_LEVEL     0x30  // VP Battery Level
#define CS43L22_REG_SPEAKER_STATUS       0x31  // Speaker Status
#define CS43L22_REG_TEMP_MON_CTL         0x32  // Temperature Monitor Control

/* Function prototypes -------------------------------------------------------*/
HAL_StatusTypeDef drv_cs43l22_init(void);
HAL_StatusTypeDef drv_cs43l22_play(void);
HAL_StatusTypeDef drv_cs43l22_pause(void);
HAL_StatusTypeDef drv_cs43l22_stop(void);
HAL_StatusTypeDef drv_cs43l22_set_volume(uint8_t volume);
HAL_StatusTypeDef drv_cs43l22_set_mute(uint8_t mute);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CS43L22_H */ 