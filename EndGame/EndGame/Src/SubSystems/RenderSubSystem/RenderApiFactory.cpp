//
//  RenderApiFactory.cpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#include "RenderApiFactory.hpp"
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlBuffer.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlVertexArray.hpp>

namespace EndGame {
    //temporary
    RenderApi RenderApiFactory::renderingApi = RenderApi::OpenGl; 

    std::unique_ptr<GraphicsContext> RenderApiFactory::createRenderContext(GLFWwindow *windowHandle) {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return std::make_unique<OpenGlContext>(windowHandle);
            } 
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    std::shared_ptr<Shader> RenderApiFactory::createShader(std::string &vertexSource, std::string &fragmentSource) {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return std::make_shared<OpenGlShader>(vertexSource, fragmentSource);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    std::shared_ptr<VertexBuffer> RenderApiFactory::createVertexBuffer(float *vertices, uint32_t size) {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return std::make_shared<OpenGlVertexBuffer>(vertices, size);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    std::shared_ptr<IndexBuffer> RenderApiFactory::createIndexBuffer(uint32_t *indices, uint32_t count) {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return std::make_shared<OpenGlIndexBuffer>(indices, count);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    std::shared_ptr<VertexArray> RenderApiFactory::createVertexArray() {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return std::make_shared<OpenGlVertexArray>();
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
