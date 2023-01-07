/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <AsyncJson.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>

#include <defaults.h>
#include <logging/Logger.h>
#include <misc/Utils.h>

#ifdef ESP32
// https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html
#include <WiFi.h>
#include <WiFiClientSecure.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include "NetworkManager.h"

/**
 * @brief Handle template variable expansion for the captive portal.
 *
 * @param var The variable to be replaced.
 * @return String
 */
String captivePortalProcessor(const String &var) {
    if (var == "HELLO_FROM_TEMPLATE")
        return F("Hello world!");
    return String();
}

/**
 * @brief Incoming websocket event handler
 *
 * @param server
 * @param client
 * @param type
 * @param arg
 * @param data
 * @param len
 */
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.println("WS_EVT_CONNECT");
            break;

        case WS_EVT_DISCONNECT:
            Serial.println("WS_EVT_DISCONNECT");
            break;

        case WS_EVT_PONG:
            Serial.println("WS_EVT_PONG");
            break;

        case WS_EVT_ERROR:
            Serial.println("WS_EVT_ERROR");
            break;

        case WS_EVT_DATA:
            Serial.println("WS_EVT_DATA");
            break;
    }
}

/**
 * @brief Handle Espressif Smartconfig to configure SSID and password.
 * See https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_smartconfig.html
 * for more information.
 */
void NetworkManager::smartConfig() {
    do {
        Serial.println("Starting SmartConfig");

        WiFi.beginSmartConfig();

        while (!WiFi.smartConfigDone()) {
            delay(1000);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("SmartConfig received.");

        if (waitForConnection()) {
            Serial.printf("Smartconfig value: %s/%s\n", WiFi.SSID().c_str(), WiFi.psk().c_str());
            settingsManager.setWifiPass(WiFi.psk().c_str());
            settingsManager.setWifiSsid(WiFi.SSID().c_str());
            Serial.println("Writing out settings");
            settingsManager.writeSettings();
        }

    } while (WiFi.status() != WL_CONNECTED);
}

/**
 * @brief Start up configure the networking stack
 */
void NetworkManager::start() {
    // Calculate a unique hostname
    auto hostname = String("pixelli-");
    hostname.concat(String((unsigned long)ESP.getEfuseMac(), HEX));
    WiFi.setHostname(hostname.c_str());

    WiFi.mode(WIFI_STA);
    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info) {
        this->onWifiEvent(event, info);
    });

    registerHandlers();
    configureOTAUpdates();

    settingsManager.readSettings();
    if (settingsManager.isIntialized()) {
        Serial.printf("EEPROM was intialized SSID: %s; Pass: %s\n", settingsManager.getWifiSsid(), settingsManager.getWIfiPass());
        WiFi.begin(settingsManager.getWifiSsid(), settingsManager.getWIfiPass());
        if (!waitForConnection()) {
            smartConfig();
        }
    } else {
        smartConfig();
    }

    webServer.begin();
}

/**
 * @brief Wait for a Wifi connection.  Returns a boolean
 * indicating whether a connection was made.
 *
 * @return true
 * @return false
 */
bool NetworkManager::waitForConnection() {
    long beginConnectionMillis = millis();
    long connectionAttemptMillis = 0;

    Serial.println("Waiting for WiFi");
    do {
        delay(500);
        Serial.print(".");
        connectionAttemptMillis = millis() - beginConnectionMillis;
    } while ((connectionAttemptMillis < maxConnectionWaitMillis) && (WiFi.status() != WL_CONNECTED));

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi Connected.");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        return true;
    } else {
        Serial.println("WiFi did not connect");

        return false;
    }
}

/**
 * @brief Handle the recurring loop.
 */
void NetworkManager::loop() {
    ArduinoOTA.handle();
}

/**
 * @brief Handle an info requerst
 *
 * @param request
 */
void handleInfoRequest(AsyncWebServerRequest *request) {
    Logger::get().println("Received info request");

    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonVariant &root = response->getRoot();
    JsonObject obj = root.to<JsonObject>();

    char build_timestamp[FORMATTED_BUILD_TIMESTAMP_LENGTH];
    Utils::formatBuildTimestamp(build_timestamp);
    obj[F("Build")] = build_timestamp;

    obj["IpAddr"] = WiFi.localIP();
    obj["SdkVersion"] = ESP.getSdkVersion();

    JsonObject sketch = obj.createNestedObject("sketch");
    sketch["Size"] = ESP.getSketchSize();
    sketch["FreeSpace"] = ESP.getFreeSketchSpace();

    JsonObject heap = obj.createNestedObject("Heap");
    heap["Size"] = ESP.getHeapSize(); //total heap size
    heap["Free"] = ESP.getFreeHeap(); //available heap
    heap["MinFree"] = ESP.getMinFreeHeap(); //lowest level of free heap since boot
    heap["MaxAlloc"] = ESP.getMaxAllocHeap(); //largest block of heap that can be allocated at once

    JsonObject psram = obj.createNestedObject("Psram");
    psram["Size"] = ESP.getPsramSize();
    psram["Free"] = ESP.getFreePsram();
    psram["MinFree"] = ESP.getMinFreePsram();
    psram["MaxAlloc"] = ESP.getMaxAllocPsram();

    JsonObject chip = obj.createNestedObject("Chip");
    chip["Model"] = ESP.getChipModel();
    chip["Revision"] = ESP.getChipRevision();
    chip["Cores"] = ESP.getChipCores();

    JsonObject flash = obj.createNestedObject("Flash");
    flash["ChipSpeed"] = ESP.getFlashChipSpeed();
    flash["ChipMode"] = ESP.getFlashChipMode();

    response->setLength();
    request->send(response);
}

