/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "TimeService.h"

#include <functional>

#include <defaults.h>
#include <logging/Logger.h>

#include "GeolocationService.h"
#include "ServiceRegistry.h"

/**
 * @brief Initialize the service, registering Task's as necessary.
 *
 * @param scheduler
 */
void TimeService::init(Scheduler *scheduler) {
    Service::init(scheduler);

    ntpUpdateTask.setCallback(std::bind(&TimeService::ntpUpdate, this));
    ntpUpdateTask.setInterval(TASK_HOUR);
    ntpUpdateTask.setIterations(TASK_FOREVER);
    ntpUpdateTask.disable();
    scheduler->addTask(ntpUpdateTask);

    GeolocationService *locationService = (GeolocationService *) ServiceRegistry::get()[GeolocationService::NAME];
    locationService->addLocationChangedListener([&]() {
        Logger::get().println("Time location changed callback");
        GeolocationService *locationService = (GeolocationService *) ServiceRegistry::get()[GeolocationService::NAME];
        if (locationService->isLocated()) {
            Logger::get().println("Enabling NTP update task");
            this->ntpUpdateTask.enable();
        } else {
            Logger::get().println("Disabling NTP update task");
            this->ntpUpdateTask.disable();
        }
    });
}

/**
 * @brief Use NTP to update the device's current time.
 */
void TimeService::ntpUpdate() {
    Logger &logger = Logger::get();

    if (!delayIfPaused(ntpUpdateTask)) {
        logger.println("Attempting NTP Update");

        GeolocationService *geo = (GeolocationService *) ServiceRegistry::get()[GeolocationService::NAME];
        if (geo->isLocated()) {
            logger.printf("Configuring NTP time for timezone: %s\n", geo->getTimezone());
            configTime(geo->getGmtOffset() * SECONDS_PER_HOUR, 0, NTP_SERVER, NTP_SERVER, NTP_SERVER);
            timeSet = true;
        } else {
            logger.println("Can't set time from NTP without location");
        }
    }
}
