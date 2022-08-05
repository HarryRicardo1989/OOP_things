
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include "driver/ledc.h"
// RGB LED GPIOs
#define RGB_LED_RED_GPIO 21
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 18

// RGB LED color mix channels
#define RGB_LED_CHANNEL_NUM 3

	// RGB LED configuration
	typedef struct
	{
		int channel;
		int gpio;
		int mode;
		int timer_index;
	} ledc_info_t;
	ledc_info_t ledc_ch[RGB_LED_CHANNEL_NUM];

	void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue);

#ifdef __cplusplus
}
#endif
