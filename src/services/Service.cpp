/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "Service.h"
#include <logging/Logger.h>

const unsigned long PAUSE_UPDATES_DELAY = TASK_SECOND * 5;

/**
 * @brief Initialize the service, registering Task's as necessary.
 *
 * @param scheduler
 */
void Service::init(Scheduler *scheduler) {
   this->scheduler = scheduler;
}


/**
 * @brief Delay the specified task if updates are currently paused.  Returns
 * a boolean indicating whether the task was delayed.
 *
 * @param task
 * @return true
 * @return false
 */
bool Service::delayIfPaused(Task &task) {
    if (updatesPaused) {
        Logger::get().printf("Delaying paused updates for %s\n", name());
        task.delay(PAUSE_UPDATES_DELAY);
        return true;
    }

    return false;
}

/**
 * @brief Return a boolean indicating whether wifi is currently connected.
 *
 * @return true
 * @return false
 */
bool Service::isWifiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

/**
 * @brief Pause any service update tasks
 */
void Service::pauseUpdates() {
    updatesPaused = true;
}

/**
 * @brief Resume any service update tasks.
 */
void Service::resumeUpdates() {
    updatesPaused = false;
}
