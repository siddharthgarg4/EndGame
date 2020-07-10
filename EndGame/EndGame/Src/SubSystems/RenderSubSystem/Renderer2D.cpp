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
        //white texture
        uint32_t whiteTextureData = 0xffffffff;
        storage->whiteTexture = RenderApiFactory::createTexture2D(1, 1, &whiteTextureData);
        //shader
        storage->quadShader = RenderApiFactory::createShader("Sandbox/Quad.glsl");
        storage->quadShader->bind();
        storage->quadShader->uploadUniform("u_texture", 0);
    }

    void Renderer2D::shutdown() {
        delete storage;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        storage->quadShader->bind();
        storage->quadShader->uploadUniform("u_viewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(QuadRendererData data, bool shouldRotate) {
        storage->quadShader->bind();
        // //color and texture
        storage->quadShader->uploadUniform("u_color", data.color);
        if (data.texture == nullptr) {
            storage->whiteTexture->bind();
        } else {
            data.texture->bind();
        }
        //transforms
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), data.position);
        if (shouldRotate) {
            transform *= glm::rotate(glm::mat4(1.0f), glm::radians(data.rotation), {0, 0, 1});
        }
        transform *= glm::scale(glm::mat4(1.0f), {data.size.x, data.size.y, 1.0f});
        storage->quadShader->uploadUniform("u_transform", transform);
        //actual drawing
        storage->quadVertexArray->bind();
        RenderCommand::drawIndexed(storage->quadVertexArray);
    }
}