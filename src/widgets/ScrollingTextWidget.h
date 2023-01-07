/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include "BaseTextWidget.h"

/**
 * @brief A base implementation for Widget's that scroll text from right to left.
 */
class ScrollingTextWidget : public BaseTextWidget {
public:
    static constexpr char *NAME = (char*) "Scrolling Text";

    ScrollingTextWidget(Scheduler *scheduler) : BaseTextWidget(scheduler) { }

    /**
     * @brief Return the name of the Widget.
     *
     * @return const char*
     */
    virtual const char* name() {
        return ScrollingTextWidget::NAME;
    }

    /**
     * @brief Start displaying this Widget, scheduling updates as necessary.
     */
    virtual void startDisplay();

private:
    int scrollOffset;
    Task *scrollTask;

    /**
     * @brief Scrolling loop callback
     */
    void scrollLoop();
};
