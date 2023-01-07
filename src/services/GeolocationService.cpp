/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "GeolocationService.h"

#include <logging/Logger.h>
#include <network/NetworkManager.h>
#include <network/NetworkUtils.h>
#include <misc/Utils.h>

/**
 * @brief Locate the device
 */
void GeolocationService::geolocate() {
    Logger &logger = Logger::get();
    logger.println("Making Geolocation call");

    String url(BASE_URL);
    url += ABSTRACT_API_KEY;

    NetworkUtils::httpGet(url, [&](int httpResponse, Stream& responseStream) {
        if (httpResponse > 0) {
            StaticJsonDocument<64> jsonFilter;
            jsonFilter["postal_code"] = true;
            jsonFilter["timezone"]["abbreviation"] = true;
            jsonFilter["timezone"]["gmt_offset"] = true;

            StaticJsonDocument<128> jsonResponse;
            deserializeJson(jsonResponse, responseStream, DeserializationOption::Filter(jsonFilter));

            gmtOffset = jsonResponse["timezone"]["gmt_offset"];
            strncpy(timezone, jsonResponse["timezone"]["abbreviation"], TIMEZONE_LENGTH);
            strncpy(zipcode, jsonResponse["postal_code"], ZIPCODE_LENGTH);

            located = true;
            this->geolocateTask.disable();
            this->signalStateChange();

        } else {
            Logger::get().printf("Geolocation failed with code: %d\n", httpResponse);
        }
    });
}

/**
 * @brief Initialize the service, registering Task's as necessary.
 *
 * @param scheduler
 */
void GeolocationService::init(Scheduler *scheduler) {
    Service::init(scheduler);

    geolocateTask.setCallback(std::bind(&GeolocationService::geolocate, this));
    geolocateTask.setInterval(TASK_HOUR);
    geolocateTask.setIterations(TASK_FOREVER);
    geolocateTask.disable();
    scheduler->addTask(geolocateTask);
}

/**
 * @brief Receives Wifi-related events.
 *
 * @param event
 * @param info
 */
void GeolocationService::onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    Logger::get().println("GeolocationService received wifi event");
    switch (event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            geolocateTask.enable();
            break;

        case SYSTEM_EVENT_STA_LOST_IP:
            located = false;
            signalStateChange();
            break;

        default:
            break;
    }
}

/**
 * @brief Nicely print the object to the specified Print object
 *
 * @param p
 * @return size_t
 */
size_t GeolocationService::printTo(Print& p) const {
    p.printf("Geolocation %p\n", (void*) this);
    p.printf("gmtOffset = %d\n", gmtOffset);
    p.printf("zipcode = %s\n", zipcode);
    p.printf("timezone = %s\n", timezone);

    return 0;
}

/**
 * @brief Call registered callbacks to indicate a location change
 */
void GeolocationService::signalStateChange() {
    Logger::get().printf("GeolocationService signaling state change. Listener Count: %d\n", locationChangedListeners.size());
    for (auto cb : locationChangedListeners) {
        cb();
    }
}
