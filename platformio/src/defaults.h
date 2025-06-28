/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <FastLED_NeoMatrix.h>

#ifndef DATA_PIN
  #define DATA_PIN 5
#endif

#ifndef MDNS_NAME
  #define MDNS_NAME "pixelli"
#endif

#ifndef NTP_SERVER
  #define NTP_SERVER "time.nist.gov"
#endif

#ifndef NTP_UPDATE_INTERVAL_MILLIS
    #define NTP_UPDATE_INTERVAL_MILLIS 3600000
#endif

#define SECONDS_PER_HOUR 3600

// Mock Matrix SPI Configuration
#ifndef MM_CS
    #define MM_CS 17
#endif

#ifndef MM_DC
    #define MM_DC 16
#endif

#ifndef MM_MOSI
    #define MM_MOSI 23
#endif

#ifndef MM_SCLK
    #define MM_SCLK 18
#endif

#ifndef MM_RST
    #define MM_RST 5
#endif

// Pull in the definition of the matrix dynamically
#define STRINGIFY(x) #x
#define MAKE_STRING(x) STRINGIFY(x)

#include MAKE_STRING(MATRIX_CONFIG.h) 
