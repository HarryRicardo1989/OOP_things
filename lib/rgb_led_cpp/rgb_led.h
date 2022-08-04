
#pragma once
#include <stdbool.h>
#include "driver/ledc.h"

#define RGB_LED_CHANNEL_NUM 3

#ifdef __cplusplus
extern "C"
{
#endif
    namespace LED
    {

        class RGB_LED

        {
        private:
            bool g_pwm_init_handle = false;

            // RGB LED configuration
            typedef struct
            {
                ledc_channel_t channel;
                int gpio;
                ledc_mode_t mode;
                ledc_timer_t timer_index;

            } ledc_info_t;

            ledc_info_t ledc_ch[RGB_LED_CHANNEL_NUM];

        public:
            RGB_LED(int rgb_led_red_gpio, int rgb_led_green_gpio, int rgb_led_blue_gpio);

            void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue);
        };
    }

#ifdef __cplusplus
}
#endif
