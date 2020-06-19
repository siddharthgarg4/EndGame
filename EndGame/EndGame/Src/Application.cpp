//
//  Application.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Application.hpp"
//^ temporary
#include <EndGame/Src/EndGamePCH.hpp>
//temporary
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderCommand.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/Renderer.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

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
        //MARK: blue shader
        blueVertexArray = RenderApiFactory::createVertexArray();
        float squareVertices[3 * 4]  = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };
        std::shared_ptr<VertexBuffer> blueVertexBuffer = RenderApiFactory::createVertexBuffer(squareVertices, sizeof(squareVertices));
        blueVertexBuffer->setLayout({
            {ShaderDataType::Float3, "attrPosition"}
        });
        blueVertexArray->addVertexBuffer(blueVertexBuffer);
        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> blueIndexBuffer = RenderApiFactory::createIndexBuffer(squareIndices, sizeof(squareIndices)/sizeof(uint32_t));
        blueVertexArray->setIndexBuffer(blueIndexBuffer);
        //creating vertex array
        vertexArray = RenderApiFactory::createVertexArray();
        //creating vertex buffer
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.1f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.1f, 1.0f
        };
        std::shared_ptr<VertexBuffer> vertexBuffer = RenderApiFactory::createVertexBuffer(vertices, sizeof(vertices));
        BufferLayout createLayout = {
            {ShaderDataType::Float3, "attrPosition"},
            {ShaderDataType::Float4, "attrColor"}
        };
        vertexBuffer->setLayout(createLayout);
        //binding vertex buffer to vertex array
        vertexArray->addVertexBuffer(vertexBuffer);
        //creating index buffer
        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer = RenderApiFactory::createIndexBuffer(indices, sizeof(indices)/sizeof(uint32_t));
        //binding index buffer to vertex array
        vertexArray->setIndexBuffer(indexBuffer);

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
        std::string blueVertexSource = R"(
                #version 330 core
                layout(location = 0) in vec3 attrPosition;
                out vec3 vecPosition;
                void main() {
                    vecPosition = attrPosition;
                    gl_Position = vec4(vecPosition, 1.0);
                }
            )";
        std::string blueFragmentSource = R"(
                #version 330 core
                layout(location = 0) out vec4 color;
                in vec3 vecPosition;
                void main() {
                    color = vec4(0.2, 0.3, 0.8, 1.0);
                }
            )";
        blueShader = RenderApiFactory::createShader(blueVertexSource, blueFragmentSource);
    }

    Application::~Application() {}

    void Application::run() {
        while (isRunning) {
            RenderCommand::clear();
            RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            Renderer::beginScene();
            // glClearColor(0.1, 0.1, 0.1, 1);
			// glClear(GL_COLOR_BUFFER_BIT);

            blueShader->bind();
            Renderer::submit(blueVertexArray);
            // blueVertexArray->bind();
            // glDrawElements(GL_TRIANGLES, blueVertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
            shader->bind();
            Renderer::submit(vertexArray);
            // vertexArray->bind();
            // glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

            Renderer::endScene();

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
