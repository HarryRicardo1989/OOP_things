
#pragma once

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

#define GATTS_TAG1 "BLE-TAG-NOTIFY"
#define GATTS_TAG2 "BLE-TAG_ERROR"
#define GATTS_TAG3 "BLE-TAG"
#define GATTS_TAG4 "BLE-Value"

#define TEST_DEVICE_NAME "BLE-Teste"

#define GATTS_SERVICE_UUID 0x2800 // 0000B5A3F393E0A9E50E24DCCA9E
#define GATTS_CHAR_UUID 0x2801
#define GATTS_DESCR_UUID 0x2802
#define GATTS_NUM_HANDLE 4

#define TEST_MANUFACTURER_DATA_LEN 17

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40
#define PREPARE_BUF_MAX_SIZE 1024
#define adv_config_flag (1 << 0)
#define scan_rsp_config_flag (1 << 1)

#define PROFILE_NUM 1
#define PROFILE_A_APP_ID 0

#ifdef __cplusplus
extern "C"
{
#endif

    void ble_init1(void);
    void pass_veryfy(char *password, uint8_t pass_length);

#ifdef __cplusplus
}
#endif
