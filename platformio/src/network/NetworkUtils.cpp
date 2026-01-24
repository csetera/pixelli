/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "NetworkUtils.h"

#include <HTTPClient.h>
#include <logging/Logger.h>

#ifdef ESP32
// https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

static WiFiClient wifiClientPlain;
static WiFiClientSecure wifiClientSecure;
static SemaphoreHandle_t clientMutex = xSemaphoreCreateMutex();

/**
 * @brief Retrieve a payload from the specified URL.
 *
 * @param url
 * @param receiver
 */
void NetworkUtils::httpGet(String& url, StreamReceiver receiver) {
    xSemaphoreTake(clientMutex, portMAX_DELAY); 

    WiFiClient* wifiClient = nullptr;
    if (url.startsWith("https:")) {
        wifiClient = &wifiClientSecure;
        wifiClientSecure.setInsecure();
    } else {
        wifiClient = &wifiClientPlain;
    }

    // Set up the REST client to make it easy to handle JSON
    HTTPClient http;
    http.useHTTP10(true);

    // Set up the REST call
     if (!http.begin(*wifiClient, url)) {
        xSemaphoreGive(clientMutex);
        return;
    }

    // Make the REST call
    Logger::get().println("Executing GET request");
    int httpResponseCode = http.GET();
    Logger::get().printf("GET request result code: %d\n", httpResponseCode);

    receiver(httpResponseCode, http.getStream());

    http.end();
    wifiClient->stop();
    xSemaphoreGive(clientMutex);
}
