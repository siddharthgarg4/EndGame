//
//  SandboxApp.cpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "SandboxApp.hpp"
#include <glm/gtc/matrix_transform.hpp>

ExampleLayer::ExampleLayer() : Layer("Example Layer"), camera(-1.6f, 1.6f, -0.9f, 0.9f) {
    //MARK: blue shader
    blueVertexArray = EndGame::RenderApiFactory::createVertexArray();
    float squareVertices[3 * 4]  = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    std::shared_ptr<EndGame::VertexBuffer> blueVertexBuffer = EndGame::RenderApiFactory::createVertexBuffer(squareVertices, sizeof(squareVertices));
    blueVertexBuffer->setLayout({
        {EndGame::ShaderDataType::Float3, "attrPosition"}
    });
    blueVertexArray->addVertexBuffer(blueVertexBuffer);
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0};
    std::shared_ptr<EndGame::IndexBuffer> blueIndexBuffer = EndGame::RenderApiFactory::createIndexBuffer(squareIndices, sizeof(squareIndices)/sizeof(uint32_t));
    blueVertexArray->setIndexBuffer(blueIndexBuffer);
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
    std::string vertexSource = R"(
        #version 330 core
        layout(location = 0) in vec3 attrPosition;
        layout(location = 1) in vec4 attrColor;
        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;
        out vec3 vecPosition;
        out vec4 vecColor;
        void main() {
            vecPosition = attrPosition;
            vecColor = attrColor;
            gl_Position = u_viewProjection * u_transform * vec4(vecPosition, 1.0);
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
    shader = EndGame::RenderApiFactory::createShader(vertexSource, fragmentSource);
    std::string blueVertexSource = R"(
            #version 330 core
            layout(location = 0) in vec3 attrPosition;
            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;
            out vec3 vecPosition;
            void main() {
                vecPosition = attrPosition;
                gl_Position = u_viewProjection * u_transform * vec4(vecPosition, 1.0);
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
    blueShader = EndGame::RenderApiFactory::createShader(blueVertexSource, blueFragmentSource);
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
    for (int y=0; y<10; y++) {
        for (int x=0; x<10; x++) {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f * x, 0.11f * y, 0.0f)) * scale;
            EndGame::Renderer::submit(blueShader, blueVertexArray, transform);
        }
    }
    EndGame::Renderer::submit(shader, vertexArray);
    EndGame::Renderer::endScene();
}