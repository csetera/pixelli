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
