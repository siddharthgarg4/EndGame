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

    struct QuadRendererData {
        //default position is 0 on all axes
        //z represents priority towards the screen with 1.0 being max, 0.0 min, ties are broken with what is drawn first is on top
        glm::vec3 position = glm::vec3(0.0f);
        //default rotation is 0
        float rotation = 0.0f;
        //default size is 100%
        glm::vec2 size = glm::vec2(1.0f);
        //default color is white
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
        //default use whiteTexture
        std::shared_ptr<Texture2D> texture = nullptr;
        //constructors
        QuadRendererData() {}
        QuadRendererData(const glm::vec3 &position, const float &rotation, const glm::vec2 &size, const glm::vec4 &color) : 
            position(position), rotation(rotation), size(size), color(color) {}
        QuadRendererData(const glm::vec2 &position, const float &rotation, const glm::vec2 &size, const glm::vec4 &color) : 
            position(glm::vec3{position.x, position.y, 0.0f}), rotation(rotation), size(size), color(color) {}
        QuadRendererData(const glm::vec3 &position, const float &rotation, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture) : 
            position(position), rotation(rotation), size(size), texture(texture) {}
        QuadRendererData(const glm::vec2 &position, const float &rotation, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture) : 
            position(glm::vec3{position.x, position.y, 0.0f}), rotation(rotation), size(size), texture(texture) {}
        QuadRendererData(const glm::vec3 &position, const float &rotation, const glm::vec2 &size, const glm::vec4 &color, const std::shared_ptr<Texture2D> &texture) : 
            position(position), rotation(rotation), size(size), color(color), texture(texture) {}
        QuadRendererData(const glm::vec2 &position, const float &rotation, const glm::vec2 &size, const glm::vec4 &color, const std::shared_ptr<Texture2D> &texture) : 
            position(glm::vec3{position.x, position.y, 0.0f}), rotation(rotation), size(size), color(color), texture(texture) {}
    };

    struct Renderer2DStorage {
        std::shared_ptr<Shader> quadShader = nullptr;
        std::shared_ptr<VertexArray> quadVertexArray = nullptr;
        std::shared_ptr<Texture2D> whiteTexture = nullptr;
    };

    class Renderer2D {
        public:
            static void init();
            static void shutdown();
            static void beginScene(const OrthographicCamera &camera);
            static void endScene();
            //primitives
            static void drawQuad(QuadRendererData data = QuadRendererData(), bool shouldRotate = false);
        private:
            //raw pointer for explicit handling
            static Renderer2DStorage *storage;
    };
}

#endif