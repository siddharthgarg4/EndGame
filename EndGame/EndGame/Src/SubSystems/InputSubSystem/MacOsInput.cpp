//
//  MacOsInput.cpp
//  
//
//  Created by Siddharth on 04/06/20.
//

#include "MacOsInput.hpp"
#include <GLFW/glfw3.h>
#include <EndGame/Src/Application.hpp>

namespace EndGame {

    Input *Input::nativeInputInstance = new MacOsInput();

    bool MacOsInput::isNativeKeyPressed(int keyCode) {
        GLFWwindow *nativeWindow = static_cast<GLFWwindow *>(Application::getApplication().getWindow().getNativeWindow());
        int state = glfwGetKey(nativeWindow, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacOsInput::isNativeMouseButtonPressed(int buttonCode) {
        GLFWwindow *nativeWindow = static_cast<GLFWwindow *>(Application::getApplication().getWindow().getNativeWindow());
        int state = glfwGetMouseButton(nativeWindow, buttonCode);
        return state == GLFW_PRESS;
    }

    std::pair<double, double> MacOsInput::getNativeMousePosition() {
        GLFWwindow *nativeWindow = static_cast<GLFWwindow *>(Application::getApplication().getWindow().getNativeWindow());
        double x,y;
        glfwGetCursorPos(nativeWindow, &x, &y);
        return {x,y};
    }
}
