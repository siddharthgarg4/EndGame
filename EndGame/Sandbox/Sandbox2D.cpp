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

void Sandbox2D::onAttach() {
    vertexArray = EndGame::RenderApiFactory::createVertexArray();
    //vertex buffer
    float squareVertices[5 * 4]  = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    std::shared_ptr<EndGame::VertexBuffer> vertexBuffer = EndGame::RenderApiFactory::createVertexBuffer(squareVertices, sizeof(squareVertices));
    vertexBuffer->setLayout({
        {EndGame::ShaderDataType::Float3, "attrPosition"},
        {EndGame::ShaderDataType::Float2, "attrTextureCoord"}
    });
    vertexArray->addVertexBuffer(vertexBuffer);
    //index buffer
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0};
    std::shared_ptr<EndGame::IndexBuffer> indexBuffer = EndGame::RenderApiFactory::createIndexBuffer(squareIndices, sizeof(squareIndices)/sizeof(uint32_t));
    vertexArray->setIndexBuffer(indexBuffer);
    auto shader = shaderLib.load("Sandbox/Sandbox2D.glsl");
}

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
    EndGame::Renderer::beginScene(cameraController.getCamera());
    std::shared_ptr<EndGame::Shader> shader = shaderLib.get("Sandbox2D");
    shader->bind();
    shader->uploadUniform("u_color", squareColor);
    EndGame::Renderer::submit(shader, vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
}