/**
 * @brief Handle a request for a network scan for available
 * wireless networks.
 *
 * @param request The incoming reuquest information.
 */
void handleNetworksRequest(AsyncWebServerRequest *request) {
    Logger::get().println("Received networks request");
    int n = WiFi.scanNetworks();

    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonVariant &root = response->getRoot();
    JsonArray array = root.to<JsonArray>();

    for (int i = 0; i < n; i++) {
        JsonObject obj = array.createNestedObject();
        obj["CHANNEL"] = WiFi.channel(i);
        obj["ENC_TYPE"] = WiFi.encryptionType(i);
        obj["RSSI"] = WiFi.RSSI(i);
        obj["SSID"] = WiFi.SSID(i);
    }

    response->setLength();
    request->send(response);

    WiFi.scanDelete();
}

/**
 * @brief Handler for Wifi connected events
 */
void NetworkManager::onWifiConnected() {
    Serial.println("onWifiConnected");

    Logger &logger = Logger::get();
    logger.publishTo(&wsSerial);

    if (!MDNS.begin(MDNS_NAME)) {
        Serial.println("Error setting up MDNS responder!");
        delay(1000);
    }

    MDNS.addService("http", "tcp", 80);
    logger.println("mDNS responder started");

    ArduinoOTA.begin();
}

/**
 * @brief Handler for Wifi disconnected events
 */
void NetworkManager::onWifiDisconnected() {
    Serial.println("onWifiDisconnected");

    Logger &logger = Logger::get();
    logger.publishTo(nullptr);

    ArduinoOTA.end();
    MDNS.end();
}

/**
 * @brief Handler for Wifi events
 *
 * @param event
 * @param info
 */
void NetworkManager::onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            onWifiConnected();
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            onWifiDisconnected();
            break;

        default:
            Logger::get().printf("Received Wifi Event: %d\n", event);
            break;
    }
}

/**
 * @brief Configure the web server
 */
void NetworkManager::registerHandlers() {
    Serial.println("Registering web handlers");

    webServer.on("/api/info", handleInfoRequest);
    webServer.on("/api/networks", handleNetworksRequest);

    webServer.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        Serial.println("Root webrequest");

        const char *filename = ON_AP_FILTER(request) ? "/captive_index.html" : "/index.html";
        request->send(SPIFFS, filename);
    });

    webServer.onNotFound([this](AsyncWebServerRequest *request) {
        Serial.println("Not found webrequest");
        if (ON_AP_FILTER(request)) {
            request->send(SPIFFS, "/captive_index.html");
        } else {
            // Otherwise, just 404
            request->send(404, "text/plain", "Not found");
        }
    });

    wsSerial.onEvent(onWsEvent);
    webServer.addHandler(&wsSerial);
}

/**
 * @brief Setup for OTA updates
 */
void NetworkManager::configureOTAUpdates() {
    Logger::get().println(F("Configuring OTA Updates"));

    ArduinoOTA.setHostname(MDNS_NAME);
    ArduinoOTA.setPassword(OTA_PASSWORD);

    ArduinoOTA.onStart([this]() {
        lastLoggedOtaPercentage = -1.0;
        Logger::get().println((ArduinoOTA.getCommand() == 0) ?
            F("OTA firmware update starting") :
            F("OTA filesystem update starting"));
    });

    ArduinoOTA.onEnd([]() {
        Logger::get().println(F("OTA Complete"));
    });

    ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
        uint percent_complete = (uint) ((double) progress / ((double) total / 100));
        if ((percent_complete % 10) == 0) {
            if (percent_complete > lastLoggedOtaPercentage) {
                lastLoggedOtaPercentage = percent_complete;
                Logger::get().printf("OTA Progress: %u%%\n", percent_complete);
            }
        }
    });

    ArduinoOTA.onError([](ota_error_t error) {
        switch (error) {
            case OTA_AUTH_ERROR:
                Logger::get().println(F("OTA - Auth failed\n"));
                break;

            case OTA_BEGIN_ERROR:
                Logger::get().println(F("OTA - Begin failed"));
                break;

            case OTA_CONNECT_ERROR:
                Logger::get().println(F("OTA - Connect failed"));
                break;

            case OTA_RECEIVE_ERROR:
                Logger::get().println(F("OTA - Receive failed"));
                break;

            case OTA_END_ERROR:
                Logger::get().println(F("OTA - End failed"));
                break;

            default:
                Logger::get().printf("OTA - Unknown OTA error: %u\n", error);
        }
    });

    Logger::get().println(F("OTA configured"));
}
