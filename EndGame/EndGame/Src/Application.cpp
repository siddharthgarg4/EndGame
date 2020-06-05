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

    //need to declare static variables and cannot init in definitions
    Application *Application::appInstance = nullptr;

    Application::Application(bool shouldAddDebugOverlay) {
        EG_ENGINE_ASSERT(appInstance, "Application already exists!");
        appInstance = this;
        window = std::unique_ptr<Window>(Window::create());
        window->setEventCallBack([this](Event &event) {
            //setting event call back
            EventDispatcher dispatcher(event);
            dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent &event) {
                //setting dispatch function to call if event is window close event
                isRunning = false;
                return true;
            });
            for (auto iterator = applicationLayers.end(); iterator != applicationLayers.begin();) {
                //since we begin from end we need to get the layer before the end
                --iterator;
                //we get each layer by dereferencing the iterator
                (*iterator)->onEvent(event);
                if (event.isHandled) {
                    break;
                }
            }
        });
        if (shouldAddDebugOverlay) {
            debugOverlay = new DebugOverlay();
            pushLayer(debugOverlay);
        }
    }

    Application::~Application() {}

    void Application::run() {
        while (isRunning) {
            glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
            for (Layer *layer : applicationLayers) {
                layer->onUpdate();
            }
            if (debugOverlay != nullptr) {
                //application has debug overlay
                debugOverlay->preRender();
                for (Layer *layer : applicationLayers) {
                    layer->onImguiRender();
                }
                debugOverlay->postRender();
            }
			window->onUpdate();
        }
    }

    //MARK: layer functions

    void Application::pushLayer(Layer *layer) {
        applicationLayers.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer *overlay) {
        applicationLayers.pushOverlay(overlay);
        overlay->onAttach();
    }
}
