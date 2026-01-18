/**********************************************************************************
 * Copyright (C) 2023-2025 Craig Setera
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
#ifndef SPI_DISP_CS
    #define SPI_DISP_CS 10
#endif

#ifndef SPI_DISP_DC
    #define SPI_DISP_DC 46
#endif

#ifndef SPI_DISP_MISO
    #define SPI_DISP_MISO 13
#endif

#ifndef SPI_DISP_MOSI
    #define SPI_DISP_MOSI 11
#endif

#ifndef SPI_DISP_SCLK
    #define SPI_DISP_SCLK 12
#endif

#ifndef SPI_DISP_RST
    #define SPI_DISP_RST 3
#endif

#ifndef SPI_DISPLAY_ROTATE
    #define SPI_DISPLAY_ROTATE 0
#endif

// Pull in the definition of the matrix dynamically
#define STRINGIFY(x) #x
#define MAKE_STRING(x) STRINGIFY(x)

#include MAKE_STRING(MATRIX_CONFIG.h) 
