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
        EG_ENGINE_INFO("OpenGL Info:");
        EG_ENGINE_INFO("vendor: {0}", glGetString(GL_VENDOR));
        EG_ENGINE_INFO("renderer: {0}", glGetString(GL_RENDERER));
        EG_ENGINE_INFO("version: {0}", glGetString(GL_VERSION));
    }

    void OpenGlContext::swapBuffers() {
        glfwSwapBuffers(windowHandle);
    }
}