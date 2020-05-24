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
    auto application = EndGame::createApplication();
    application->run();
    delete application;
}
