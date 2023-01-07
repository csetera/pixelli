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

/**
 * @brief A service implementation to retrieve top headlines.
 */
class NewsService: public Service {
public:
    static constexpr char *NAME = (char*) "News";

    NewsService(): articleCount(0) {}

    // Disable copy semantics
    NewsService(const NewsService&) = delete;

    /**
     * @brief Destroy the  object
     */
    virtual ~NewsService() {}

    /**
     * @brief Return a reference to the specified article title.
     *
     * @param index
     * @return String&
     */
    String *getArticleTitle(int index);

    /**
     * @brief Return the current number of articles.
     *
     * @return uint8_t
     */
    uint8_t getArticleCount() {
        return articleCount;
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
        return NewsService::NAME;
    }

    /**
     * @brief Retrieve latest news headlines
     */
    void newsUpdate();

    /**
     * @brief Receives Wifi-related events.
     *
     * @param event
     * @param info
     */
    virtual void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info);

private:
    static const int MAX_TITLES = 5;
    static constexpr char *BASE_URL = (char*) "https://newsapi.org/v2/top-headlines?country=us&pageSize=5&apiKey=";

    Task newsUpdateTask;

    String *titles[MAX_TITLES];
    uint8_t articleCount;
};
