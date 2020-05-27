//
//  EntryPoint.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "EntryPoint.hpp"

int main() {
    EndGame::LogSubSystem::init();
    auto application = EndGame::createApplication();
    application->run();
    delete application;
}
