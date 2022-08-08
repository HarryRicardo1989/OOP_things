#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rgb_led.hpp"

#define RGB_LED_RED_GPIO 21
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 18
#define LED_DUTY_RESOLUTION LEDC_TIMER_10_BIT
extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    LED_RGB::RGB_LED rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO, LED_DUTY_RESOLUTION);

    while (true)
    {
        printf("inicio\n");
        rgb_led.rgb_led_set_color(2, 0, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_led.rgb_led_set_color(0, 2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_led.rgb_led_set_color(0, 0, 2);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rgb_led.rgb_led_set_color(0, 0, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("fim\n");
    }
}