/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include "BaseTextWidget.h"

#include <TaskSchedulerDeclarations.h>

/**
 * @brief A simple Widget that displays a piece of static text.
 */
class StaticTextWidget : public BaseTextWidget {
public:
    static constexpr char *NAME = (char*) "Static Text";

    StaticTextWidget(Scheduler *scheduler, const char *value, CRGB color = CRGB::White) : BaseTextWidget(scheduler) {
        displayValue.concat(value);
        this->color = color;
    }

    StaticTextWidget(Scheduler *scheduler, String &value, CRGB color = CRGB::White) : BaseTextWidget(scheduler) {
        displayValue.concat(value);
        this->color = color;
    }

    /**
     * @brief Return the name of the Widget.
     *
     * @return const char*
     */
    virtual const char* name() {
        return StaticTextWidget::NAME;
    }
};
