#include "lang_conect.h"
#include "rgb_led.hpp"
#include "ADC_control/adc.hpp"
#include "open_padlock.hpp"
//#include "base64.hpp"

LED_RGB::RGB_CONTROL rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO, LED_DUTY_RESOLUTION);
// ADC::ADC_CONTROLL adc = ADC::ADC_CONTROLL(ADC1_CHANNEL_7);
PADLOCK::OPEN_PADLOCK padlock_commands = PADLOCK::OPEN_PADLOCK();

void set_rgb_led_interface(int red, int green, int blue)
{
    rgb_led.set_color(red, green, blue);
}

void open_with_password_connect(char *password)
{
    // BASE64().decode();
    padlock_commands.open_with_password(password);
}

void set_led_ble(void)
{
    set_rgb_led_interface(0, 130, 252);
}
void set_led_access_denid(void)
{
    set_rgb_led_interface(2048, 0, 0);
}
void set_led_access_allowed(void)
{
    set_rgb_led_interface(0, 2048, 0);
}