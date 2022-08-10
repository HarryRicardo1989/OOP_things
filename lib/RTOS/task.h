#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task_led_handle = NULL;
TaskHandle_t task_print_handle = NULL;

void vTask_led(void *pvParameters);
void vTask_print(void *pvParameters);