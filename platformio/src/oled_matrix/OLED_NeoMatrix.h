/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
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

#ifdef ENABLE_REMOTE_VIEWER
    #include <ESPAsyncWebServer.h>

    enum Command {
        ON_CONNECT = 1,
        SHOW = 2
    };

    #pragma pack(1)
        struct OnConnectPacket {
            uint8_t     command;
            uint8_t     width;
            uint8_t     height;
        };

        struct ShowScreenPacket {
            uint8_t     command;
            uint16_t    pixels[NUM_LEDS];
        };
    #pragma pack(0)

#endif

/**
 * @brief Wraps a SSD1351 display (eg https://www.amazon.com/gp/product/B07V579YK2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)
 * to act like a Neopixel matrix for testing purposes.
 */
class OLED_NeoMatrix : public Adafruit_NeoMatrix {
public:
    OLED_NeoMatrix(int w, int h) :
        Adafruit_NeoMatrix(w, h),
        databus(new Arduino_ESP32SPI(MM_DC, MM_CS, MM_SCLK, MM_MOSI)),
        gfx(new Arduino_SSD1351(databus, MM_RST)),
        height(h),
        width(w),
        firstScreenClear(true) {}

    void    begin(int32_t speed = GFX_NOT_DEFINED);
    void    clear(void);
    void    drawPixel(int16_t x, int16_t y, uint16_t color);
    void    fillScreen(uint16_t color);
    void    show(void);

    #ifdef ENABLE_REMOTE_VIEWER
        void setRemoteViewerSocket(AsyncWebSocket *remoteSocket);
    #endif

private:
    Arduino_DataBus         *databus;
    Arduino_GFX             *gfx;
    uint8_t                 errorCode;
    int                     height;
    int                     width;
    bool                    firstScreenClear;

    bool    inBounds(int16_t x, int16_t y);

    #ifdef ENABLE_REMOTE_VIEWER
        AsyncWebSocket          *socket;
        OnConnectPacket         onConnectPacket;
        ShowScreenPacket        showScreenPacket;

        bool isRemoteConnected();
    #endif
};
