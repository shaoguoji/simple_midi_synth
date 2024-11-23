/**
  * @file    drv_cs43l22.c
  * @brief   CS43L22 codec驱动文件
  */

#include "drv_cs43l22.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t is_initialized = 0;

/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef write_register(uint8_t reg, uint8_t value);
static HAL_StatusTypeDef read_register(uint8_t reg, uint8_t *value);

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  初始化CS43L22
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef drv_cs43l22_init(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint8_t id;

    /* 复位CS43L22 */
    HAL_GPIO_WritePin(CODEC_RST_GPIO_Port, CODEC_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(CODEC_RST_GPIO_Port, CODEC_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(5);

    /* 读取芯片ID验证通信 */
    status = read_register(CS43L22_REG_ID, &id);
    if (status != HAL_OK || (id & 0xF8) != 0xE0) {
        return HAL_ERROR;
    }

    /* 初始化寄存器配置 */
    write_register(0x00, 0x99);     // 解除写保护
    write_register(0x47, 0x80);     // 设置额外功能
    write_register(0x32, 0xBB);     // 设置主音量
    write_register(0x32, 0x3B);     // 设置主音量
    write_register(0x00, 0x00);     // 恢复写保护

    write_register(CS43L22_REG_POWER_CTL1, 0x9E);  // Power down

    /* 时钟配置 */
    write_register(CS43L22_REG_CLOCKING_CTL, 0x81);  // Auto detect clock
    write_register(CS43L22_REG_INTERFACE_CTL1, 0x07);  // I2S 24bit

    /* PCM配置 */
    write_register(CS43L22_REG_PCMA_VOL, 0x0A);  // PCM A volume
    write_register(CS43L22_REG_PCMB_VOL, 0x0A);  // PCM B volume

    /* 音量配置 */
    write_register(CS43L22_REG_MASTER_A_VOL, 0x00);
    write_register(CS43L22_REG_MASTER_B_VOL, 0x00);
    write_register(CS43L22_REG_HP_B_VOL, 0x00);
    write_register(CS43L22_REG_HP_B_VOL, 0x00);
    write_register(CS43L22_REG_SPEAKER_A_VOL, 0x00);
    write_register(CS43L22_REG_SPEAKER_B_VOL, 0x00);

    /* 上电 */
    write_register(CS43L22_REG_POWER_CTL2, 0xAF);  // Power up
    write_register(CS43L22_REG_POWER_CTL1, 0x9E);  // Power up

    is_initialized = 1;
    return status;
}

/**
  * @brief  开始播放
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef drv_cs43l22_play(void)
{
    if (!is_initialized) return HAL_ERROR;
    
    /* 取消静音并开始播放 */
    write_register(CS43L22_REG_POWER_CTL2, 0xAF);
    return HAL_OK;
}

/**
  * @brief  暂停播放
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef drv_cs43l22_pause(void)
{
    if (!is_initialized) return HAL_ERROR;
    
    /* 静音 */
    write_register(CS43L22_REG_POWER_CTL2, 0x01);
    return HAL_OK;
}

/**
  * @brief  停止播放
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef drv_cs43l22_stop(void)
{
    if (!is_initialized) return HAL_ERROR;
    
    /* 静音并关闭输出 */
    write_register(CS43L22_REG_POWER_CTL2, 0x01);
    write_register(CS43L22_REG_POWER_CTL1, 0x9F);
    return HAL_OK;
}

/**
  * @brief  设置音量
  * @param  volume: 音量值(0-100)
  * @retval HAL status
  */
HAL_StatusTypeDef drv_cs43l22_set_volume(uint8_t volume)
{
    if (!is_initialized) return HAL_ERROR;
    
    /* 将0-100映射到0-255 */
    uint8_t vol = (volume * 255) / 100;
    
    /* 设置主音量 */
    write_register(CS43L22_REG_MASTER_A_VOL, vol);
    write_register(CS43L22_REG_MASTER_B_VOL, vol);
    return HAL_OK;
}

/**
  * @brief  设置静音
  * @param  mute: 1-静音, 0-取消静音
  * @retval HAL status
  */
HAL_StatusTypeDef drv_cs43l22_set_mute(uint8_t mute)
{
    if (!is_initialized) return HAL_ERROR;
    
    if (mute) {
        write_register(CS43L22_REG_POWER_CTL2, 0x01);
    } else {
        write_register(CS43L22_REG_POWER_CTL2, 0xAF);
    }
    return HAL_OK;
}

/* Private functions --------------------------------------------------------*/
/**
  * @brief  写CS43L22寄存器
  * @param  reg: 寄存器地址
  * @param  value: 要写入的值
  * @retval HAL status
  */
static HAL_StatusTypeDef write_register(uint8_t reg, uint8_t value)
{
    return HAL_I2C_Mem_Write(&hi2c1, CS43L22_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY);
}

/**
  * @brief  读CS43L22寄存器
  * @param  reg: 寄存器地址
  * @param  value: 读取值的存储地址
  * @retval HAL status
  */
static HAL_StatusTypeDef read_register(uint8_t reg, uint8_t *value)
{
    return HAL_I2C_Mem_Read(&hi2c1, CS43L22_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, value, 1, HAL_MAX_DELAY);
}