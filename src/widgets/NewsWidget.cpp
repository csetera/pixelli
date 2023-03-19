/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#include "NewsWidget.h"

#include <logging/Logger.h>
#include <services/NewsService.h>
#include <settings/SettingsManager.h>

/**
 * @brief Start displaying this Widget, scheduling updates as necessary.
 */
void NewsWidget::startDisplay() {
    color = SettingsManager::get().getNewsColor();
    displayValue.clear();

    NewsService *newsService = (NewsService *) getService(NewsService::NAME);
    if (newsService->getArticleCount() > 0) {
        if (storyIndex >= newsService->getArticleCount()) {
            storyIndex = 0;
        }

        String *title = newsService->getArticleTitle(storyIndex);
        // Logger::get().printf("NewsWidget title[%d] = [%p]\n", storyIndex, title);
        displayValue.concat(title->c_str());

        storyIndex++;

    } else {
        displayValue.concat("No News");
    }

    ScrollingTextWidget::startDisplay();
}
