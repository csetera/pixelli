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
#include <SPIFFS.h>
#include <TaskScheduler.h>
#include <Wire.h>

#include <defaults.h>
#include <display/Alignment.h>
#include <display/DisplayManager.h>
#include <logging/Logger.h>
#include <network/NetworkManager.h>
#include <misc/Utils.h>

#include <services/GeolocationService.h>
#include <services/ServiceRegistry.h>

#include <utils/SettingsManager.h>
#include <widgets/StaticTextWidget.h>

Scheduler scheduler;
SettingsManager settingsManager;
NetworkManager networkManager(settingsManager);

/**
 * @brief Standard Arduino setup routine.  Called once.
 */
void setup() {
    Serial.begin(115200);

    char build_timestamp[FORMATTED_BUILD_TIMESTAMP_LENGTH];
    Utils::formatBuildTimestamp(build_timestamp);
    Serial.printf("Starting version built: %s\n", build_timestamp);

    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    settingsManager.begin();
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
    networkManager.loop();
    scheduler.execute();
}
