/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "NewsService.h"

#include <functional>

#include <compatibility.h>
#include <defaults.h>
#include <logging/Logger.h>
#include <network/NetworkUtils.h>
#include <misc/Utils.h>

#include "ServiceRegistry.h"

/**
 * @brief Return a reference to the specified article title.
 *
 * @param index
 * @return String&
 */
String *NewsService::getArticleTitle(int index) {
    if ((index < 0) || (index >= articleCount)) {
        index = 0;
    }

    return titles[index];
}

/**
 * @brief Initialize the service, registering Task's as necessary.
 *
 * @param scheduler
 */
void NewsService::init(Scheduler *scheduler) {
    Service::init(scheduler);

    newsUpdateTask.setCallback(std::bind(&NewsService::newsUpdate, this));
    newsUpdateTask.setInterval(TASK_MINUTE * 15);
    newsUpdateTask.setIterations(TASK_FOREVER);
    newsUpdateTask.disable();
    scheduler->addTask(newsUpdateTask);
}

/**
     * @brief Retrieve latest news headlines
 */
void NewsService::newsUpdate() {
    Logger &logger = Logger::get();

    if (!delayIfPaused(newsUpdateTask)) {
        logger.println("Attempting News Update");

        String url(BASE_URL);
        url += NEWS_API_KEY;

        NetworkUtils::httpGet(url, [&](int httpResponse, Stream& responseStream) {
            if (httpResponse > 0) {
                StaticJsonDocument<64> jsonFilter;
                jsonFilter["articles"][0]["title"] = true;

                StaticJsonDocument<1024> jsonResponse;
                deserializeJson(jsonResponse, responseStream, DeserializationOption::Filter(jsonFilter));

                auto articles = jsonResponse["articles"].as<JsonArray>();
                logger.printf("Received %d news articles\n", articles.size());

                logger.println("Freeing previous articles");
                if (articleCount > 0) {
                    for (int i = 0; i < articleCount; i++) {
                        logger.printf("Freeing article: %s\n", titles[i]->c_str());
                        delete titles[i];
                    }

                    articleCount = 0;
                }

                articleCount = articles.size() > MAX_TITLES ? MAX_TITLES : articles.size();
                for (int i = 0; i < articleCount; i++) {
                    titles[i] = new String((String) articles[i]["title"].as<String>());

                    // Trim the news source from the article title
                    titles[i]->remove(titles[i]->lastIndexOf('-'));
                    titles[i]->trim();
                    titles[i]->toUpperCase(); // Avoid descenders

                    // logger.printf("Received article[%d] = [%p] %s\n", i, titles[i], titles[i]->c_str());
                }

            } else {
                logger.printf("News update failed with code: %d\n", httpResponse);
            }
        });
    }
}

/**
 * @brief Receives Wifi-related events.
 *
 * @param event
 * @param info
 */
void NewsService::onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    Logger::get().println("NewsService received wifi event");
    switch (event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            newsUpdateTask.enable();
            break;

        case SYSTEM_EVENT_STA_LOST_IP:
            newsUpdateTask.disable();
            break;

        default:
            break;
    }
}
