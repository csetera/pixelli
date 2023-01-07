/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "TempWidget.h"

#include <misc/TemperaturePalette.h>
#include <services/WeatherService.h>

/**
 * @brief Start displaying this Widget, scheduling updates as necessary.
 */
void TempWidget::startDisplay() {
    WeatherService *weatherService = (WeatherService *) getService(WeatherService::NAME);

    displayValue.clear();
    if (weatherService->isWeatherAvailable()) {
        int temp = weatherService->getTemperature();
        color = TemperaturePalette::GetColorForTemperature(temp);
        displayValue.concat(temp);
    } else {
        displayValue.concat('?');
    }

    displayValue.concat((char) 176);
    displayValue.concat('F');

    BaseTextWidget::startDisplay();
}
