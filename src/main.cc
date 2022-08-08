#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rgb_led.h"
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
    // LED::RGB_LED rgb_led(); //= new LED::RGB_LED(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO);
    //  rgb_led_set_color(1, 0, 0);
    //   LED::RGB_LED(21, LEDC_CHANNEL_0).led_set_value(1);
    //   rgb_led.rgb_led_set_color(50, 0, 0);
    //   rgb_led.rgb_led_set_color(0, 50, 0);
    //   rgb_led.rgb_led_set_color(0, 0, 50);

    while (true)
    {
        printf("inicio\n");
        // printf("Cr\n");
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // printf("Cg\n");
        // rgb_led_set_color(0, 1, 0);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // printf("Cb\n");
        // rgb_led_set_color(0, 0, 1);
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        // printf("fimC\n");
        printf("CPPr\n");
        rgb_led.rgb_led_set_color(2, 0, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("CPPg\n");
        rgb_led.rgb_led_set_color(0, 2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("CPPb\n");
        rgb_led.rgb_led_set_color(0, 0, 2);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("CPP-Black\n");
        rgb_led.rgb_led_set_color(0, 0, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("fimCPP\n");
        printf("fim\n");
    }
}

/* LED::RGB_LED(21, 19, 18).rgb_led_set_color(0, 0, 1);
vTaskDelay(1000 / portTICK_PERIOD_MS);
LED::RGB_LED(21, 19, 18).rgb_led_set_color(0, 1, 0);
vTaskDelay(1000 / portTICK_PERIOD_MS);
LED::RGB_LED(21, 19, 18).rgb_led_set_color(1, 0, 0);
vTaskDelay(1000 / portTICK_PERIOD_MS); */