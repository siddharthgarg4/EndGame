//
//  RenderApiUtilities.cpp
//  EndGame
//
//  Created by Siddharth on 08/06/20.
//

#include "RenderApiUtilities.hpp"
#include <glad/glad.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

namespace EndGame {

    uint32_t RenderApiUtilities::shaderDataTypeSize(ShaderDataType type) {
        RenderApi renderingApi = RenderApiFactory::getRenderingApi();
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return 0;
            }
            case RenderApi::OpenGl: {
                return OpenGlShader::shaderDataTypeToOpenGlDataType(type).size;
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return 0;
    }

    uint32_t RenderApiUtilities::shaderDataTypeCount(ShaderDataType type) {
        RenderApi renderingApi = RenderApiFactory::getRenderingApi();
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return 0;
            }
            case RenderApi::OpenGl: {
                return OpenGlShader::shaderDataTypeToOpenGlDataType(type).count;
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI!");
        return 0;
    }
}
