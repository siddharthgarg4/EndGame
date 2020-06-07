//
//  Application.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Application.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

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
            pushOverlay(new DebugOverlay());
            hasDebugOverlay = true;
        }
        //creating a triangle
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f 
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        unsigned int indices[3] = { 0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSource = R"(
            #version 330 core
            layout(location = 0) in vec3 attrPosition;
            out vec3 vecPosition;
            void main() {
                vecPosition = attrPosition;
                gl_Position = vec4(vecPosition, 1.0);

            }
        )";
        std::string fragmentSource = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 vecPosition;
            void main() {
                color = vec4(vecPosition * 0.5 + 0.5, 1.0);
            }
        )";
        shader = RenderApiFactory::createShader(vertexSource, fragmentSource);
    }

    Application::~Application() {
        delete shader;
    }

    void Application::run() {
        while (isRunning) {
            glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (Layer *layer : applicationLayers) {
                layer->onUpdate();
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
