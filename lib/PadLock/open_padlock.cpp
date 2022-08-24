#include "open_padlock.hpp"

namespace PADLOCK
{
    OPEN_PADLOCK::OPEN_PADLOCK()
    {
        // blink_led(blink_init, 100);
    }

    void OPEN_PADLOCK::open_with_password(char *password)
    {
        if (strcmp(password, secret) == 0)
        {
            blink_led_allowed(count_led, time_led_open);
            padlock_open_routine(count_open, time_open_padlock);
            vTaskDelay(time_wait_padlock / portTICK_PERIOD_MS);
            padlock_close_routine(count_close, time_close_padlock);
        }
        else
        {

            blink_led_denied(3, 100);
            return;
        }
    }

    void OPEN_PADLOCK::blink_led_allowed(uint8_t blink_count, uint time_delay)
    {
        for (int i = 0; i <= blink_count; i++)
        {
            set_led_access_allowed();
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
            set_led_ble();
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
        }
    }
    void OPEN_PADLOCK::blink_led_denied(uint8_t blink_count, uint time_delay)
    {
        for (int i = 0; i <= blink_count; i++)
        {
            set_led_access_denid();
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
            set_led_ble();
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
        }
    }

    void OPEN_PADLOCK::padlock_open_routine(uint8_t pulse_count, uint time_delay)
    {
        lockpad_enable.set_level(true);
        for (int i = 0; i <= pulse_count; i++)
        {
            lockpad_open.set_level(true);
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
            lockpad_open.set_level(false);
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
        }
        lockpad_enable.set_level(false);
    }

    void OPEN_PADLOCK::padlock_close_routine(uint8_t pulse_count, uint time_delay)
    {
        lockpad_enable.set_level(true);
        for (int i = 0; i <= pulse_count; i++)
        {
            lockpad_close.set_level(true);
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
            lockpad_close.set_level(false);
            vTaskDelay(time_delay / portTICK_PERIOD_MS);
        }
        lockpad_enable.set_level(false);
    }

} // namespace GPIO
