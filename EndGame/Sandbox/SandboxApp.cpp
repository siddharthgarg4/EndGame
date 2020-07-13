//
//  SandboxApp.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "SandboxApp.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/include/imgui.h>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() : Layer("Example Layer"), cameraController((1280.0f/720.0f)) {
    //MARK: flat color shader
    flatColorVertexArray = EndGame::RenderApiFactory::createVertexArray();
    float squareVertices[5 * 4]  = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    std::shared_ptr<EndGame::VertexBuffer> flatColorVertexBuffer = EndGame::RenderApiFactory::createVertexBuffer(sizeof(squareVertices), squareVertices);
    flatColorVertexBuffer->setLayout({
        {EndGame::ShaderDataType::Float3, "attrPosition"},
        {EndGame::ShaderDataType::Float2, "attrTextureCoord"}
    });
    flatColorVertexArray->addVertexBuffer(flatColorVertexBuffer);
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0};
    std::shared_ptr<EndGame::IndexBuffer> flatColorIndexBuffer = EndGame::RenderApiFactory::createIndexBuffer(sizeof(squareIndices), squareIndices);
    flatColorVertexArray->setIndexBuffer(flatColorIndexBuffer);
    //creating vertex array
    vertexArray = EndGame::RenderApiFactory::createVertexArray();
    //creating vertex buffer
    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.1f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.1f, 1.0f
    };
    std::shared_ptr<EndGame::VertexBuffer> vertexBuffer = EndGame::RenderApiFactory::createVertexBuffer(sizeof(vertices), vertices);
    EndGame::BufferLayout createLayout = {
        {EndGame::ShaderDataType::Float3, "attrPosition"},
        {EndGame::ShaderDataType::Float4, "attrColor"}
    };
    vertexBuffer->setLayout(createLayout);
    //binding vertex buffer to vertex array
    vertexArray->addVertexBuffer(vertexBuffer);
    //creating index buffer
    uint32_t indices[3] = { 0, 1, 2 };
    std::shared_ptr<EndGame::IndexBuffer> indexBuffer = EndGame::RenderApiFactory::createIndexBuffer(sizeof(indices), indices);
    //binding index buffer to vertex array
    vertexArray->setIndexBuffer(indexBuffer);
    auto shader = shaderLib.load("Sandbox/Triangle.glsl");
    auto gridShader = shaderLib.load("Sandbox/Grid.glsl");
    auto textureShader = shaderLib.load("Sandbox/Texture.glsl");
    texture = EndGame::RenderApiFactory::createTexture2D("Sandbox/assets/spongebob.png");
    semiTexture = EndGame::RenderApiFactory::createTexture2D("Sandbox/assets/apple.png");
    textureShader->uploadUniform("u_texture", 0);
}

void ExampleLayer::onUpdate(const float &timeSinceStart, const float &dtime) {
    cameraController.onUpdate(timeSinceStart, dtime);
}

void ExampleLayer::onEvent(EndGame::Event &event) {
    cameraController.onEvent(event);
}

void ExampleLayer::onRender(const float &alpha, const float &dtime) {
    cameraController.onRender(alpha, dtime);
    EndGame::RenderCommand::clear();
    EndGame::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    EndGame::Renderer::beginScene(cameraController.getCamera());
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    std::shared_ptr<EndGame::Shader> flatColorShader = shaderLib.get("Grid");
    std::shared_ptr<EndGame::Shader> shader = shaderLib.get("Triangle");
    std::shared_ptr<EndGame::Shader> textureShader = shaderLib.get("Texture");
    flatColorShader->bind();
    flatColorShader->uploadUniform("u_flatColor", flatColor);
    flatColorShader->unbind();
    for (int y=0; y<10; y++) {
        for (int x=0; x<10; x++) {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f * x, 0.11f * y, 0.0f)) * scale;
            EndGame::Renderer::submit(flatColorShader, flatColorVertexArray, transform);
        }
    }
    EndGame::Renderer::submit(shader, vertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 0.0f)));
    texture->bind();
    EndGame::Renderer::submit(textureShader, flatColorVertexArray);
    semiTexture->bind();
    EndGame::Renderer::submit(textureShader, flatColorVertexArray);
    EndGame::Renderer::endScene();
}

void ExampleLayer::onImguiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", glm::value_ptr(flatColor));
    ImGui::End();
}
