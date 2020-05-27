//
//  Application.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Application.hpp"

namespace EndGame {

    Application::Application() {}
    Application::~Application() {}

    void Application::run() {
        WindowResizeEvent event(1280, 720);
        if (event.isEventInCategory(EventCategory::EventCategoryApplication)) {
            EG_TRACE(event);
        }
        if (event.isEventInCategory(EventCategory::EventCategoryInput)) {
            EG_TRACE(event);
        }
        while (true);
    }
}
