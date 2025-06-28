/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <TaskSchedulerDeclarations.h>

#include <display/Alignment.h>
#include <display/Extents.h>
#include <services/Service.h>

/**
 * @brief Base class for all "displayable Widgets"
 */
class Widget {
public:
    Widget(Scheduler *scheduler) :
        x(Alignment::H_ALIGN_CENTER),
        y(Alignment::V_ALIGN_CENTER),
        scheduler(scheduler) { }

    /**
     * @brief Calculate the actual X coordinate taking into account
     * potential alignment requestes
     *
     * @param widget
     * @param x
     * @return int16_t
     */
    static int16_t calculate_x(Widget &widget, int16_t x);

    /**
     * @brief Calculate the actual Y coordinate taking into account
     * potential alignment requests.
     *
     * @param widget
     * @param y
     * @return int16_t
     */
    static int16_t calculate_y(Widget &widget, int16_t y);

    /**
     * @brief Callback for use when the display of the Widget has
     * completed.  By default, just notifies the DisplayManager
     * of completion.
     */
    virtual void displayComplete();

    /**
     * @brief Display this Widget for the specified number of seconds.
     *
     * @param numSeconds
     */
    void displayForSeconds(int numSeconds);

    /**
     * @brief Get the Extents of this Widget
     *
     * @return Extents
     */
    virtual Extents getExtents() = 0;

    /**
     * @brief Return the X value
     *
     * @return int16_t
     */
    int16_t getX() {
        return x;
    }

    /**
     * @brief Return the Y value
     *
     * @return int16_t
     */
    int16_t getY() {
        return y;
    }

    /**
     * @brief Return the name of this Widget.
     *
     * @return const char*
     */
    virtual const char* name() = 0;

    /**
     * @brief Set the X value
     *
     * @param new_x
     */
    void setX(int16_t new_x) {
        x = new_x;
    }

    /**
     * @brief Set the Y value
     *
     * @param new_y
     */
    void setY(int16_t new_y) {
        y = new_y;
    }

    /**
     * @brief Start displaying this Widget, scheduling updates as necessary.
     */
    virtual void startDisplay() = 0;

protected:
    int16_t x;
    int16_t y;
    Scheduler *scheduler;

    /**
     * @brief Return the Service* with the specified name.
     *
     * @param name
     * @return Scene*
     */
    Service* getService(const char *name);
};
