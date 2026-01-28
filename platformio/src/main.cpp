/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#define _TASK_STD_FUNCTION

#include <Arduino.h>

#ifdef ESP32
    #include <AsyncTCP.h>
    #include <Esp.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <ESPAsyncTCP.h>
#endif

#include <SPI.h>
#include <LittleFS.h>
#include <TaskScheduler.h>
#include <Wire.h>
#include <misc/Utils.h>

#include <defaults.h>
#include <display/Alignment.h>
#include <display/DisplayManager.h>
#include <settings/SettingsManager.h>

#include <logging/Logger.h>
#include <network/AppNetworkManager.h>

#include <services/GeolocationService.h>
#include <services/ServiceRegistry.h>
#include <widgets/StaticTextWidget.h>

#include "esp_partition.h"
#include "build_info.h"

AppNetworkManager networkManager;
Scheduler scheduler;

#ifdef DUMP_PARTITIONS
/**
 * Dump the parition table.
 */
void dumpPartitionTable() {
    const esp_partition_t *part = esp_partition_find_first(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, NULL);
    if (part) {
        Serial.printf("App partition: %s at 0x%08x size 0x%x\n", part->label, part->address, part->size);
    }

    // Iterate all:
    esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);

    while (it != NULL) {
        const esp_partition_t *p = esp_partition_get(it);
        Serial.printf("%s (%s): 0x%08x size 0x%x\n", p->label, p->type == ESP_PARTITION_TYPE_APP ? "app" : "data", p->address, p->size);
        it = esp_partition_next(it);
    }

    esp_partition_iterator_release(it);
}
#endif

/**
 * @brief Standard Arduino setup routine.  Called once.
 */
void setup() {
    Serial.begin(115200);

    Serial.printf("Starting version built: %s\n", BUILD_TIMESTAMP_STR);
    Serial.flush();

    #ifdef DUMP_PARTITIONS
        dumpPartitionTable();
    #endif

    if (!LittleFS.begin(true)) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    SettingsManager::get().readSettings();
    ServiceRegistry::get().init(&scheduler);
    DisplayManager &displayManager = DisplayManager::get();
    displayManager.init(&scheduler);
    displayManager.clear();
    
    displayManager.startDisplay();
    networkManager.start();
}

/**
 * @brief Standard Arduino method called repeatedly
 */
void loop() {
    #ifndef LED_CHECK
        networkManager.loop();
        scheduler.execute();
    #else
        DisplayManager &displayManager = DisplayManager::get();

        for (int i = 0; i < NUM_LEDS; i++) {
            displayManager.getGraphics().fillScreen(0);
            displayManager.setLed(i, CRGB::Red);
            displayManager.show();
            delay(500);
        }
    #endif
}
