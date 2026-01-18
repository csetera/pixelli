/**********************************************************************************
 * Copyright (C) 2025 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "SPI_Display_NeoMatrix.h"

void SPI_Display_NeoMatrix::begin(int32_t speed) {
    gfx->begin(speed);
    gfx->setRotation(SPI_DISPLAY_ROTATE);
}

void SPI_Display_NeoMatrix::clear(void) {
    fillScreen(0);
}

void SPI_Display_NeoMatrix::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (inBounds(x, y)) {
        int16_t x0 = x * 4;
        int16_t y0 = y * 4;

        gfx->fillRect(x0, y0, 3, 3, color);
    }
}

void SPI_Display_NeoMatrix::fillScreen(uint16_t color) {
    if (firstScreenClear) {
        gfx->fillScreen(0);
        firstScreenClear = false;
    } else {
        gfx->fillRect(0, 0, width * 4, height * 4, color);
    }
}

bool SPI_Display_NeoMatrix::inBounds(int16_t x, int16_t y) {
    return (x >= 0) && (x < width) && (y >= 0) && (y < height);
}

void SPI_Display_NeoMatrix::show(void) {
}
