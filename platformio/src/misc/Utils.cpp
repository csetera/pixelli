/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include <Arduino.h>
#include <time.h>

#include "Utils.h"

/**
 * @brief Convert a CRGB structure into a hex color string,
 * storing the result in the provided buffer.
 *
 * @param color
 * @param buffer
 */
void Utils::crgbToHexColorString(CRGB color, char *buffer) {
    sprintf(buffer, "#%02x%02x%02x", color.red, color.green, color.blue);
}

/**
 * @brief Format the build timestamp into the provided buffer.
 *
 * @param buffer
 */
void Utils::formatBuildTimestamp(char* buffer) {
    time_t timestamp = BUILD_TIMESTAMP;
    strftime(buffer, FORMATTED_BUILD_TIMESTAMP_LENGTH, "%Y-%m-%dT%H:%M:%SZ", localtime(&timestamp));
}

/**
 * @brief Return a random color
 *
 * @return CRGB
 */
CRGB Utils::getRandomColor() {
    int h = rand() % 255;
    int s = rand() % 128 + 127;

    return CRGB(CHSV(h, s, 200));
}

/**
 * @brief Convert a hex color string into a CRGB structure.
 *
 * @param colorString
 * @return CRGB
 */
CRGB Utils::hexColorStringToCrgb(const char *colorString) {
    uint32_t data = (colorString[0] == '#') ?
        (uint32_t) strtol((colorString + 1), NULL, 16) :
        (uint32_t) strtol(colorString, NULL, 16);

    return CRGB(((data >> 16) & 0xFF), ((data >> 8) & 0xFF), ((data >> 0) & 0xFF));
}
