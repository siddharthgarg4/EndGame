//
//  RenderApiFactory.cpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#include "RenderApiFactory.hpp"
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlBuffer.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlRendererApi.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlVertexArray.hpp>

namespace EndGame {

    std::unique_ptr<GraphicsContext> RenderApiFactory::createRenderContext(GLFWwindow *windowHandle) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_unique<OpenGlContext>(windowHandle);
            } 
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }

    std::unique_ptr<RendererApi> RenderApiFactory::createRendererApi() {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_unique<OpenGlRendererApi>();
            } 
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }

    std::shared_ptr<Shader> RenderApiFactory::createShader(std::string &name, std::string &vertexSource, std::string &fragmentSource) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_shared<OpenGlShader>(name, vertexSource, fragmentSource);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }

    std::shared_ptr<Shader> RenderApiFactory::createShader(const std::string &filepath) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_shared<OpenGlShader>(filepath);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }

    std::shared_ptr<VertexBuffer> RenderApiFactory::createVertexBuffer(float *vertices, uint32_t size) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_shared<OpenGlVertexBuffer>(vertices, size);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }

    std::shared_ptr<IndexBuffer> RenderApiFactory::createIndexBuffer(uint32_t *indices, uint32_t count) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_shared<OpenGlIndexBuffer>(indices, count);
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }

    std::shared_ptr<VertexArray> RenderApiFactory::createVertexArray() {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return nullptr;
            }
            case RendererApi::Api::OpenGl: {
                return std::make_shared<OpenGlVertexArray>();
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
		return nullptr;
    }
}
