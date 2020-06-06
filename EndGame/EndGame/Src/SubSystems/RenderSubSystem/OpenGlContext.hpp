//
//  OpenGlContext.hpp
//  
//
//  Created by Siddharth on 05/06/20.
//

#ifndef OpenGlContext_hpp
#define OpenGlContext_hpp
#include <GLFW/glfw3.h>
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/GraphicsContext.h>

namespace EndGame {

    class OpenGlContext : public GraphicsContext {
        public:
            OpenGlContext(GLFWwindow *windowHandle);
            void init() override;
            void swapBuffers() override;
        private:
            GLFWwindow *windowHandle;
    };
}

#endif
