/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "WeatherService.h"

#include <functional>
#include <logging/Logger.h>
#include <network/NetworkUtils.h>

#include "ServiceRegistry.h"
#include "GeolocationService.h"

/**
 * @brief Initialize the service, registering Task's as necessary.
 *
 * @param scheduler
 */
void WeatherService::init(Scheduler *scheduler) {
    Service::init(scheduler);

    weatherUpdateTask.setCallback(std::bind(&WeatherService::weatherUpdate, this));
    weatherUpdateTask.setInterval(TASK_MINUTE * 15);
    weatherUpdateTask.setIterations(TASK_FOREVER);
    weatherUpdateTask.disable();
    scheduler->addTask(weatherUpdateTask);

    GeolocationService *locationService = (GeolocationService *) ServiceRegistry::get()[GeolocationService::NAME];
    locationService->addLocationChangedListener([&]() {
        Logger::get().println("Weather location changed callback");
        GeolocationService *locationService = (GeolocationService *) ServiceRegistry::get()[GeolocationService::NAME];
        if (locationService->isLocated()) {
            this->weatherUpdateTask.enable();
        } else {
            this->weatherUpdateTask.disable();
        }
    });
}

/**
 * @brief Call registered callbacks to indicate an update
 */
void WeatherService::signalUpdate() {
    Logger::get().printf("WeatherService signaling update. Listener Count: %d\n", weatherUpdatedListeners.size());
    for (auto cb : weatherUpdatedListeners) {
        cb();
    }
}

/**
 * @brief Update current weather information.
 */
void WeatherService::weatherUpdate() {
    Logger &logger = Logger::get();
    logger.println("Updating weather");

    String url(BASE_URL);
    url += OWM_API_KEY;

    NetworkUtils::httpGet(url, [&](int httpResponse, Stream& responseStream) {
        if (httpResponse > 0) {
            StaticJsonDocument<64> jsonFilter;
            jsonFilter["main"]["temp"] = true;

            StaticJsonDocument<64> jsonResponse;
            deserializeJson(jsonResponse, responseStream, DeserializationOption::Filter(jsonFilter));

            temperature = jsonResponse["main"]["temp"];
            weatherAvailable = true;

        } else {
            weatherAvailable = false;
            Logger::get().printf("Weather update failed with code: %d\n", httpResponse);
        }
    });
}
