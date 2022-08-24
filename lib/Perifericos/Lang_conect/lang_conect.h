#pragma once

#define RGB_LED_RED_GPIO 13
#define RGB_LED_GREEN_GPIO 12
#define RGB_LED_BLUE_GPIO 14

/**
 * LEDC_TIMER_8_BIT = 255
 * LEDC_TIMER_9_BIT = 512
 * LEDC_TIMER_10_BIT = 1024
 * LEDC_TIMER_12_BIT = 4096
 * LEDC_TIMER_13_BIT = 8192
 * LEDC_TIMER_14_BIT = 16384
 */
#define LED_DUTY_RESOLUTION LEDC_TIMER_12_BIT

#ifdef __cplusplus
extern "C"
{
#endif

    void set_rgb_led_interface(int red, int blue, int green);
    void open_with_password_connect(char *password);
    void set_led_ble(void);
    void set_led_access_denid(void);
    void set_led_access_allowed(void);

#ifdef __cplusplus
}
#endif