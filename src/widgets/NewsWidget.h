/**********************************************************************************
 * Copyright (C) 2023 Craig Setera
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 **********************************************************************************/
#pragma once

#include "ScrollingTextWidget.h"

/**
 * @brief A displayable Widget capable of scrolling a news article's title
 * on the matrix.
 */
class NewsWidget : public ScrollingTextWidget {
public:
    static constexpr char *NAME = (char*) "News";

    NewsWidget(Scheduler *scheduler) : ScrollingTextWidget(scheduler), storyIndex(0) { }

    /**
     * @brief Return the name of the Widget.
     *
     * @return const char*
     */
    virtual const char* name() {
        return NewsWidget::NAME;
    }

    /**
     * @brief Start displaying this Widget, scheduling updates as necessary.
     */
    virtual void startDisplay();

private:
    int storyIndex;
};
