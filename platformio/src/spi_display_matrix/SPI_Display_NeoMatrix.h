/**********************************************************************************
 * Copyright (C) 2023-2025 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <defaults.h>
#include <Adafruit_NeoMatrix.h>
#include <Arduino_GFX_Library.h>
#include <stdint.h>

#if defined(USE_SSD1351)
  typedef Arduino_SSD1351 Arduino_Display_Type;
#elif defined(USE_ILI9341)
  typedef Arduino_ILI9341 Arduino_Display_Type;
#else
  #error "No display type defined"
#endif

/**
 * @brief Wraps an SPI-attached display (eg https://www.amazon.com/gp/product/B07V579YK2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)
 * to act like a Neopixel matrix for testing purposes.
 */
class SPI_Display_NeoMatrix : public Adafruit_NeoMatrix {
public:
    SPI_Display_NeoMatrix(int w, int h) :
        Adafruit_NeoMatrix(w, h),
        databus(new Arduino_ESP32SPI(SPI_DISP_DC, SPI_DISP_CS, SPI_DISP_SCLK, SPI_DISP_MOSI, SPI_DISP_MISO)),
        gfx(new Arduino_Display_Type(databus, SPI_DISP_RST)),
        height(h),
        width(w),
        firstScreenClear(true) {}

    void    begin(int32_t speed = GFX_NOT_DEFINED);
    void    clear(void);
    void    drawPixel(int16_t x, int16_t y, uint16_t color);
    void    fillScreen(uint16_t color);
    void    show(void);

private:
    Arduino_DataBus         *databus;
    Arduino_GFX             *gfx;
    uint8_t                 errorCode;
    int                     height;
    int                     width;
    bool                    firstScreenClear;

    bool    inBounds(int16_t x, int16_t y);
};
