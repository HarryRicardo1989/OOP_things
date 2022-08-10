
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

#define GATTS_TAG "BLE-TAG"
#define TEST_DEVICE_NAME "BLE-Teste"

#define GATTS_SERVICE_UUID 0x2800
#define GATTS_CHAR_UUID 0x0002
#define GATTS_DESCR_UUID 0x1801
#define GATTS_NUM_HANDLE 4

#define GATTS_SERVICE_UUID_TEST_B 0x00EE
#define GATTS_CHAR_UUID_TEST_B 0xEE01
#define GATTS_DESCR_UUID_TEST_B 0x2222
#define GATTS_NUM_HANDLE_TEST_B 4

#define TEST_MANUFACTURER_DATA_LEN 17

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40
#define PREPARE_BUF_MAX_SIZE 1024
#define adv_config_flag (1 << 0)
#define scan_rsp_config_flag (1 << 1)

#define PROFILE_NUM 1
#define PROFILE_A_APP_ID 0
#define PROFILE_B_APP_ID 1
/// Declare the static function
#ifdef __cplusplus
extern "C"
{
#endif

    void ble_init1(void);

#ifdef __cplusplus
}
#endif
