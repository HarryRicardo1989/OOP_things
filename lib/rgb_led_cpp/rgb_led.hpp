#pragma once

#include "Led_Control/led_control.hpp"
#include "Led_Control/led_control_timer.hpp"

namespace LED_RGB
{
    class RGB_LED : LED::LED_CONTROL_TIMER
    {
    private:
        LED::LED_CONTROL led_controller_r = LED::LED_CONTROL();
        LED::LED_CONTROL led_controller_g = LED::LED_CONTROL();
        LED::LED_CONTROL led_controller_b = LED::LED_CONTROL();
        // LED::LED_CONTROL_TIMER led_controller_timer = LED::LED_CONTROL_TIMER();

    public:
        /**
         * @brief Construct a new rgb led object
         *
         * @param gpio_r GPIO
         * @param gpio_g
         * @param gpio_b
         * @param led_Duty_Resolution
         */
        RGB_LED(int gpio_r, int gpio_g, int gpio_b, ledc_timer_bit_t led_Duty_Resolution);
        void rgb_led_set_color(int red, int green, int blue);
    };

} // namespace RGB
