/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "esp_chip_info.h"
//#include "esp_flash.h"
//#include "esp_system.h"

void app_main(void)
{
    for (int i = 1; i <= 10; i++) {
        printf("Hello world %d\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    fflush(stdout);
    esp_restart();
}
