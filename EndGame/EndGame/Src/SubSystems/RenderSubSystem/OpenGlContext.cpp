//
//  OpenGlContext.cpp
//  
//
//  Created by Siddharth on 05/06/20.
//

#include "OpenGlContext.hpp"
#include <glad/glad.h>

namespace EndGame {

    OpenGlContext::OpenGlContext(GLFWwindow *windowHandle) : windowHandle(windowHandle) {
        EG_ENGINE_ASSERT(windowHandle, "Window handle cannot be null")
    }

    void OpenGlContext::init() {
        glfwMakeContextCurrent(windowHandle);
        //init glad
        __unused int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EG_ENGINE_ASSERT(gladInitSuccess, "Could not intialize Glad!");
    }

    void OpenGlContext::swapBuffers() {
        glfwSwapBuffers(windowHandle);
    }
}