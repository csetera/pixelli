/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <FastLED_NeoMatrix.h>

#define MATRIX_TYPE (NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG)

#ifndef DATA_PIN
  #define DATA_PIN 5
#endif

#ifndef MATRIX_HEIGHT
  #define MATRIX_HEIGHT 8
#endif

#ifndef MATRIX_WIDTH
  #define MATRIX_WIDTH 32
#endif

#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)

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

#define ENABLE_REMOTE_VIEWER
