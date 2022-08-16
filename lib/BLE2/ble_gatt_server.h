
#pragma once
#include "esp_bt_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
//#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"

#include "driver/gpio.h"

#define GATTS_TAG "BLE-TAG-NOTIFY"
#define GATTS_TAG2 "BLE-TAG_ERROR"
#define GATTS_TAG3 "BLE-TAG"
#define GATTS_TAG4 "BLE-Value"

#define TEST_DEVICE_NAME "BLE-Teste2"
#define PROFILE_NUM 1
#define PROFILE_A_APP_ID 0
#define TEST_MANUFACTURER_DATA_LEN 10
#define adv_config_flag (1 << 0)
#define scan_rsp_config_flag (1 << 1)
#define GPIO_IO 2
#define GPIO_OUTPUT_SEL ((1ULL << GPIO_IO))
#define NOTIFY_LED_EVENT (1 << 1)
//#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x01

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40
#define PREPARE_BUF_MAX_SIZE 1024

#ifdef __cplusplus
extern "C"
{
#endif
    void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
    void gatts_profile_a_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
    void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

    void ledTask(void *pvParameters);

    void ble_init2(void);
#ifdef __cplusplus
}
#endif
