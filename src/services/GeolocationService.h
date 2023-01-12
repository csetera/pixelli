/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include <TaskSchedulerDeclarations.h>

#include "Service.h"

typedef std::function<void()> LocationChangedEventFuncCb;

/**
 * @brief A service implementation for accessing location
 * information based on IP lookup.
 */
class GeolocationService : public Service, Printable {
public:
    /**
     * @brief Name of this service
     */
    static constexpr char *NAME = (char*) "Geolocation";

    /**
     * @brief Construct a new Geolocation Service object
     */
    GeolocationService(): located(false) { }

    // Disable copy semantics
    GeolocationService(const GeolocationService&) = delete;

    /**
     * @brief Destroy the  object
     */
    virtual ~GeolocationService() {}

    /**
     * @brief Add a new callback function to be called when
     * location information has changed.
     *
     * @param cb
     */
    void addLocationChangedListener(LocationChangedEventFuncCb cb) {
        locationChangedListeners.push_back(cb);
    }

    /**
     * @brief Return the offset from GMT at the location
     *
     * @return int
     */
    int getGmtOffset() {
        return gmtOffset;
    }

    /**
     * @brief Return the identifier of the located timezone.
     *
     * @return const char*
     */
    const char *getTimezone() {
        return timezone;
    }

    /**
     * @brief Return the zip code of the located timezone.
     *
     * @return const char*
     */
    const char *getZipcode() {
        return zipcode;
    }

    /**
     * @brief Initialize the service, registering Task's as necessary.
     *
     * @param scheduler
     */
    virtual void init(Scheduler *scheduler);

    /**
     * @brief Return a boolean indicating whether geolocation has succeeded.
     *
     * @return true
     * @return false
     */
    bool isLocated() {
        return located;
    }

    /**
     * @brief Return the name of the object.
     *
     * @return const char*
     */
    virtual const char* name() {
        return GeolocationService::NAME;
    }

    /**
     * @brief Receives Wifi-related events.
     *
     * @param event
     * @param info
     */
    virtual void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);

    /**
     * @brief Nicely print the object to the specified Print object
     *
     * @param p
     * @return size_t
     */
    virtual size_t printTo(Print& p) const;

private:
    static const int ZIPCODE_LENGTH = 10;
    static const int TIMEZONE_LENGTH = 10;
    static constexpr char *BASE_URL = (char*) "https://ipgeolocation.abstractapi.com/v1/?api_key=";

    Task geolocateTask;

    bool located;
    int gmtOffset;
    char zipcode[ZIPCODE_LENGTH];
    char timezone[TIMEZONE_LENGTH];

    std::vector<LocationChangedEventFuncCb> locationChangedListeners;

    /**
     * @brief Locate the device
     */
    void geolocate();

    /**
     * @brief Call registered callbacks to indicate a location change
     */
    void signalStateChange();
};
