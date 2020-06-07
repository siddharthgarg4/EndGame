//
//  RenderApiFactory.cpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#include "RenderApiFactory.hpp"
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>

namespace EndGame {
    //temporary
    RenderApi RenderApiFactory::renderingApi = RenderApi::OpenGl; 

    GraphicsContext *RenderApiFactory::createRenderContext(GLFWwindow *windowHandle) {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return new OpenGlContext(windowHandle);
            } 
        }
    }

    Shader *RenderApiFactory::createShader(std::string &vertexSource, std::string &fragmentSource) {
        switch(renderingApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return new OpenGlShader(vertexSource, fragmentSource);
            }
        }
    }
}
