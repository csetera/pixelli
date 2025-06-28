/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <functional>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <TaskSchedulerDeclarations.h>
#include <U8g2_for_Adafruit_GFX.h>

#include <widgets/NewsWidget.h>
#include <widgets/TempWidget.h>
#include <widgets/TimeWidget.h>
#include <widgets/Widget.h>

/**
 * @brief A function to draw on the display
 */
typedef std::function<void(Adafruit_GFX &gfx, U8G2_FOR_ADAFRUIT_GFX &text_gfx)> DisplayCallback;

class DisplayManager {
public:
    /**
     * @brief Return the singleton instance of the DisplayManager.
     *
     * @return Logger&
     */
    static DisplayManager& get();

    // Disable copy semantics
    DisplayManager(const DisplayManager&) = delete;

    /**
     * @brief Clear the Display
     *
     */
    void clear();

    /**
     * @brief Get the Font Graphics object
     *
     * @return U8G2_FOR_ADAFRUIT_GFX&
     */
    U8G2_FOR_ADAFRUIT_GFX &getFontGraphics() {
        return u8g2_for_adafruit_gfx;
    }

    /**
     * @brief Return the graphics interface
     *
     * @return Adafruit_GFX&
     */
    Adafruit_GFX &getGraphics();

    /**
     * @brief Initialize the Display, registering Task's as necessary.
     *
     * @param scheduler
     */
    void init(Scheduler *scheduler);

    /**
     * @brief Set the Remote Viewer Socket object
     *
     * @param remoteSocket
     */
    void setRemoteViewerSocket(AsyncWebSocket *remoteSocket);

    /**
     * @brief Show the latest changes on the matrix
     *
     */
    void show();

    /**
     * @brief Start the display task.
     */
    void startDisplay();

    /**
     * @brief Csllback from the Widget that it has completed display and
     * is handing control back to the DisplayManager.
     */
    void widgetDisplayComplete();

private:
    enum DisplayState {
        CONNECTING,
        CONFIGURING,
        NTP,
        TIME,
        TEMP,
        NEWS
    };

    DisplayState displayState;
    Scheduler *scheduler;
    U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

    NewsWidget *newsWidget;
    TempWidget *tempWidget;
    TimeWidget *timeWidget;

    /**
     * @brief Construct a new DisplayManager object
     */
    DisplayManager():
        displayState(CONNECTING),
        scheduler(nullptr),
        newsWidget(nullptr),
        tempWidget(nullptr),
        timeWidget(nullptr) {}

    void displayNews();
    void displayTemp();
    void displayTime();
    boolean isDisplayEnabled();
};
