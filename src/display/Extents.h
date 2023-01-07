/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <Arduino.h>

/**
 * @brief A holder for length and width information.
 */
struct Extents {
    uint16_t width;
    uint16_t height;

    inline Extents(uint16_t w, uint16_t h)  __attribute__((always_inline)) : width(w), height(h) { }
};
