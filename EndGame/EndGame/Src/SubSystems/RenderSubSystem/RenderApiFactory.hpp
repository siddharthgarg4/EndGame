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

namespace EndGame {

    enum class RenderApi {
        None = 0,
        OpenGl = 1
    };

    class RenderApiFactory {
        public:
            static GraphicsContext *createRenderContext(GLFWwindow *windowHandle);
            inline static RenderApi getRenderingApi() { return rendererApi; }
        private:
            static RenderApi rendererApi;
    };
}

#endif
