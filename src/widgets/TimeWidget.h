/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include "BaseTextWidget.h"
#include <FastLED.h>

/**
 * @brief A Widget to display the current time.
 */
class TimeWidget : public BaseTextWidget {
public:
    static constexpr char *NAME = (char*) "Time";

    TimeWidget(Scheduler *scheduler) : BaseTextWidget(scheduler) {}

    /**
     * @brief Return the name of the object.
     *
     * @return const char*
     */
    virtual const char* name() {
        return TimeWidget::NAME;
    }

    /**
     * @brief Start displaying this Widget, scheduling updates as necessary.
     */
    virtual void startDisplay();
};
