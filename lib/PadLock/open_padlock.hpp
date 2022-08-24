#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Lang_conect/lang_conect.h"
#include "GPIO/gpio.hpp"
#include "string.h"

namespace PADLOCK
{
    class OPEN_PADLOCK
    {
    private:
        const uint8_t count_open = 10;
        const uint8_t time_open_padlock = 20;
        const uint8_t count_close = 10;
        const uint8_t time_close_padlock = 20;

        const uint8_t time_wait_padlock = 50;

        const uint8_t count_led = 3;
        const uint8_t time_led_open = 50;

        const char *secret = "assaplk";

        Perifericos::GPIO lockpad_close = Perifericos::GPIO(GPIO_NUM_27, GPIO_MODE_OUTPUT, GPIO_PULLDOWN_ONLY);
        Perifericos::GPIO lockpad_open = Perifericos::GPIO(GPIO_NUM_26, GPIO_MODE_OUTPUT, GPIO_PULLDOWN_ONLY);
        Perifericos::GPIO lockpad_enable = Perifericos::GPIO(GPIO_NUM_25, GPIO_MODE_OUTPUT, GPIO_PULLDOWN_ONLY);

        /**
         * @brief blink led command
         *
         * @param blink_count the counter times to blink the led
         * @param time_delay the time of delay between state of led
         */
        void blink_led_allowed(uint8_t blink_count, uint time_delay);
        void blink_led_denied(uint8_t blink_count, uint time_delay);

        /**
         * @brief routine to open padlock with the motor
         *
         * @param pulse_count
         * @param time_delay
         */
        void padlock_open_routine(uint8_t pulse_count, uint time_delay);
        void padlock_close_routine(uint8_t pulse_count, uint time_delay);

    public:
        OPEN_PADLOCK();
        void open_with_password(char *password);
    };
} // namespace PADLOCK
