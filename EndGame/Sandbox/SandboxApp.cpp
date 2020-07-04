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

ExampleLayer::ExampleLayer() : Layer("Example Layer"), camera(-1.6f, 1.6f, -0.9f, 0.9f) {
    //MARK: flat color shader
    flatColorVertexArray = EndGame::RenderApiFactory::createVertexArray();
    float squareVertices[3 * 4]  = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    std::shared_ptr<EndGame::VertexBuffer> flatColorVertexBuffer = EndGame::RenderApiFactory::createVertexBuffer(squareVertices, sizeof(squareVertices));
    flatColorVertexBuffer->setLayout({
        {EndGame::ShaderDataType::Float3, "attrPosition"}
    });
    flatColorVertexArray->addVertexBuffer(flatColorVertexBuffer);
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0};
    std::shared_ptr<EndGame::IndexBuffer> flatColorIndexBuffer = EndGame::RenderApiFactory::createIndexBuffer(squareIndices, sizeof(squareIndices)/sizeof(uint32_t));
    flatColorVertexArray->setIndexBuffer(flatColorIndexBuffer);
    //creating vertex array
    vertexArray = EndGame::RenderApiFactory::createVertexArray();
    //creating vertex buffer
    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.1f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.1f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.1f, 1.0f
    };
    std::shared_ptr<EndGame::VertexBuffer> vertexBuffer = EndGame::RenderApiFactory::createVertexBuffer(vertices, sizeof(vertices));
    EndGame::BufferLayout createLayout = {
        {EndGame::ShaderDataType::Float3, "attrPosition"},
        {EndGame::ShaderDataType::Float4, "attrColor"}
    };
    vertexBuffer->setLayout(createLayout);
    //binding vertex buffer to vertex array
    vertexArray->addVertexBuffer(vertexBuffer);
    //creating index buffer
    uint32_t indices[3] = { 0, 1, 2 };
    std::shared_ptr<EndGame::IndexBuffer> indexBuffer = EndGame::RenderApiFactory::createIndexBuffer(indices, sizeof(indices)/sizeof(uint32_t));
    //binding index buffer to vertex array
    vertexArray->setIndexBuffer(indexBuffer);
    shaderLib.load("Sandbox/Triangle.glsl");
    shaderLib.load("Sandbox/Grid.glsl");
}

std::pair<glm::vec3, float> ExampleLayer::cameraTransformAfterUpdate(const float &dtime) {
    std::pair<glm::vec3, float> currentCameraTransform (cameraPosition, cameraRotation);
    if (EndGame::Input::isKeyPressed(EG_KEY_LEFT)) {
        currentCameraTransform.first.x -= cameraMoveSpeed * dtime;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_RIGHT)) {
        currentCameraTransform.first.x += cameraMoveSpeed * dtime;
    }

    if (EndGame::Input::isKeyPressed(EG_KEY_UP)) {
        currentCameraTransform.first.y += cameraMoveSpeed * dtime;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_DOWN)) {
        currentCameraTransform.first.y -= cameraMoveSpeed * dtime;
    }
    
    if (EndGame::Input::isKeyPressed(EG_KEY_A)) {
        currentCameraTransform.second += cameraRotationSpeed * dtime;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_D)) {
        currentCameraTransform.second -= cameraRotationSpeed * dtime;
    }
    return currentCameraTransform;
}

void ExampleLayer::onUpdate(const float &timeSinceStart, const float &dtime) {
    std::pair<glm::vec3, float> newCameraTranform = cameraTransformAfterUpdate(dtime);
    cameraPosition = newCameraTranform.first;
    cameraRotation = newCameraTranform.second;
}

void ExampleLayer::onRender(const float &alpha, const float &dtime) {
    std::pair<glm::vec3, float> nextCameraTransform = cameraTransformAfterUpdate(dtime);
    glm::vec3 interpolatedCameraPosition = (cameraPosition * (1-alpha)) + (nextCameraTransform.first * alpha);
    float interpolatedCameraRotation = (cameraRotation * (1-alpha)) + (nextCameraTransform.second * alpha);
    EndGame::RenderCommand::clear();
    EndGame::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    camera.setPosition(interpolatedCameraPosition);
    camera.setRotation(interpolatedCameraRotation);
    EndGame::Renderer::beginScene(camera);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    std::shared_ptr<EndGame::Shader> flatColorShader = shaderLib.get("Grid");
    std::shared_ptr<EndGame::Shader> shader = shaderLib.get("Triangle");
    flatColorShader->bind();
    flatColorShader->uploadUniform("u_flatColor", flatColor);
    flatColorShader->unbind();
    for (int y=0; y<10; y++) {
        for (int x=0; x<10; x++) {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f * x, 0.11f * y, 0.0f)) * scale;
            EndGame::Renderer::submit(flatColorShader, flatColorVertexArray, transform);
        }
    }
    EndGame::Renderer::submit(shader, vertexArray);
    EndGame::Renderer::endScene();
}

void ExampleLayer::onImguiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Color", glm::value_ptr(flatColor));
    ImGui::End();
}