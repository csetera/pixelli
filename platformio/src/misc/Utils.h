/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <FastLED.h>

#define FORMATTED_BUILD_TIMESTAMP_LENGTH 22

namespace Utils {
    /**
     * @brief Convert a CRGB structure into a hex color string,
     * storing the result in the provided buffer.
     *
     * @param color
     * @param buffer
     */
    void crgbToHexColorString(CRGB color, char *buffer);

    /**
     * @brief Format the build timestamp into the provided buffer.
     *
     * @param buffer
     */
    void formatBuildTimestamp(char* buffer);

    /**
     * @brief Return a random color
     *
     * @return CRGB
     */
    CRGB getRandomColor();

    /**
     * @brief Convert a hex color string into a CRGB structure.
     *
     * @param colorString
     * @return CRGB
     */
    CRGB hexColorStringToCrgb(const char *colorString);

    /**
     * @brief Mask the contents of the source string into the destination string.
     */
    void mask_string(const char* source, char* destination, size_t dest_size);
}
