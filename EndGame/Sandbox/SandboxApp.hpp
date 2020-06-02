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

class ExampleLayer : public EndGame::Layer {
    public:
        ExampleLayer() : Layer("Example") {}
        void onUpdate() override {
            EG_INFO("ExampleLayer::Update");
        }
        void onEvent(EndGame::Event &event) override {
            EG_TRACE("{0}", event);
        }
};

class Sandbox : public EndGame::Application {
    public:
        Sandbox() {
            pushLayer(new ExampleLayer());
        }
        ~Sandbox() {}
};

//custom run the application as per the client
EndGame::Application *EndGame::createApplication() {
    return new Sandbox();
}

#endif
