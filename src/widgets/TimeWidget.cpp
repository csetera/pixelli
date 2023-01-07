/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "TimeWidget.h"

#include <Arduino.h>
#include <time.h>

#include <misc/Utils.h>
#include <services/GeolocationService.h>

/**
 * @brief Format the current time into the provided String.
 *
 * @param formattedTime
 */
void formatTime(String &formattedTime) {
    time_t now = time(nullptr);
    struct tm *tm = localtime(&now);

    auto hours = tm->tm_hour;
    if (hours > 12) {
      hours -= 12;
    } else if (hours == 0) {
      hours = 12;
    }

    formattedTime.remove(0);
    formattedTime.concat(hours);
    formattedTime.concat(":");

    auto minutes = tm->tm_min;
    if (minutes < 10) {
        formattedTime.concat("0");
    }
    formattedTime.concat(minutes);
}

/**
 * @brief Start displaying this Widget, scheduling updates as necessary.
 */
void TimeWidget::startDisplay() {
    color = Utils::getRandomColor();

    displayValue.clear();
    GeolocationService *geolocationService = (GeolocationService *) getService(GeolocationService::NAME);
    if (geolocationService->isLocated()) {
        formatTime(displayValue);
    } else {
        displayValue.concat("??:??");
    }

    BaseTextWidget::startDisplay();
}
