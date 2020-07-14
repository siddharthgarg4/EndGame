//
//  Renderer2D.hpp
//  
//
//  Created by Siddharth on 09/07/20.
//

#ifndef Renderer2D_hpp
#define Renderer2D_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/VertexArray.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OrthographicCamera.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Texture.h>

namespace EndGame {

    struct QuadVertexData {
        //how data is arranged in vertex buffers
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 textureCoords;
        float textureIndex;
        float tilingFactor;
        //constructors
        QuadVertexData() {}
        QuadVertexData(glm::vec3 position, glm::vec4 color, glm::vec2 textureCoords, float textureIndex, float tilingFactor) : 
            position(position), color(color), textureCoords(textureCoords), textureIndex(textureIndex), tilingFactor(tilingFactor) {}
    };

    struct Renderer2DStorage {
        static const uint32_t maxFragmentTextureSlots = 16; //todo: RenderCommand::getMaxFragmentTextureSlots();
        static const uint32_t maxQuadPerDraw = 10000;
        static const uint32_t maxQuadVerticesPerDraw = maxQuadPerDraw * 4;
        static const uint32_t maxQuadIndicesPerDraw = maxQuadPerDraw * 6;
        //shading assets
        std::shared_ptr<Shader> quadShader = nullptr;
        std::shared_ptr<VertexBuffer> quadVertexBuffer = nullptr;
        std::shared_ptr<VertexArray> quadVertexArray = nullptr;
        //batch rendering data
        glm::vec4 quadVertexDefaultPositions[4] = {
            {-0.5f, -0.5f, 0.0f, 1.0f},
            { 0.5f, -0.5f, 0.0f, 1.0f},
            { 0.5f,  0.5f, 0.0f, 1.0f},
            {-0.5f,  0.5f, 0.0f, 1.0f}
        };
        //render data for batch rendering (raw pointers for speed)
        uint32_t quadVertexBufferDataSize = 0;
        std::array<QuadVertexData, maxQuadVerticesPerDraw> quadVertexBufferData;
        uint32_t textureSlotsDataSize = 0;
        std::array<std::shared_ptr<Texture2D>, maxFragmentTextureSlots> textureSlots;
    };

    struct QuadRendererData {
         //data as taken in by renderer to draw the quads
        //z represents priority towards the screen with 1.0 being max, 0.0 min, ties are broken with what is drawn first is on top
        glm::vec3 position = glm::vec3(0.0f);
        float rotation = 0.0f;
        glm::vec2 size = glm::vec2(1.0f);
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
        std::shared_ptr<Texture2D> texture = nullptr;
        float tilingFactor = 1.0f;
        //constructors
        QuadRendererData() {}
        QuadRendererData(const glm::vec3 &position, const float &rotation, const glm::vec2 &size, const glm::vec4 &color) : 
            position(position), rotation(rotation), size(size), color(color) {}
        QuadRendererData(const glm::vec2 &position, const float &rotation, const glm::vec2 &size, const glm::vec4 &color) : 
            position(glm::vec3{position.x, position.y, 0.0f}), rotation(rotation), size(size), color(color) {}
        QuadRendererData(const glm::vec3 &position, const float &rotation, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, const float &tilingFactor) : 
            position(position), rotation(rotation), size(size), texture(texture), tilingFactor(tilingFactor) {}
        QuadRendererData(const glm::vec2 &position, const float &rotation, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, const float &tilingFactor) : 
            position(glm::vec3{position.x, position.y, 0.0f}), rotation(rotation), size(size), texture(texture), tilingFactor(tilingFactor) {}
        QuadRendererData(const glm::vec3 &position, const float &rotation, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, const float &tilingFactor, const glm::vec4 &tintColor) : 
            position(position), rotation(rotation), size(size), color(tintColor), texture(texture), tilingFactor(tilingFactor) {}
        QuadRendererData(const glm::vec2 &position, const float &rotation, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, const float &tilingFactor, const glm::vec4 &tintColor) : 
            position(glm::vec3{position.x, position.y, 0.0f}), rotation(rotation), size(size), color(tintColor), texture(texture), tilingFactor(tilingFactor) {}
    };

    class Renderer2D {
        public:
            static void init();
            static void shutdown();
            static void beginScene(const OrthographicCamera &camera);
            static void endScene();
            static void flushVertexBuffer();
            //primitives
            static void drawQuad(QuadRendererData data = QuadRendererData(), bool shouldRotate = false);
        private:
            //raw pointer for explicit handling
            static Renderer2DStorage *storage;
            static void beginNewBatch();
            static void addTextureSlot(std::shared_ptr<Texture2D> texture);
            static void addQuadVertexData(const QuadVertexData &data);
    };
}

#endif