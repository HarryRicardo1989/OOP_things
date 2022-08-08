#pragma once

#include "Led_Control/led_control.hpp"
#include "Led_Control/led_control_timer.hpp"

namespace LED_RGB
{
    /**
     * @brief Construct a new rgb led object
     *
     * @param gpio_r GPIO pin led Red
     * @param gpio_g GPIO pin led Green
     * @param gpio_b GPIO pin led Blue
     * @param led_Duty_Resolution LEDC PWM duty resolution of bits
     * LEDC_TIMER_8_BIT = 255
     * LEDC_TIMER_9_BIT = 512
     * LEDC_TIMER_10_BIT = 1024
     * LEDC_TIMER_12_BIT = 4096
     * LEDC_TIMER_13_BIT = 8192
     * LEDC_TIMER_14_BIT = 16384
     * LEDC_TIMER_15_BIT = 32768
     * LEDC_TIMER_16_BIT = 65536
     */
    class RGB_CONTROL : Perifericos::LED_CONTROL_TIMER
    {
    private:
        Perifericos::LED_CONTROL led_controller_r = Perifericos::LED_CONTROL();
        Perifericos::LED_CONTROL led_controller_g = Perifericos::LED_CONTROL();
        Perifericos::LED_CONTROL led_controller_b = Perifericos::LED_CONTROL();
        // LED::LED_CONTROL_TIMER led_controller_timer = LED::LED_CONTROL_TIMER();

    public:
        /**
         * @brief Construct a new rgb led object
         *
         *
         * @param gpio_r GPIO pin led Red
         * @param gpio_g GPIO pin led Green
         * @param gpio_b GPIO pin led Blue
         * @param led_Duty_Resolution LEDC PWM duty resolution of bits
         * LEDC_TIMER_8_BIT = 255
         * LEDC_TIMER_9_BIT = 512
         * LEDC_TIMER_10_BIT = 1024
         * LEDC_TIMER_12_BIT = 4096
         * LEDC_TIMER_13_BIT = 8192
         * LEDC_TIMER_14_BIT = 16384
         * LEDC_TIMER_15_BIT = 32768
         * LEDC_TIMER_16_BIT = 65536
         */
        RGB_CONTROL(int gpio_r, int gpio_g, int gpio_b, ledc_timer_bit_t led_Duty_Resolution);

        /**
         * @brief Method for change duty cycle of each led
         *
         *
         * @param red   PWM duty cycle uint32_t but depends of led_Duty_Resolution
         * @param green PWM duty cycle uint32_t but depends of led_Duty_Resolution
         * @param blue  PWM duty cycle uint32_t but depends of led_Duty_Resolution
         */
        void set_color(uint32_t red, uint32_t green, uint32_t blue);
    };

} // namespace RGB
