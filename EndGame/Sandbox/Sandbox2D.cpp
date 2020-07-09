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
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({1.0f, 1.5f}, 0.0f, {1.5f, 0.5f}, {0.2f, 0.3f, 0.9f, 1.0f}));
    EndGame::Renderer2D::endScene();
}
