#pragma once

#include "Led_Control/led_control.hpp"
#include "Led_Control/led_control_timer.hpp"

namespace LED_RGB
{
    class RGB_LED
    {
    private:
        LED::LED_CONTROL led_controller_r = LED::LED_CONTROL();
        LED::LED_CONTROL led_controller_g = LED::LED_CONTROL();
        LED::LED_CONTROL led_controller_b = LED::LED_CONTROL();
        LED::LED_CONTROL_TIMER led_controller_timer = LED::LED_CONTROL_TIMER();

    public:
        RGB_LED(int gpio_r, int gpio_g, int gpio_b);
        void rgb_led_set_color(int red, int green, int blue);
    };

} // namespace RGB
