//
//  Renderer2D.cpp
//  
//
//  Created by Siddharth on 09/07/20.
//

#include "Renderer2D.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderCommand.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

namespace EndGame {
    //initializing the storage
    Renderer2DStorage *Renderer2D::storage = new Renderer2DStorage();

    void Renderer2D::init() {
        storage->quadVertexArray = RenderApiFactory::createVertexArray();
        //vertex buffer
        float quadVertices[5 * 4]  = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        std::shared_ptr<VertexBuffer> quadVertexBuffer = RenderApiFactory::createVertexBuffer(quadVertices, sizeof(quadVertices));
        quadVertexBuffer->setLayout({
            {ShaderDataType::Float3, "attrPosition"},
            {ShaderDataType::Float2, "attrTextureCoord"}
        });
        storage->quadVertexArray->addVertexBuffer(quadVertexBuffer);
        //index buffer
        uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> quadIndexBuffer = RenderApiFactory::createIndexBuffer(quadIndices, sizeof(quadIndices)/sizeof(uint32_t));
        storage->quadVertexArray->setIndexBuffer(quadIndexBuffer);
        storage->quadShader = RenderApiFactory::createShader("Sandbox/Quad.glsl");
    }

    void Renderer2D::shutdown() {
        delete storage;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        storage->quadShader->bind();
        storage->quadShader->uploadUniform("u_viewProjection", camera.getViewProjectionMatrix());
        storage->quadShader->uploadUniform("u_transform", glm::mat4(1.0f));
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(QuadRendererData data) {
        storage->quadShader->bind();
        storage->quadShader->uploadUniform("u_color", data.color);
        storage->quadVertexArray->bind();
        RenderCommand::drawIndexed(storage->quadVertexArray);
    }
}