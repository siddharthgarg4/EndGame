//
//  Application.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Application.hpp"
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>
#include <EndGame/Src/EndGamePCH.hpp>
#include <GLFW/glfw3.h>

namespace EndGame {

    Application::Application() {
        window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() {}

    void Application::run() {
        while (isRunning) {
            glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->onUpdate();
        }
    }
}
