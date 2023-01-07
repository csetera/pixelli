/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <Esp.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <utils/SettingsManager.h>

/**
 * @brief Separate the network management functionality
 */
class NetworkManager {
public:
    NetworkManager(SettingsManager &settingsManager) :
        settingsManager(settingsManager),
        webServer(80),
        wsSerial("/ws_serial") { }

    /**
     * @brief Start up the network.
     */
    void start();

    /**
     * @brief Handle a loop call as necessary
     */
    void loop();

    /**
     * @brief Get the Web Server object
     *
     * @return AsyncWebServer&
     */
    AsyncWebServer& getWebServer() {
        return webServer;
    }

private:
    static const long   maxConnectionWaitMillis = 30 * 1000;
    SettingsManager&    settingsManager;
    AsyncWebServer      webServer;
    AsyncWebSocket      wsSerial;

    double              lastLoggedOtaPercentage;

    WiFiEventId_t       eventID;

    void onWifiConnected();
    void onWifiDisconnected();

    void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);
    void registerHandlers();
    void configureOTAUpdates();

    void smartConfig();
    bool waitForConnection();
};
