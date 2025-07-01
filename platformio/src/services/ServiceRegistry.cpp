/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "ServiceRegistry.h"

#include <string.h>
#include <WiFi.h>

#include <compatibility.h>
#include <logging/Logger.h>
#include "GeolocationService.h"
#include "NewsService.h"
#include "TimeService.h"
#include "WeatherService.h"

/**
 * @brief Return the singleton instance.
 *
 * @return Logger&
 */
ServiceRegistry& ServiceRegistry::get() {
    static ServiceRegistry singleton;
    return singleton;
}

/**
 * @brief Construct a new ServiceRegistry object
 */
ServiceRegistry::ServiceRegistry() {
    services = {
        new GeolocationService(),
        new NewsService(),
        new TimeService(),
        new WeatherService()
    };
}

/**
 * @brief Destroy the ServiceRegistry object
 */
ServiceRegistry::~ServiceRegistry() {
    for (size_t i = 0; i < services.size(); i++) {
        delete services[i];
    }
}

/**
 * @brief Execute the specified function for each
 * Service* in the list.
 *
 * @param f
 */
void ServiceRegistry::each(std::function<void(Service*)> f) {
    for (auto & element : services) {
        f(element);
    }
}

/**
 * @brief Initialize the registry with the provided Scheduler.
 *
 * @param scheduler
 */
void ServiceRegistry::init(Scheduler *scheduler) {
    for (auto & element : services) {
        element->init(scheduler);
    }

    WiFi.onEvent([&](WiFiEvent_t event, WiFiEventInfo_t info) {
        switch (event) {
            case SYSTEM_EVENT_STA_GOT_IP:
                Logger::get().println("Connected with IP Address");
                Logger::get().println(WiFi.localIP());
                // Intentional fall through

            default:
                for (auto & element : services) {
                   element->onWifiEvent(event, info);
                }
                break;
        }
    });
}

/**
 * @brief Return the Service* at the specified index.
 *
 * @param index
 * @return Service*
 */
Service* ServiceRegistry::operator[](int index) {
    return services[index];
}

/**
 * @brief Return the Service* with the specified name.
 *
 * @param name
 * @return Scene*
 */
Service* ServiceRegistry::operator[](const char *name) {
    for (size_t i = 0; i < services.size(); i++) {
        if (strcmp(name, services[i]->name()) == 0) {
            return services[i];
        }
    }

    return nullptr;
}

/**
 * @brief Pause any service update tasks
 */
void ServiceRegistry::pauseUpdates() {
    this->each([](Service *service) { service->pauseUpdates(); });
}

/**
 * @brief Resume any service update tasks.
 */
void ServiceRegistry::resumeUpdates() {
    this->each([](Service *service) { service->resumeUpdates(); });
}
