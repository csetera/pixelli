/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <TaskSchedulerDeclarations.h>
#include "Service.h"

/**
 * @brief A service implementation to update system time via NTP.
 */
class TimeService: public Service {
public:
    static constexpr char *NAME = (char*) "Time";

    TimeService(): timeSet(false) {}

    // Disable copy semantics
    TimeService(const TimeService&) = delete;

    /**
     * @brief Destroy the  object
     */
    virtual ~TimeService() {}

    /**
     * @brief Initialize the service, registering Task's as necessary.
     *
     * @param scheduler
     */
    virtual void init(Scheduler *scheduler);

    /**
     * @brief Return a boolean indicating whether the time has been set.
     *
     * @return true
     * @return false
     */
    bool isTimeSet() {
        return timeSet;
    }

    /**
     * @brief Return the name of the object.
     *
     * @return const char*
     */
    virtual const char* name() {
        return TimeService::NAME;
    }

private:
    bool timeSet;
    Task ntpUpdateTask;

    /**
     * @brief Get the Update Task object
     *
     * @return Task*
     */
    virtual Task *getUpdateTask() {
        return &ntpUpdateTask;
    }

    /**
     * @brief Use NTP to update the device's current time.
     */
    void ntpUpdate();
};
