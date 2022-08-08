#pragma once

#include "led_control.hpp"
#include "driver/ledc.h"
#include "esp_err.h"

namespace LED
{
    class LED_CONTROL_TIMER
    {
    private:
        ledc_timer_config_t _timer_config;
        void _set_defaults();

    protected:
        LED_CONTROL_TIMER(void);

        esp_err_t InitializeDefaults(void);
        esp_err_t SetTimerSpeedMode(ledc_mode_t speed_mode);
        esp_err_t SetTimerDutyResolution(ledc_timer_bit_t duty_resolution);
        esp_err_t SetTimerSource(ledc_timer_t timer_num);
        esp_err_t SetTimerFrequency(uint32_t freq_hz);
        esp_err_t SetTimerClockSource(ledc_clk_cfg_t clk_cfg);
        esp_err_t SetTimerAll(ledc_mode_t speed_mode,
                              ledc_timer_bit_t duty_resolution,
                              ledc_timer_t timer_num,
                              uint32_t freq_hz,
                              ledc_clk_cfg_t clk_cfg);

    }; // Class CppLedTimer

} // namespace RGB
