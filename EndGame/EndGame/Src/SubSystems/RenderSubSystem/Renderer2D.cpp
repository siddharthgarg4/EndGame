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
            {ShaderDataType::Float2, "attrTextureCoord"},
            {ShaderDataType::Float, "attrTextureIndex"},
            {ShaderDataType::Float, "attrTilingFactor"}
        });
        storage->quadVertexArray->addVertexBuffer(storage->quadVertexBuffer);
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
        //shader
        storage->quadShader = RenderApiFactory::createShader("Sandbox/Quad.glsl");
        storage->quadShader->bind();
        //setting sampler slots
        std::shared_ptr<int32_t> samplers(new int32_t[storage->maxFragmentTextureSlots], std::default_delete<int[]>());
        for (int32_t i=0; i<storage->maxFragmentTextureSlots; i++) {
            samplers.get()[i] = i;
        }
        storage->quadShader->uploadUniform("u_textures", samplers, storage->maxFragmentTextureSlots);
        //white texture
        uint32_t whiteTextureData = 0xffffffff;
        storage->whiteTexture = RenderApiFactory::createTexture2D(1, 1, &whiteTextureData);
        addTextureSlot(storage->whiteTexture);
    }

    void Renderer2D::shutdown() {
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
        storage->quadVertexBuffer->setData(storage->quadVertexBufferDataSize * sizeof(QuadVertexData), storage->quadVertexBufferData.data());
        storage->quadVertexArray->bind();
        //bind all texture slots
        for (uint32_t i=0; i<storage->textureSlotsDataSize; i++) {
            storage->textureSlots[i]->bind(i);
        }
        //each quad is 6 indices (2 triangles)
        uint32_t numberOfQuads = storage->quadVertexBufferDataSize/4;
        RenderCommand::drawIndexed(storage->quadVertexArray, numberOfQuads*6);
    }

    void Renderer2D::drawQuad(QuadRendererData data, bool shouldRotate) {
        //pushing to local buffer until data can be accomodated
        if (storage->quadVertexBufferDataSize >= storage->maxQuadVerticesPerDraw ||
            storage->textureSlotsDataSize >= storage->maxFragmentTextureSlots) {
            //flush if we reach max quads or max textures
            flushVertexBuffer();
            beginNewBatch();
        }
        //textures - default to white
       float textureIndex = 0.0f;
       if (data.texture != nullptr) {
           //if quad has texture
           for (uint32_t i=1; i<storage->textureSlotsDataSize; i++) {
               if (*storage->textureSlots[i].get() == *data.texture.get()) {
                   textureIndex = (float)i;
                   break;
               }
           }
           //texture hasn't been used before
           if (textureIndex == 0.0f) {
                textureIndex = (float)storage->textureSlotsDataSize;
                addTextureSlot(data.texture);
            }
       }
       //temporary - tiling factor
       const static float tilingFactor = 1.0f;
        addQuadVertexData(QuadVertexData(data.position, data.color, {0.0f, 0.0f}, textureIndex, tilingFactor));
        addQuadVertexData(QuadVertexData({data.position.x + data.size.x, data.position.y, 0.0f}, data.color, {1.0f, 0.0f}, textureIndex, tilingFactor));
        addQuadVertexData(QuadVertexData({data.position.x + data.size.x, data.position.y + data.size.y, 0.0f}, data.color, {1.0f, 1.0f}, textureIndex, tilingFactor));
        addQuadVertexData(QuadVertexData({data.position.x, data.position.y + data.size.y, 0.0f}, data.color, {0.0f, 1.0f}, textureIndex, tilingFactor));
    }

    void Renderer2D::beginNewBatch() {
        storage->quadVertexBufferDataSize = 0;
        storage->textureSlotsDataSize = 0;
    }

    void Renderer2D::addQuadVertexData(const QuadVertexData &data) {
        storage->quadVertexBufferData[storage->quadVertexBufferDataSize] = data;
        storage->quadVertexBufferDataSize++;
    }

    void Renderer2D::addTextureSlot(std::shared_ptr<Texture2D> texture) {
        storage->textureSlots[storage->textureSlotsDataSize] = texture;
        storage->textureSlotsDataSize++;
    }
}