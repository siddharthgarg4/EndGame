//
//  RenderApiFactory.cpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#include "RenderApiFactory.hpp"

namespace EndGame {
    //temporary
    RenderApi RenderApiFactory::rendererApi = RenderApi::OpenGl; 

    GraphicsContext *RenderApiFactory::createRenderContext(GLFWwindow *windowHandle) {
        switch(rendererApi) {
            case RenderApi::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::None is currently not supported!");
                return nullptr;
            }
            case RenderApi::OpenGl: {
                return new OpenGlContext(windowHandle);
            } 
        }
    }
}
