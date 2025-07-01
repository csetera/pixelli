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

#ifndef ESP32_QEMU
#include <defaults.h>
#include <display/Alignment.h>
#include <display/DisplayManager.h>
#include <logging/Logger.h>
#include <network/AppNetworkManager.h>

#include <services/GeolocationService.h>
#include <services/ServiceRegistry.h>

#include <settings/SettingsManager.h>
#include <widgets/StaticTextWidget.h>
#endif 

#ifdef ESP32_QEMU
    #include "esp_task_wdt.h"
    #include <qemu_matrix/QEMU_NeoMatrix.h>

    #define LED_PIXEL_SIZE 20
    #define GUTTER_PIXEL_SIZE 4
    #define MATRIX_WIDTH 32
    #define MATRIX_HEIGHT 16

    #define WIDTH 800
    #define HEIGHT 400

    QEMU_NeoMatrix qemu_matrix(MATRIX_WIDTH, MATRIX_HEIGHT, LED_PIXEL_SIZE, GUTTER_PIXEL_SIZE);
#else
Scheduler scheduler;
AppNetworkManager networkManager;
#endif

/**
 * @brief Standard Arduino setup routine.  Called once.
 */
void setup() {
    #ifdef ESP32_QEMU
        // Give QEMU cache time to stabilize
        delay(100);
    #endif

    Serial.begin(115200);

    #ifdef ESP32_QEMU
        // Disable watchdogs that might interfere
        esp_task_wdt_deinit();
        
        // Explicit yield to ensure cache coherency
        yield();
    #endif

    char build_timestamp[FORMATTED_BUILD_TIMESTAMP_LENGTH];
    Utils::formatBuildTimestamp(build_timestamp);
    Serial.printf("Starting version built: %s\n", build_timestamp);

    #ifdef ESP32_QEMU
    qemu_matrix.begin();
    #else
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
    #endif
}

/**
 * @brief Standard Arduino method called repeatedly
 */
void loop() {
    #ifdef ESP32_QEMU
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            qemu_matrix.startWrite();
            qemu_matrix.clear();
            qemu_matrix.drawPixel(x, y, RGB565_RED);
            qemu_matrix.endWrite();

            delay(100);
        }
    }
    #else
    networkManager.loop();
    scheduler.execute();
    #endif
}
