#include "rgb_led.hpp"

namespace LED_RGB
{

    RGB_LED::RGB_LED(int gpio_r, int gpio_g, int gpio_b, ledc_timer_bit_t led_Duty_Resolution)
    {
        InitializeDefaults();
        SetTimerDutyResolution(led_Duty_Resolution);

        led_controller_r.SetChannel(LEDC_CHANNEL_0);
        led_controller_g.SetChannel(LEDC_CHANNEL_1);
        led_controller_b.SetChannel(LEDC_CHANNEL_2);

        led_controller_r.SetChannelGpio(gpio_r);
        led_controller_g.SetChannelGpio(gpio_g);
        led_controller_b.SetChannelGpio(gpio_b);
    }

    void RGB_LED::rgb_led_set_color(int red, int green, int blue)
    {
        led_controller_r.SetChannelDutyCycle(red);
        led_controller_g.SetChannelDutyCycle(green);
        led_controller_b.SetChannelDutyCycle(blue);
    }

} // namespace RGB_LED
