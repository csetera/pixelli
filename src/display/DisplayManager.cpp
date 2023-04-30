/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "DisplayManager.h"

#include <display/Alignment.h>
#include <functional>
#include <defaults.h>

#include <logging/Logger.h>
#include <misc/Utils.h>

#include <services/GeolocationService.h>
#include <services/NewsService.h>
#include <services/ServiceRegistry.h>
#include <services/TimeService.h>
#include <services/WeatherService.h>

#include <widgets/StaticTextWidget.h>

#ifdef MOCK_MATRIX
    #include "mock_matrix/OLED_NeoMatrix.h"
    OLED_NeoMatrix matrix(MATRIX_WIDTH, MATRIX_HEIGHT);
#else
    CRGB leds[NUM_LEDS];
    FastLED_NeoMatrix matrix(leds, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE);
#endif

StaticTextWidget* connectingWidget;
StaticTextWidget* configuringWidget;
StaticTextWidget* ntpWidget;

/**
 * @brief Return the singleton instance of the Display.
 *
 * @return Logger&
 */
DisplayManager& DisplayManager::get() {
    static DisplayManager singleton;
    return singleton;
}

/**
 * @brief Clear the Display
 *
 */
void DisplayManager::clear() {
    matrix.fillScreen(0);
}

/**
 * @brief Display the News widget
 */
void DisplayManager::displayNews() {
    displayState = DisplayState::NEWS;
    newsWidget->startDisplay();
}

/**
 * @brief Display the Temperature widget
 */
void DisplayManager::displayTemp() {
    displayState = DisplayState::TEMP;
    tempWidget->displayForSeconds(15);
}

/**
 * @brief Display the time widget
 */
void DisplayManager::displayTime() {
    displayState = DisplayState::TIME;
    timeWidget->displayForSeconds(15);
}

/**
 * @brief Return the graphics interface
 *
 * @return Adafruit_GFX&
 */
Adafruit_GFX &DisplayManager::getGraphics() {
    return matrix;
}

/**
 * @brief Initialize the Display, registering Task's as necessary.
 *
 * @param scheduler
 */
void DisplayManager::init(Scheduler *scheduler) {
#ifndef MOCK_MATRIX
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
#endif
    this->scheduler = scheduler;

    matrix.begin();
    matrix.setBrightness(80);

    // Initialize the font
    u8g2_for_adafruit_gfx.begin(matrix);
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setFontDirection(0);
    u8g2_for_adafruit_gfx.setFont(u8g2_font_bitcasual_tf);

    // Initialize the widgets to be displayed
    connectingWidget = new StaticTextWidget(scheduler, "CONN", CRGB::Red);
    configuringWidget = new StaticTextWidget(scheduler, "CFG", CRGB::Orange);
    ntpWidget = new StaticTextWidget(scheduler, "NTP", CRGB::Yellow);

    newsWidget = new NewsWidget(scheduler);
    tempWidget = new TempWidget(scheduler);
    timeWidget = new TimeWidget(scheduler);

    // Wire up a listener for wifi connected to update the display status
    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info) {
        if (event == ARDUINO_EVENT_WIFI_STA_CONNECTED) {
            connectingWidget->displayComplete();
        }
    });

    // Wire up a listener for location changed to update the display status
    GeolocationService *locationService = (GeolocationService*) ServiceRegistry::get()[GeolocationService::NAME];
    locationService->addLocationChangedListener([&]() {
        GeolocationService *locationService = (GeolocationService *) ServiceRegistry::get()[GeolocationService::NAME];
        if (locationService->isLocated()) {
            if (displayState == DisplayState::CONFIGURING) {
                configuringWidget->displayComplete();
            }
        }
    });
}

/**
 * @brief Show the latest changes on the matrix
 *
 */
void DisplayManager::setRemoteViewerSocket(AsyncWebSocket *remoteSocket) {
#ifdef ENABLE_REMOTE_VIEWER
    matrix.setRemoteViewerSocket(remoteSocket);
#endif
}

void DisplayManager::show()
{
    matrix.show();
}

/**
 * @brief Start the display task.
 */
void DisplayManager::startDisplay() {
    connectingWidget->startDisplay();
}

/**
 * @brief Csllback from the Widget that it has completed display and
 * is handing control back to the DisplayManager.
 */
void DisplayManager::widgetDisplayComplete() {
    TimeService *timeService = (TimeService*) ServiceRegistry::get()[TimeService::NAME];
    WeatherService *weatherService = (WeatherService*) ServiceRegistry::get()[WeatherService::NAME];

    switch (displayState) {
        case DisplayState::CONFIGURING:
            if (timeService->isTimeSet()) {
                displayTime();
            } else {
                displayState = DisplayState::NTP;
                ntpWidget->displayForSeconds(5);
            }
            break;

        case DisplayState::CONNECTING:
            displayState = DisplayState::CONFIGURING;
            configuringWidget->startDisplay();
            break;

        case DisplayState::NEWS:
            displayTime();
            break;

        case DisplayState::NTP:
            if (timeService->isTimeSet()) {
                displayTime();
            } else {
                ntpWidget->displayForSeconds(5);
            }
            break;

        case DisplayState::TEMP:
            displayNews();
            break;

        case DisplayState::TIME:
            if (weatherService->isWeatherAvailable()) {
                displayTemp();
            } else {
                displayTime();
            }

            break;
    }
}
