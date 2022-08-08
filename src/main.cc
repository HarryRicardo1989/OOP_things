#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rgb_led.hpp"

#define RGB_LED_RED_GPIO 21
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 18
extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    LED_RGB::RGB_LED rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO);

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

/* LED::RGB_LED(21, 19, 18).rgb_led_set_color(0, 0, 1);
vTaskDelay(1000 / portTICK_PERIOD_MS);
LED::RGB_LED(21, 19, 18).rgb_led_set_color(0, 1, 0);
vTaskDelay(1000 / portTICK_PERIOD_MS);
LED::RGB_LED(21, 19, 18).rgb_led_set_color(1, 0, 0);
vTaskDelay(1000 / portTICK_PERIOD_MS); */