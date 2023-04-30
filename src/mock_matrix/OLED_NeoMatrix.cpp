/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "OLED_NeoMatrix.h"

void OLED_NeoMatrix::begin(int32_t speed) {
    gfx->begin(speed);
    gfx->setRotation(3);

    #ifdef ENABLE_REMOTE_VIEWER
        showScreenPacket.command = Command::SHOW;

        // This packet will not change contents
        onConnectPacket.command = Command::ON_CONNECT;
        onConnectPacket.height = height;
        onConnectPacket.width = width;
    #endif
}

void OLED_NeoMatrix::clear(void) {
    fillScreen(0);
}

void OLED_NeoMatrix::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (inBounds(x, y)) {
        int16_t x0 = x * 4;
        int16_t y0 = y * 4;

        gfx->fillRect(x0, y0, 3, 3, color);

        #ifdef ENABLE_REMOTE_VIEWER
            showScreenPacket.pixels[x + (y * WIDTH)] = color;
        #endif
    }
}

void OLED_NeoMatrix::fillScreen(uint16_t color) {
    if (firstScreenClear) {
        gfx->fillScreen(0);
        firstScreenClear = false;
    } else {
        gfx->fillRect(0, 0, width * 4, height * 4, color);
    }

    #ifdef ENABLE_REMOTE_VIEWER
        for (int i = 0; i < NUM_LEDS; i++) {
            showScreenPacket.pixels[i] = color;
        }
    #endif
}

bool OLED_NeoMatrix::inBounds(int16_t x, int16_t y) {
    return (x >= 0) && (x < width) && (y >= 0) && (y < height);
}

void OLED_NeoMatrix::show(void) {
    #ifdef ENABLE_REMOTE_VIEWER
        if (isRemoteConnected()) {
            socket->binaryAll((const char *) &showScreenPacket, sizeof(showScreenPacket));
        }
    #endif
}

#ifdef ENABLE_REMOTE_VIEWER
    bool OLED_NeoMatrix::isRemoteConnected() {
        return (socket != nullptr) && (socket->count() > 0);
    }

    void OLED_NeoMatrix::setRemoteViewerSocket(AsyncWebSocket *remoteSocket) {
        Serial.printf("Remote viewer socket set: %p\n", remoteSocket);
        socket = remoteSocket;
        socket->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
            Serial.printf("Remote WS event: %d/%d\n", client->id(), type);
            if (type == AwsEventType::WS_EVT_CONNECT) {
                Serial.println("Connect event");
                socket->binary(client->id(), (const char*) &onConnectPacket, sizeof(onConnectPacket));
            }
        });
    }
#endif
