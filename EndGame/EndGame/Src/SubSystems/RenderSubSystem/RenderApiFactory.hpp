//
//  RenderApiFactory.hpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#ifndef RenderApiFactory_hpp
#define RenderApiFactory_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/GraphicsContext.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlContext.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Buffer.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/VertexArray.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Texture.h>

namespace EndGame {

    class RenderApiFactory {
        public:
            static std::unique_ptr<GraphicsContext> createRenderContext(GLFWwindow *windowHandle);
            static std::unique_ptr<RendererApi> createRendererApi();
            //these objects are passed around and thus should be shared pointers
            static std::shared_ptr<Shader> createShader(const std::string &name, std::string &vertexSource, std::string &fragmentSource);
            static std::shared_ptr<Shader> createShader(const std::string &filepath);
            static std::shared_ptr<VertexBuffer> createVertexBuffer(float *vertices, uint32_t size);
            static std::shared_ptr<IndexBuffer> createIndexBuffer(uint32_t *indices, uint32_t count);
            static std::shared_ptr<VertexArray> createVertexArray();
            static std::shared_ptr<Texture2D> createTexture2D(const std::string &filepath);
    };
}

#endif
