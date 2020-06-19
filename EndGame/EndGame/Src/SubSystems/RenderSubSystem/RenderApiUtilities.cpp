//
//  RenderApiUtilities.cpp
//  EndGame
//
//  Created by Siddharth on 08/06/20.
//

#include "RenderApiUtilities.hpp"
#include <glad/glad.h>
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>

namespace EndGame {

    uint32_t RenderApiUtilities::shaderDataTypeSize(ShaderDataType type) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return 0;
            }
            case RendererApi::Api::OpenGl: {
                return OpenGlShader::shaderDataTypeToOpenGlDataType(type).size;
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
        return 0;
    }

    uint32_t RenderApiUtilities::shaderDataTypeCount(ShaderDataType type) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return 0;
            }
            case RendererApi::Api::OpenGl: {
                return OpenGlShader::shaderDataTypeToOpenGlDataType(type).count;
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
        return 0;
    }
}
