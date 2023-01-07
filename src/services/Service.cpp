/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "Service.h"

/**
 * @brief Initialize the service, registering Task's as necessary.
 *
 * @param scheduler
 */
void Service::init(Scheduler *scheduler) {
   this->scheduler = scheduler;
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
