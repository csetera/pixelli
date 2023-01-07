/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <Arduino.h>

/**
 * @brief Provides a wrapper for EEPROM based storage of system settings.
 * In particular, provides a location for storing Wifi connection information.
 */
class SettingsManager {
public:
    SettingsManager();

    /**
     * @brief Start up the SettingsManager instance.
     *
     * @return true
     * @return false
     */
    bool begin();

    /**
     * @brief Return the Wifi password.
     *
     * @return const char*
     */
    const char* getWIfiPass() {
        return settings.wifi_pass;
    }

    /**
     * @brief Return the Wifi SSID
     *
     * @return const char*
     */
    const char* getWifiSsid() {
        return settings.wifi_ssid;
    }

    /**
     * @brief Return a boolean indicating whether the settings have been initialized.
     *
     * @return true
     * @return false
     */
    bool isIntialized() {
        return (settings.magic = MAGIC_KEY) && (settings.version == VERSION);
    }

    /**
     * @brief Set the Wifi password
     *
     * @param pass
     */
    void setWifiPass(const char *pass) {
        strncpy(settings.wifi_pass, pass, STRING_LENGTH);
    }

    /**
     * @brief Set the Wifi SSID
     *
     * @param ssid
     */
    void setWifiSsid(const char *ssid) {
        strncpy(settings.wifi_ssid, ssid, STRING_LENGTH);
    }

    /**
     * @brief Read all settings in from EEPOM.
     *
     * @return true
     * @return false
     */
    bool readSettings();

    /**
     * @brief Clear all settings from EEPROM.
     */
    void reset();

    /**
     * @brief Write out the current settings to the EEPROM
     */
    void writeSettings();

private:
    static const uint8_t   STRING_LENGTH = 40;
    static const uint32_t  MAGIC_KEY = 0xB01DFACE;
    static const uint8_t   VERSION = 1;

    struct __attribute ((packed)) Settings {
        uint32_t    magic;
        uint8_t     version;
        char        wifi_ssid[STRING_LENGTH];
        char        wifi_pass[STRING_LENGTH];
    };

    Settings settings;

    /**
     * @brief Clear out the settings from tHe EEPROM.
     */
    void clearSettings();
};
