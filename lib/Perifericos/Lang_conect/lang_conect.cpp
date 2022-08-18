#include "lang_conect.h"

LED_RGB::RGB_CONTROL rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO, LED_DUTY_RESOLUTION);
// ADC::ADC_CONTROLL adc = ADC::ADC_CONTROLL(ADC1_CHANNEL_7);

extern "C" void set_rgb_led_interface(int red, int blue, int green);

void set_rgb_led_interface(int red, int green, int blue)
{
    rgb_led.set_color(red, green, blue);
}
