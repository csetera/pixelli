/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <stdint.h>

namespace Alignment {
    const int16_t H_ALIGN_LEFT = -0x7ffd;
    const int16_t H_ALIGN_CENTER = -0x7ffd + 1;
    const int16_t H_ALIGN_RIGHT = -0x7ffd + 2;

    const int16_t V_ALIGN_TOP = -0x7ffd + 3;
    const int16_t V_ALIGN_CENTER = -0x7ffd + 4;
    const int16_t V_ALIGN_BOTTOM = -0x7ffd + 5;
}
