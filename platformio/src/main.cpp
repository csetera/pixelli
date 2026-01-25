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

#include "build_info.h"

AppNetworkManager networkManager;
Scheduler scheduler;

/**
 * @brief Standard Arduino setup routine.  Called once.
 */
void setup() {
    Serial.begin(115200);

    Serial.printf("Starting version built: %s\n", BUILD_TIMESTAMP_STR);
    Serial.flush();

    #ifndef WOKWI
    if (!LittleFS.begin(true)) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    SettingsManager::get().readSettings();
    #endif

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
