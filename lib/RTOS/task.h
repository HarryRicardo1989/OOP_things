#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task_led_handle = NULL;
TaskHandle_t task_print_handle = NULL;
TaskHandle_t task_battery_voltage_handle = NULL;

#define VTASK_CORE_ID_LED 1
#define VTASK_PRIORITY_LED 10
#define VTASK_STACK_SIZE_LED configMINIMAL_STACK_SIZE + 1024

//#define VTASK_CORE_ID_PRINT 1
//#define VTASK_PRIORITY_PRINT 10
//#define VTASK_STACK_SIZE_PRINT configMINIMAL_STACK_SIZE + 1024

#define VTASK_CORE_ID_BATTERY_VOLTAGE 1
#define VTASK_PRIORITY_BATTERY_VOLTAGE 5
#define VTASK_STACK_SIZE_BATTERY_VOLTAGE configMINIMAL_STACK_SIZE + 1024

void vTask_led(void *pvParameters);
// void vTask_print(void *pvParameters);
void vTask_battery_voltage(void *pvParameters);
