#include "stdio.h"

#include "task.h"
#include "rom/ets_sys.h"
#include "rgb_led.hpp"

#include "ADC_control/adc.hpp"

#define RGB_LED_RED_GPIO 21
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 18

/**
 * LEDC_TIMER_8_BIT = 255
 * LEDC_TIMER_9_BIT = 512
 * LEDC_TIMER_10_BIT = 1024
 * LEDC_TIMER_12_BIT = 4096
 * LEDC_TIMER_13_BIT = 8192
 * LEDC_TIMER_14_BIT = 16384
 */
#define LED_DUTY_RESOLUTION LEDC_TIMER_12_BIT

extern "C"
{
    void app_main(void);
}
LED_RGB::RGB_CONTROL rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO, LED_DUTY_RESOLUTION);
ADC::ADC_CONTROLL adc = ADC::ADC_CONTROLL(ADC1_CHANNEL_7);

void app_main(void)
{
    rgb_led.set_color(10, 0, 0);

    xTaskCreatePinnedToCore(vTask_led, "TASK LED", configMINIMAL_STACK_SIZE + 1024, NULL, 10, &task_led_handle, 0);
    xTaskCreatePinnedToCore(vTask_print, "TASK Print", configMINIMAL_STACK_SIZE + 1024, NULL, 1, &task_print_handle, 1);

    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTask_led(void *pvParameters)
{
    while (true)
    {
        printf("adc pin35:%d \n", adc.GetRaw());
        printf("Volt pin35:%d \n", adc.GetVoltage());
        printf("%d\n", ets_get_cpu_frequency());
        // vTaskDelay(1000 / portTICK_PERIOD_MS);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void vTask_print(void *pvParameters)
{
    while (true)
    {
        rgb_led.set_color(0, 0, adc.GetRaw());
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}