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

uint8_t led_mode, led_light, led_color, led_flag;
uint32_t led_red = 0, led_green = 255, led_blue = 255, led_rgb;
unsigned char pitch_str[10], yaw_str[10], roll_str[10], temp_str[10];

int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(72);                /* ��ʼ��USMART */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */
    tp_dev.init();                      /* ��������ʼ�� */
    btim_timx_int_init(10-1,7200-1);    /* ��ʼ����ʱ�� */
	
	WS2812B_Init();

    lv_init();                          /* lvglϵͳ��ʼ�� */
    lv_port_disp_init();                /* lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ��� */
    lv_port_indev_init();               /* lvgl����ӿڳ�ʼ��,����lv_init()�ĺ��� */
    
    //lv_demo_stress();                   /* lvgl�ٷ����� */
	//ui_init();
	ui_led_start();
	
    while(1)
    {
        lv_task_handler();

        
        switch (led_mode)
        {
        case 0:
            ws2812_AllShutOff();  
            break;
        case 1:
            led_rgb = (led_green << 16) | (led_red << 8) | led_blue;
            light_ctr(led_light, led_rgb);
            break;
        case 2:
            rainbowCycle(14);
            break;
        case 3:
            Running_water_lamp(led_red, led_green, led_blue, 100);
            break;
        case 4:
            horse_race_lamp(100);
            break;
        case 5:
            led_rgb = (led_green << 16) | (led_red << 8) | led_blue;
            ws2812_All_LED_one_Color_breath(20, led_rgb);
            break;
        default:
            break;
        }
    }
}
