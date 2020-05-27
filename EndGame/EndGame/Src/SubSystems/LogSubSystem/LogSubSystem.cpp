//
//  LogSubSystem.cpp
//  EndGame
//
//  Created by Siddharth on 25/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "LogSubSystem.hpp"

namespace EndGame {
    //defining the loggers
    std::shared_ptr<spdlog::logger> LogSubSystem::engineLogger;
    std::shared_ptr<spdlog::logger> LogSubSystem::clientLogger;

    //initilaizing the loggers
    void LogSubSystem::init() {
        spdlog::set_pattern("%^[%T] %n [%l]: %v%$");

        LogSubSystem::engineLogger = spdlog::stdout_color_mt("ENDGAME");
        engineLogger->set_level(spdlog::level::trace);

        clientLogger = spdlog::stdout_color_mt("APP");
        clientLogger->set_level(spdlog::level::trace);
    }
}
