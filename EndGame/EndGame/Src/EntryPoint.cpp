//
//  EntryPoint.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "EntryPoint.hpp"
#include <iostream>

int main() {
    EndGame::LogSubSystem::init();
    EG_ENGINE_ERROR("error");
    EG_ENGINE_WARNING("warn");
    EG_ENGINE_TRACE("trace");
    EG_ENGINE_INFO("info");
    EG_ENGINE_CRITICAL("critical");
    
    EG_ERROR("error");
    EG_WARNING("warn");
    EG_TRACE("trace");
    EG_INFO("info");
    EG_CRITICAL("critical");
    auto application = EndGame::createApplication();
    application->run();
    delete application;
}
