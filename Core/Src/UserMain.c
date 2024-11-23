/**
  * @file    UserMain.c
  * @brief   用户代码主文件
  */

#include "UserMain.h"

/**
  * @brief  用户代码初始化函数
  * @param  None
  * @retval None
  */
void UserMain_Init(void)
{
    /* 在此添加初始化代码 */
}

/**
  * @brief  用户代码主循环函数
  * @param  None
  * @retval None
  */
void UserMain_Loop(void)
{
    static uint32_t led_blink_tick = 0;
    
    if (HAL_GetTick() - led_blink_tick >= 500) 
    {
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);  // LED_BLUE
        led_blink_tick = HAL_GetTick();

        // printf("Hello, World!\n");
    }

} 