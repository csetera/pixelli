/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "ScrollingTextWidget.h"

#include <functional>

#include <defaults.h>
#include <services/ServiceRegistry.h>

const int SCROLL_INTERVAL = 50; // millis
/**
 * @brief Callback for use when the display of the Widget has
 * completed.  By default, just notifies the DisplayManager
 * of completion.
 */
void ScrollingTextWidget::displayComplete() {
    // Re-enable potentially long-running service tasks
    ServiceRegistry::get().resumeUpdates();
    BaseTextWidget::displayComplete();
}

/**
 * @brief Scrolling loop callback
 */
void ScrollingTextWidget::scrollLoop() {
    scrollOffset--;
    auto extents = getExtents();
    if (scrollOffset < -extents.width) {
        scrollTask->disable();
        scheduler->deleteTask(*scrollTask);
        delete(scrollTask);

        displayComplete();
    } else {
        auto y = calculate_y(*this, Alignment::V_ALIGN_CENTER);
        drawText(scrollOffset, y, displayValue);
    }
}

/**
 * @brief Start displaying this Widget, scheduling updates as necessary.
 */
void ScrollingTextWidget::startDisplay() {
    // Pause potentially long-running service tasks
    ServiceRegistry::get().pauseUpdates();

    scrollOffset = MATRIX_WIDTH;

    scrollTask = new Task();
    scrollTask->setCallback(std::bind(&ScrollingTextWidget::scrollLoop, this));
    scrollTask->setInterval(SCROLL_INTERVAL * TASK_MILLISECOND);
    scrollTask->setIterations(TASK_FOREVER);
    scheduler->addTask(*scrollTask);

    scrollTask->enable();
}
