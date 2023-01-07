/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include "Widget.h"
#include <FastLED.h>
#include <U8g2_for_Adafruit_GFX.h>

/**
 * @brief A base implementation for Widget's that display text.
 */
class BaseTextWidget : public Widget {
public:
    BaseTextWidget(Scheduler *scheduler): Widget(scheduler), color(CRGB::White) {}

    /**
     * @brief Get the Extents of this Widget
     *
     * @return Extents
     */
    virtual Extents getExtents();

    /**
     * @brief Start displaying this Widget, marking display
     * complete after the specified number of seconds.
     *
     * @param numSeconds
     */
    void displayForSeconds(int numSeconds);

    /**
     * @brief Set the color of the text
     *
     * @param color
     */
    void setColor(CRGB color) {
       color = color;
    }

    /**
     * @brief Start displaying this Widget, scheduling updates as necessary.
     */
    void startDisplay();

protected:
    CRGB color;
    String displayValue;

    /**
     * @brief Display the specified text at the specified "absolute" location.
     *
     * @param x
     * @param y
     * @param text
     */
    void drawText(int16_t x, int16_t y, String text);
};
