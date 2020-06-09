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
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiUtilities.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>
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
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.1f, 1.0f
        };
        vertexBuffer = RenderApiFactory::createVertexBuffer(vertices, sizeof(vertices));
        BufferLayout createLayout = {
            {ShaderDataType::Float3, "attrPosition"},
            {ShaderDataType::Float4, "attrColor"}
        };
        vertexBuffer->setLayout(createLayout);
        const BufferLayout &layout = vertexBuffer->getLayout();
        uint32_t index = 0;
        for (const auto &element : layout) {
            glEnableVertexAttribArray(index);
            OpenGlDataType openGlDataType = OpenGlShader::shaderDataTypeToOpenGlDataType(element.type);
            glVertexAttribPointer(index, openGlDataType.count, 
                openGlDataType.type,
                element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(),
                reinterpret_cast<const void*>((intptr_t)element.offset));
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        indexBuffer = RenderApiFactory::createIndexBuffer(indices, sizeof(indices)/sizeof(uint32_t));

        std::string vertexSource = R"(
            #version 330 core
            layout(location = 0) in vec3 attrPosition;
            layout(location = 1) in vec4 attrColor;
            out vec3 vecPosition;
            out vec4 vecColor;
            void main() {
                vecPosition = attrPosition;
                vecColor = attrColor;
                gl_Position = vec4(vecPosition, 1.0);
            }
        )";
        std::string fragmentSource = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 vecPosition;
            in vec4 vecColor;
            void main() {
                color = vecColor;
            }
        )";
        shader = RenderApiFactory::createShader(vertexSource, fragmentSource);
    }

    Application::~Application() {}

    void Application::run() {
        while (isRunning) {
            glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
