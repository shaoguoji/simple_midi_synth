/**
  * @file    UserMain.c
  * @brief   用户代码主文件
  */

#include "UserMain.h"
#include "midi.h"
/**
  * @brief  用户代码初始化函数
  * @param  None
  * @retval None
  */
void User_Init(void)
{
    drv_uart_init();
    
    // 先初始化 CODEC
    drv_cs43l22_init();
    drv_cs43l22_set_volume(90);  // 设置初始音量为70%
    
    // 再初始化并启动合成器
    synth_init();
    HAL_Delay(10);  // 等待CODEC稳定
    synth_start();
    drv_cs43l22_play();  // 确保CODEC开始播放
}

/**
  * @brief  用户代码主循环函数
  * @param  None
  * @retval None
  */
void User_Main(void)
{
    static uint32_t led_blink_tick = 0;
    
    if (HAL_GetTick() - led_blink_tick >= 500) 
    {
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);  // LED_BLUE
        led_blink_tick = HAL_GetTick();

        // printf("Hello, World!\n");
        // drv_uart_debug_write("Hello, World!\n", 14);
    }

    midi_main();
} 
