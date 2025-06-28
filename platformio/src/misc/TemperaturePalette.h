/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <FastLED.h>

/**
 * @brief Defines a FastLED palette that maps temps to color values.
 */
namespace TemperaturePalette {
    /**
     * @brief Get the Color For Temperature (fahrenheit)
     *
     * @param temp
     * @return CRGB
     */
    CRGB GetColorForTemperature(int temp);
}
