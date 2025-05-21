/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "BaseTextWidget.h"

#include <display/DisplayManager.h>
#include <logging/Logger.h>

#include <FastLED.h>
#include <FastLED_NeoMatrix.h>

/**
 * @brief Start displaying this Widget, marking display
 * complete after the specified number of seconds.
 *
 * @param scheduler
 * @param numSeconds
 */
void BaseTextWidget::displayForSeconds(int numSeconds) {
    Task *task = new Task(
        numSeconds * TASK_SECOND, 1,
        [this] () {
            DisplayManager::get().widgetDisplayComplete();
        },
        scheduler, false, nullptr, nullptr, true); // enable self-destruct
    task->enableDelayed(numSeconds * TASK_SECOND);

    startDisplay();
}

/**
 * @brief Display the specified text at the specified "absolute" location.
 *
 * @param x
 * @param y
 * @param text
 */
void BaseTextWidget::drawText(int16_t x, int16_t y, String text) {
    U8G2_FOR_ADAFRUIT_GFX &u8g2_for_adafruit_gfx = DisplayManager::get().getFontGraphics();
    DisplayManager::get().clear();

    auto color565 = FastLED_NeoMatrix::Color24to16(FastLED_NeoMatrix::CRGBtoint32(color));
    u8g2_for_adafruit_gfx.setForegroundColor(color565);
    u8g2_for_adafruit_gfx.setCursor(x, y);
    u8g2_for_adafruit_gfx.print(text);

    DisplayManager::get().show();
}

/**
 * @brief Get the Extents of this Widget
 *
 * @return Extents
 */
Extents BaseTextWidget::getExtents() {
    U8G2_FOR_ADAFRUIT_GFX &u8g2_for_adafruit_gfx = DisplayManager::get().getFontGraphics();
    return Extents(
        u8g2_for_adafruit_gfx.getUTF8Width(displayValue.c_str()),
        u8g2_for_adafruit_gfx.getFontAscent() + u8g2_for_adafruit_gfx.getFontDescent());
}

/**
 * @brief Start displaying this Widget, scheduling updates as necessary.
 */
void BaseTextWidget::startDisplay() {
    int16_t calculated_x = calculate_x(*this, x);
    int16_t calculated_y = calculate_y(*this, y);

    drawText(calculated_x, calculated_y, displayValue);
}
