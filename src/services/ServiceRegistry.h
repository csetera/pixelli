/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include <functional>
#include <vector>
#include "Service.h"

/**
 * @brief Provides a registry of all Service implementations, accessible
 * by service name.
 */
class ServiceRegistry {
public:
    /**
     * @brief Return the singleton instance.
     *
     * @return Logger&
     */
    static ServiceRegistry& get();

    // Disable copy semantics
    ServiceRegistry(const ServiceRegistry&) = delete;

    /**
     * @brief Destroy the ServiceRegistry object
     */
    ~ServiceRegistry();

    /**
     * @brief Execute the specified function for each
     * Service* in the list.
     *
     * @param f
     */
    void each(std::function<void(Service*)> f);

    /**
     * @brief Initialize the registry with the provided Scheduler.
     *
     * @param scheduler
     */
    void init(Scheduler *scheduler);

    /**
     * @brief Return the Service* at the specified index.
     *
     * @param index
     * @return Service*
     */
    Service* operator[](int index);

    /**
     * @brief Return the Service* with the specified name.
     *
     * @param name
     * @return Scene*
     */
    Service* operator[](const char *name);

private:
    /**
     * @brief Construct a new Services object
     */
    ServiceRegistry();

    std::vector<Service*> services;
};
