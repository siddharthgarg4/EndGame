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
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/Buffer.h>

namespace EndGame {

    enum class RenderApi {
        None = 0,
        OpenGl = 1
    };

    class RenderApiFactory {
        public:
            static std::unique_ptr<GraphicsContext> createRenderContext(GLFWwindow *windowHandle);
            static std::unique_ptr<Shader> createShader(std::string &vertexSource, std::string &fragmentSource);
            static std::unique_ptr<VertexBuffer> createVertexBuffer(float *vertices, uint32_t size);
            static std::unique_ptr<IndexBuffer> createIndexBuffer(uint32_t *indices, uint32_t count);
            inline static RenderApi getRenderingApi() { return renderingApi; }
        private:
            static RenderApi renderingApi;
    };
}

#endif
