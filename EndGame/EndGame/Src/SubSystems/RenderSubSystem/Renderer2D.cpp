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
    Renderer2DStorage *Renderer2D::storage = nullptr;

    void Renderer2D::init() {
        //init storage
        storage = new Renderer2DStorage();
        storage->quadVertexArray = RenderApiFactory::createVertexArray();
        //vertex buffer
        storage->quadVertexBuffer = RenderApiFactory::createVertexBuffer(storage->maxQuadVerticesPerDraw * sizeof(QuadVertexData));
        storage->quadVertexBuffer->setLayout({
            {ShaderDataType::Float3, "attrPosition"},
            {ShaderDataType::Float4, "attrColor"},
            {ShaderDataType::Float2, "attrTextureCoord"}
        });
        storage->quadVertexArray->addVertexBuffer(storage->quadVertexBuffer);
        //batch rendering setup
        storage->quadVertexBufferDataBase = new QuadVertexData[storage->maxQuadVerticesPerDraw];
        //index buffer
        uint32_t *quadIndices = new uint32_t[storage->maxQuadIndicesPerDraw];
        for (uint32_t offset=0, i=0; i<storage->maxQuadIndicesPerDraw; i+=6) {
            quadIndices[i+0] = offset+0;
            quadIndices[i+1] = offset+1;
            quadIndices[i+2] = offset+2;
            quadIndices[i+3] = offset+2;
            quadIndices[i+4] = offset+3;
            quadIndices[i+5] = offset+0;
            offset+=4;
        }
        std::shared_ptr<IndexBuffer> quadIndexBuffer = RenderApiFactory::createIndexBuffer(storage->maxQuadIndicesPerDraw * sizeof(uint32_t), quadIndices);
        storage->quadVertexArray->setIndexBuffer(quadIndexBuffer);
        delete[] quadIndices;
        //white texture
        uint32_t whiteTextureData = 0xffffffff;
        storage->whiteTexture = RenderApiFactory::createTexture2D(1, 1, &whiteTextureData);
        //shader
        storage->quadShader = RenderApiFactory::createShader("Sandbox/Quad.glsl");
        storage->quadShader->bind();
        storage->quadShader->uploadUniform("u_texture", 0);
    }

    void Renderer2D::shutdown() {
        delete[] storage->quadVertexBufferDataBase;
        delete storage;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        storage->quadShader->bind();
        storage->quadShader->uploadUniform("u_viewProjection", camera.getViewProjectionMatrix());
        beginNewBatch();
    }

    void Renderer2D::endScene() {
        flushVertexBuffer();
    }

    void Renderer2D::flushVertexBuffer() {
        storage->quadShader->bind();
        storage->quadVertexBuffer->setData(storage->quadVertexBufferDataSize * sizeof(QuadVertexData), storage->quadVertexBufferDataBase);
        uint32_t numberOfQuads = storage->quadVertexBufferDataSize/4;
        storage->quadVertexArray->bind();
        //each quad is 6 indices (2 triangles)
        RenderCommand::drawIndexed(storage->quadVertexArray, numberOfQuads*6);
    }

    void Renderer2D::drawQuad(QuadRendererData data, bool shouldRotate) {
        if (storage->quadVertexBufferDataSize >= storage->maxQuadVerticesPerDraw) {
            flushVertexBuffer();
            beginNewBatch();
        }
        addQuadVertexData(QuadVertexData(data.position, data.color, {0.0f, 0.0f}));
        addQuadVertexData(QuadVertexData({data.position.x + data.size.x, data.position.y, 0.0f}, data.color, {1.0f, 0.0f}));
        addQuadVertexData(QuadVertexData({data.position.x + data.size.x, data.position.y + data.size.y, 0.0f}, data.color, {1.0f, 1.0f}));
        addQuadVertexData(QuadVertexData({data.position.x, data.position.y + data.size.y, 0.0f}, data.color, {0.0f, 1.0f}));
    }

    void Renderer2D::beginNewBatch() {
        storage->quadVertexBufferDataSize = 0;
    }

    void Renderer2D::addQuadVertexData(const QuadVertexData &data) {
        storage->quadVertexBufferDataBase[storage->quadVertexBufferDataSize] = data;
        storage->quadVertexBufferDataSize++;
    }
}