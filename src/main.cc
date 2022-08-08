#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rgb_led.hpp"

#define RGB_LED_RED_GPIO 21
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 18

/**
 * LEDC_TIMER_8_BIT = 255
 * LEDC_TIMER_9_BIT = 512
 * LEDC_TIMER_10_BIT = 1024
 * LEDC_TIMER_12_BIT = 4096
 * LEDC_TIMER_13_BIT = 8192
 * LEDC_TIMER_14_BIT = 16384
 */
#define LED_DUTY_RESOLUTION LEDC_TIMER_12_BIT

extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    LED_RGB::RGB_CONTROL test();
    LED_RGB::RGB_CONTROL rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO, LED_DUTY_RESOLUTION);

    while (true)
    {
        printf("inicio\n");
        rgb_led.set_color(1, 0, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_led.set_color(0, 1, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_led.set_color(0, 0, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_led.set_color(1, 1, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("fim\n");
    }
}