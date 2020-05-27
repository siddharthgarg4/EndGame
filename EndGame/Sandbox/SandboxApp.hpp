//
//  SandboxApp.hpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef SandboxApp_hpp
#define SandboxApp_hpp
#include <EndGame/EndGame.h>

class Sandbox : public EndGame::Application {
    public:
        Sandbox() {}
        ~Sandbox() {}
};

//custom run the application as per the client
EndGame::Application *EndGame::createApplication() {
    return new Sandbox();
}

#endif
