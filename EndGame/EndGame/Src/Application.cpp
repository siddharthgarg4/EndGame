//
//  Application.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Application.hpp"
#include <EndGame/Src/EndGamePCH.hpp>
#include <glfw/glfw3.h>

namespace EndGame {
    //need to declare static variables and cannot init in definitions
    Application *Application::appInstance = nullptr;

    Application::Application(bool shouldAddDebugOverlay) {
        EG_ENGINE_ASSERT(!appInstance, "Application already exists!");
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
            pushOverlay(new DebugOverlay());
            hasDebugOverlay = true;
        }
    }

    Application::~Application() {}

    void Application::run() {
        //timestep setup
        const float maxFrameTime = 0.25f;
        const float dtime = 0.01f;
        //variables for timestep
        float time = 0.0f;
        float currentTime = 0.0f;
        float accumulator = 0.0f;
        while (isRunning) {
            float newTime = float(glfwGetTime());
            float frameTime = newTime - currentTime;
            currentTime = newTime;
            if (frameTime > maxFrameTime) {
                //prevents locking out due to slow refresh rate
                frameTime = maxFrameTime;
            }
            accumulator += frameTime;
            while (accumulator >= dtime) {
                for (Layer *layer : applicationLayers) {
                    //updating the states per layer
                    layer->onUpdate(time, dtime);
                }
                time += dtime;
                accumulator -= dtime;
            }
            //allows interpolation, usually done with states
            const float alpha = accumulator / dtime;
            //actual rendering
            for (Layer *layer : applicationLayers) {
                //passing alpha and timestep to allow interpolation during rendering
                layer->onRender(alpha, dtime);
            }
            if (hasDebugOverlay) {
                //application has debug overlay
                DebugOverlay::preImguiRender();
                for (Layer *layer : applicationLayers) {
                    layer->onImguiRender();
                }
                DebugOverlay::postImguiRender();
            }
			window->onUpdate();
        }
    }

    //MARK: layer functions
    void Application::pushLayer(Layer *layer) {
        applicationLayers.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *overlay) {
        applicationLayers.pushOverlay(overlay);
    }
}
