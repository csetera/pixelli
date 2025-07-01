/**********************************************************************************
 * Copyright (C) 2025 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#ifdef ESP32
#include <Esp.h>
#endif

// ESP32 3.0.0 Breaking changes
#ifdef ESP_ARDUINO_VERSION_MAJOR
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
    #define SYSTEM_EVENT_STA_LOST_IP ARDUINO_EVENT_WIFI_STA_LOST_IP
    #define SYSTEM_EVENT_STA_GOT_IP ARDUINO_EVENT_WIFI_STA_GOT_IP
    #define SYSTEM_EVENT_STA_DISCONNECTED ARDUINO_EVENT_WIFI_STA_DISCONNECTED
  #endif
#endif
