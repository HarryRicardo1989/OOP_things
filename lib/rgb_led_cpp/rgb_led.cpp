#include "rgb_led.hpp"

#define LEDC_TIMER LEDC_TIMER_2
#define LEDC_MODE LED
#define LEDC_OUTPUT_IO (5)              // Define the output GPIO
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_FREQUENCY (10)             // Frequency in Hertz. Set frequency at 5 kHz

namespace LED
{
    RGB_LED::RGB_LED(int rgb_led_red_gpio, int rgb_led_green_gpio, int rgb_led_blue_gpio)
    {
        int rgb_ch;
        // red
        ledc_ch[0].channel = LEDC_CHANNEL_0;
        ledc_ch[0].gpio = rgb_led_red_gpio;
        ledc_ch[0].mode = LEDC_MODE;
        ledc_ch[0].timer_index = LEDC_TIMER;

        // green

        ledc_ch[1].channel = LEDC_CHANNEL_1;
        ledc_ch[1].gpio = rgb_led_green_gpio;
        ledc_ch[1].mode = LEDC_MODE;
        ledc_ch[1].timer_index = LEDC_TIMER;

        // blue

        ledc_ch[2].channel = LEDC_CHANNEL_2;
        ledc_ch[2].gpio = rgb_led_blue_gpio;
        ledc_ch[2].mode = LEDC_MODE;
        ledc_ch[2].timer_index = LEDC_TIMER;

        // configure timer zero
        ledc_timer_config_t ledc_timer;

        ledc_timer.duty_resolution = LEDC_DUTY_RES;
        ledc_timer.freq_hz = LEDC_FREQUENCY;
        ledc_timer.speed_mode = LEDC_MODE;
        ledc_timer.timer_num = LEDC_TIMER;
        ledc_timer.clk_cfg = LEDC_AUTO_CLK;

        ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

        printf("\n");
        printf("0-> channel:%d gpio:%d mode:%d timer_index:%d \n",
               ledc_ch[0].channel,
               ledc_ch[0].gpio,
               ledc_ch[0].mode,
               ledc_ch[0].timer_index);

        printf("1-> channel:%d gpio:%d mode:%d timer_index:%d\n",
               ledc_ch[1]
                   .channel,
               ledc_ch[1].gpio,
               ledc_ch[1].mode,
               ledc_ch[1].timer_index);
        printf("2-> channel:%d gpio:%d mode:%d timer_index:%d\n",
               ledc_ch[2].channel,
               ledc_ch[2].gpio,
               ledc_ch[2].mode,
               ledc_ch[2].timer_index);

        //  configure channels
        for (rgb_ch = 0; rgb_ch < RGB_LED_CHANNEL_NUM; rgb_ch++)
        {

            ledc_channel_config_t ledc_channel;
            ledc_channel.channel = ledc_ch[rgb_ch].channel;
            ledc_channel.duty = 0;
            ledc_channel.hpoint = 0;
            ledc_channel.gpio_num = ledc_ch[rgb_ch].gpio;
            ledc_channel.intr_type = LEDC_INTR_DISABLE;
            ledc_channel.speed_mode = ledc_ch[rgb_ch].mode;
            ledc_channel.timer_sel = ledc_ch[rgb_ch].timer_index;
            ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

            printf("rgb_ch:%d-> gpio_num:%d speed_mode:%d timer_sel:%d channel:%d\n",
                   rgb_ch, ledc_channel.gpio_num, ledc_channel.speed_mode, ledc_channel.timer_sel, ledc_channel.channel);
        }
        g_pwm_init_handle = true;
    }
    void RGB_LED::rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue)
    {
        uint8_t color[3];
        color[0] = red;
        color[1] = green;
        color[2] = blue;

        // Value should be 0 - 255 for 8 bit number
        for (int rgb_ch = 0; rgb_ch < RGB_LED_CHANNEL_NUM; rgb_ch++)
        {

            ESP_ERROR_CHECK(ledc_set_duty(ledc_ch[rgb_ch].mode, ledc_ch[rgb_ch].channel, color[rgb_ch]));
            ESP_ERROR_CHECK(ledc_update_duty(ledc_ch[rgb_ch].mode, ledc_ch[rgb_ch].channel));

            printf("mode:%d  channel:%d color:%d\n", ledc_ch[rgb_ch].mode, ledc_ch[rgb_ch].channel, color[rgb_ch]);
        }
    }
}