#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rgb_led.h"

#define RGB_LED_RED_GPIO 21
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 18
extern "C"
{
    void app_main(void);
}

void app_main(void)
{

    // LED::RGB_LED rgb_led = LED::RGB_LED(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO);
    LED::RGB_LED(21, 19, 18).rgb_led_set_color(0, 0, 50);
    // rgb_led.rgb_led_set_color(50, 0, 0);
    // rgb_led.rgb_led_set_color(0, 50, 0);
    // rgb_led.rgb_led_set_color(0, 0, 50);
}