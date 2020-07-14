//
//  SandboxApp2D.cpp
//  EndGame
//
//  Created by Siddharth on 07/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Sandbox2D.hpp"
#include <imgui/include/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), cameraController((1280.0f/720.0f)) {}

Sandbox2D::~Sandbox2D() {}

void Sandbox2D::onAttach() {}

void Sandbox2D::onDetach() {}

void Sandbox2D::onImguiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Color", glm::value_ptr(squareColor));
    ImGui::End();
}

void Sandbox2D::onEvent(EndGame::Event &event) {
    cameraController.onEvent(event);
}

void Sandbox2D::onUpdate(const float &timeSinceStart, const float &dtime) {
    cameraController.onUpdate(timeSinceStart, dtime);
}

void Sandbox2D::onRender(const float &alpha, const float &dtime) {
    cameraController.onRender(alpha, dtime);
    EndGame::RenderCommand::clear();
    EndGame::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    EndGame::Renderer2D::beginScene(cameraController.getCamera());
    std::shared_ptr<EndGame::Texture2D> texture = EndGame::RenderApiFactory::createTexture2D("Sandbox/assets/spongebob.png");
    std::shared_ptr<EndGame::Texture2D> appleTexture = EndGame::RenderApiFactory::createTexture2D("Sandbox/assets/apple.png");
    // EndGame::Renderer2D::drawQuad();
    // EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({0.5f, 0.0f, 0.4f}, 45.0f, {1.0f, 1.0f}, texture), true);
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({5.5f, 0.5f, 0.6f}, 0.0f, {1.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}));
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({5.5f, 0.5f, 0.7f}, 0.0f, {1.5f, 0.5f}, {0.2f, 0.3f, 0.9f, 1.0f}));

    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({-5.5f, 0.5f, 0.7f}, 0.0f, {1.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}));
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({-5.5f, 0.5f, 0.6f}, 0.0f, {1.5f, 0.5f}, {0.2f, 0.3f, 0.9f, 1.0f}));

    static float rotation = 0.0f;
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({-15.5f, 0.5f, 0.6f}, rotation, {2.5f, 2.5f}, texture, 2.0f), true);
    rotation+=1.0f;

    int counter = 0;
    for (float y= -10.0f; y<10.0f; y+=0.5f) {
        for (float x= -10.0f; x<10.0f; x+=0.5f) {
            if (counter%2 == 0) {
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x, y, 0.9}, 0.0f, {0.45f, 0.45f}, texture, 4.0f, {0.2f, 0.9f, 0.3f, 1.0f}));
            } else {
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x, y, 0.9}, 0.0f, {0.45f, 0.45f}, {0.2f, 0.3f, 0.9f, 1.0f}));
            }
            counter++;
            // EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x, y}, 0.0f, {0.45f, 0.45f}, {0.2f, 0.3f, 0.9f, 1.0f}));
        }
    }
    EndGame::Renderer2D::endScene();
}