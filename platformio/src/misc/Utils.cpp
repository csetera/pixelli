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

/**
 * @brief Mask the contents of the source string into the destination string.
 */
void Utils::mask_string(const char* source, char* destination, size_t dest_size) {
    // Check for null pointers
    if (source == NULL || destination == NULL) {
        if (destination != NULL && dest_size > 0) {
            destination[0] = '\0';
        }
        return;
    }
    
    size_t src_len = strnlen(source, dest_size);
    
    // Ensure destination buffer is large enough (including null terminator)
    if (dest_size <= src_len) {
        if (dest_size > 0) {
            destination[0] = '\0';
        }
        return;
    }
    
    // Handle strings with 4 or fewer characters - don't mask anything
    if (src_len <= 4) {
        strncpy(destination, source, dest_size);
        return;
    }
    
    // Copy first 2 characters
    destination[0] = source[0];
    destination[1] = source[1];
    
    // Mask middle characters with '*'
    for (size_t i = 2; i < src_len - 2; i++) {
        destination[i] = '*';
    }
    
    // Copy last 2 characters
    destination[src_len - 2] = source[src_len - 2];
    destination[src_len - 1] = source[src_len - 1];
    
    // Null terminate
    destination[src_len] = '\0';
}