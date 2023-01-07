/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "SettingsManager.h"

#include <EEPROM.h>

SettingsManager::SettingsManager() {
    clearSettings();
}

/**
 * @brief Start up the SettingsManager instance.
 *
 * @return true
 * @return false
 */
bool SettingsManager::begin() {
    Serial.printf("Size: %d\n", sizeof(Settings));
    return EEPROM.begin(sizeof(Settings));
}

/**
 * @brief Clear out the settings from tHe EEPROM.
 */
void SettingsManager::clearSettings() {
    memset(&settings, 0, sizeof(Settings));
}

/**
 * @brief Read all settings in from EEPOM.
 *
 * @return true
 * @return false
 */
bool SettingsManager::readSettings() {
    EEPROM.get(0, settings);
    return isIntialized();
}

/**
 * @brief Clear all settings from EEPROM.
 */
void SettingsManager::reset() {
    clearSettings();
    writeSettings();
}

/**
 * @brief Write out the current settings to the EEPROM
 */
void SettingsManager::writeSettings() {
    settings.magic = MAGIC_KEY;
    settings.version = VERSION;

    EEPROM.put(0, settings);
    EEPROM.commit();
}
