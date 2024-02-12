#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "./BSP/TIMER/btim.h"
#include "./BSP/TOUCH/touch.h"
#include "./BSP/ws2812/ws2812.h"

/* LVGL */
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "lv_demo_stress.h"
#include "ui.h"
#include "ui_led.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    usmart_dev.init(72);                /* 初始化USMART */
    led_init();                         /* 初始化LED */
    lcd_init();                         /* 初始化LCD */
    key_init();                         /* 初始化按键 */
    my_mem_init(SRAMIN);                /* 初始化内部SRAM内存池 */
    tp_dev.init();                      /* 触摸屏初始化 */
    btim_timx_int_init(10-1,7200-1);    /* 初始化定时器 */
	
	WS2812B_Init();

    lv_init();                          /* lvgl系统初始化 */
    lv_port_disp_init();                /* lvgl显示接口初始化,放在lv_init()的后面 */
    lv_port_indev_init();               /* lvgl输入接口初始化,放在lv_init()的后面 */
    
    //lv_demo_stress();                   /* lvgl官方例程 */
	//ui_init();
	ui_led_start();
	
    while(1)
    {
        lv_task_handler();
        WS2812B_Test();
    }
}
