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

namespace EndGame {

    enum class RenderApi {
        None = 0,
        OpenGl = 1
    };

    class RenderApiFactory {
        public:
            static GraphicsContext *createRenderContext(GLFWwindow *windowHandle);
            static Shader *createShader(std::string &vertexSource, std::string &fragmentSource);
            inline static RenderApi getRenderingApi() { return renderingApi; }
        private:
            static RenderApi renderingApi;
    };
}

#endif
