/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "defaults.h"
#include "Widget.h"

#include <display/DisplayManager.h>
#include <services/ServiceRegistry.h>

const int16_t CENTER_X = PIXELS_X / 2;
const int16_t CENTER_Y = PIXELS_Y / 2;

/**
 * @brief Calculate the actual X coordinate taking into account
 * potential alignment requestes
 *
 * @param widget
 * @param x
 * @return int16_t
 */
int16_t Widget::calculate_x(Widget &widget, int16_t x) {
    int16_t calculated_x = 0;
    Extents extents = widget.getExtents();

    switch (x) {
        case Alignment::H_ALIGN_CENTER:
            calculated_x = CENTER_X - (extents.width / 2);
            break;

        case Alignment::H_ALIGN_LEFT:
            calculated_x = 0;
            break;

        case Alignment::H_ALIGN_RIGHT:
            calculated_x = PIXELS_X - extents.width;
            break;

        default:
            calculated_x = x;
            break;
    }

    return calculated_x;
}

/**
 * @brief Calculate the actual Y coordinate taking into account
 * potential alignment requests.
 *
 * @param widget
 * @param y
 * @return int16_t
 */
int16_t Widget::calculate_y(Widget &widget, int16_t y) {
    int16_t calculated_y = 0;
    Extents extents = widget.getExtents();

    switch (y) {
        case Alignment::V_ALIGN_CENTER:
            calculated_y = CENTER_Y - (extents.height / 2);
            break;

        case Alignment::V_ALIGN_TOP:
            calculated_y = 0;
            break;

        case Alignment::V_ALIGN_BOTTOM:
            calculated_y = PIXELS_Y - extents.height;
            break;

        default:
            calculated_y = y;
            break;
    }

    return PIXELS_Y - calculated_y + 1;
}

/**
 * @brief Callback for use when the display of the Widget has
 * completed.  By default, just notifies the DisplayManager
 * of completion.
 */
void Widget::displayComplete() {
    DisplayManager::get().widgetDisplayComplete();
}

/**
 * @brief Display this Widget for the specified number of seconds.
 *
 * @param numSeconds
 */
void Widget::displayForSeconds(int numSeconds) {
    Task *task = new Task(
        numSeconds * TASK_SECOND, 1,
        [this] () {
            this->displayComplete();
        },
        scheduler, false, nullptr, nullptr, true); // enable self-destruct
    task->enableDelayed(numSeconds * TASK_SECOND);

    startDisplay();
}

/**
 * @brief Return the Service* with the specified name.
 *
 * @param name
 * @return Scene*
 */
Service* Widget::getService(const char *name) {
    return ServiceRegistry::get()[name];
}
