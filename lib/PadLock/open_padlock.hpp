#pragma once

#include "rgb_led.hpp"

namespace PADLOCK
{
    class OPEN_PADLOCK
    {
    private:
    public:
        OPEN_PADLOCK(int gpio);
        bool open_with_password(char password, int pass_length);
    };
} // namespace PADLOCK
