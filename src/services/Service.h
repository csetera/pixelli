/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <TaskSchedulerDeclarations.h>
#include <WiFi.h>

/**
 * @brief Base class for all services that provide
 * data to the system.
 */
class Service {
public:
    /**
     * @brief Construct a new Service object
     */
    Service(): paused(false) {}

    // Disable copy semantics
    Service(const Service&) = delete;

    /**
     * @brief Destroy the  object
     */
    virtual ~Service() {}

    /**
     * @brief Return the name of the object.
     *
     * @return const char*
     */
    virtual const char* name() = 0;

    /**
     * @brief Initialize the service, registering Task's as necessary.
     *
     * @param scheduler
     */
    virtual void init(Scheduler *scheduler);

    /**
     * @brief Receives Wifi-related events.
     *
     * @param event
     * @param info
     */
    virtual void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
        // Do nothing by default
    }

    /**
     * @brief Pause any service update tasks
     */
    virtual void pauseUpdates();

    /**
     * @brief Resume any service update tasks.
     */
    virtual void resumeUpdates();

protected:
    bool paused;
    Scheduler *scheduler;

    /**
     * @brief Get the Update Task object
     *
     * @return Task*
     */
    virtual Task *getUpdateTask() {
        return nullptr;
    }

    /**
     * @brief Return a boolean indicating whether wifi is currently connected.
     *
     * @return true
     * @return false
     */
    bool isWifiConnected();
};
