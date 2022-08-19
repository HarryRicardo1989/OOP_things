#pragma once

#include "rgb_led.hpp"
#include "GPIO/gpio.hpp"

namespace PADLOCK
{
    class OPEN_PADLOCK
    {
    private:
        Perifericos::GPIO lockpad_close = Perifericos::GPIO();
        Perifericos::GPIO lockpad_open;
        Perifericos::GPIO lockpad_enable;

    public:
        OPEN_PADLOCK(int gpio);
        bool open_with_password(char password, int pass_length);
    };
} // namespace PADLOCK
