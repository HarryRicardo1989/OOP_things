// default C/C++ lib
#include "stdio.h"

// project libs

#include "task.h"
//#include "rom/ets_sys.h"
#include "rgb_led.hpp"
#include "ble_gatt.h"
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
#define LED_DUTY_RESOLUTION LEDC_TIMER_8_BIT

extern "C"
{
    void app_main(void);
}
LED_RGB::RGB_CONTROL rgb_led(RGB_LED_RED_GPIO, RGB_LED_GREEN_GPIO, RGB_LED_BLUE_GPIO, LED_DUTY_RESOLUTION);
ADC::ADC_CONTROLL adc = ADC::ADC_CONTROLL(ADC1_CHANNEL_7);

void app_main(void)
{
    rgb_led.set_color(10, 0, 0);
    battery_value(adc.GetVoltage());
    xTaskCreatePinnedToCore(vTask_led, "TASK LED", VTASK_STACK_SIZE_LED, NULL, VTASK_PRIORITY_LED, &task_led_handle, VTASK_CORE_ID_LED);
    xTaskCreatePinnedToCore(vTask_battery_voltage, "TASK BATTERY VOLTAGE", VTASK_STACK_SIZE_BATTERY_VOLTAGE, NULL, VTASK_PRIORITY_BATTERY_VOLTAGE, &task_battery_voltage_handle, VTASK_CORE_ID_BATTERY_VOLTAGE);
    ble_init1();
    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTask_led(void *pvParameters)
{
    while (true)
    {
        rgb_led.set_color(0, 160, 208);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void vTask_battery_voltage(void *pvParameters)
{
    while (true)
    {
        battery_value(adc.GetVoltage());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}