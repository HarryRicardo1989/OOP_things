// default C/C++ lib
#include "stdio.h"

// project libs

#include "task.h"
//#include "rom/ets_sys.h"
#include "rgb_led.hpp"
#include "ble_gatt.h"
#include "ADC_control/adc.hpp"
//#include "wifi_app.h"
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include "Lang_conect/lang_conect.h"

extern "C"
{
    void app_main(void);
}
ADC::ADC_CONTROLL adc = ADC::ADC_CONTROLL(ADC1_CHANNEL_7);
void app_main(void)
{

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    battery_value(adc.GetVoltage());
    // xTaskCreatePinnedToCore(vTask_led, "TASK LED", VTASK_STACK_SIZE_LED, NULL, VTASK_PRIORITY_LED, &task_led_handle, VTASK_CORE_ID_LED);
    xTaskCreatePinnedToCore(vTask_battery_voltage, "TASK BATTERY VOLTAGE", VTASK_STACK_SIZE_BATTERY_VOLTAGE, NULL, VTASK_PRIORITY_BATTERY_VOLTAGE, &task_battery_voltage_handle, VTASK_CORE_ID_BATTERY_VOLTAGE);
    set_rgb_led_interface(0, 130, 252);
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
        set_rgb_led_interface(0, 0, adc.GetRaw());
        // rgb_led.set_color(0, 130, 252); //azul bluetooth
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
