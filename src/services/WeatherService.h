/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <TaskSchedulerDeclarations.h>
#include <vector>

#include "Service.h"

typedef std::function<void()> WeatherUpdatedEventFuncCb;

/**
 * @brief A service implementation to retrieve current weather
 * conditions.
 */
class WeatherService : public Service {
public:
    static constexpr char *NAME = (char*) "Weather";

    WeatherService() {}

    // Disable copy semantics
    WeatherService(const WeatherService&) = delete;

    /**
     * @brief Destroy the  object
     */
    virtual ~WeatherService() {}

    /**
     * @brief Add a new callback function to be called when
     * location information has changed.
     *
     * @param cb
     */
    void addWeatherUpdatedListener(WeatherUpdatedEventFuncCb cb) {
        weatherUpdatedListeners.push_back(cb);
    }

    /**
     * @brief Initialize the service, registering Task's as necessary.
     *
     * @param scheduler
     */
    virtual void init(Scheduler *scheduler);

    /**
     * @brief Return the name of the object.
     *
     * @return const char*
     */
    virtual const char* name() {
        return WeatherService::NAME;
    }

    /**
     * @brief Return the most recently received temperature in Farenheit
     *
     * @return int
     */
    int getTemperature() {
        return temperature;
    }

    /**
     * @brief Return a boolean indicating whether weather data has been successfully retrieved.
     *
     * @return true
     * @return false
     */
    bool isWeatherAvailable() {
        return weatherAvailable;
    }

private:
    static constexpr char *BASE_URL = (char*) "https://api.openweathermap.org/data/2.5/weather?zip=55960&units=imperial&APPID=";

    bool weatherAvailable = false;
    int temperature;

    Task weatherUpdateTask;
    std::vector<WeatherUpdatedEventFuncCb> weatherUpdatedListeners;

    /**
     * @brief Call registered callbacks to indicate an update
     */
    void signalUpdate();

    /**
     * @brief Update current weather information.
     */
    void weatherUpdate();
};
