//
//  MacOsWindow.cpp
//  EndGame
//
//  Created by Siddharth on 28/05/20.
//

#include "MacOsWindow.hpp"
#include <EndGame/Src/EndGamePCH.hpp>

namespace EndGame {
    static bool isGlfwInitialized = false;

    Window *Window::create(const WindowProperties &properties) {
        return new MacOsWindow(properties);
    }

    MacOsWindow::MacOsWindow(const WindowProperties &properties) {
        init(properties); 
    }

    MacOsWindow::~MacOsWindow() {
        shutdown();
    }

    void MacOsWindow::onUpdate() {
        glfwPollEvents();
		glfwSwapBuffers(window);
    }

    void MacOsWindow::setEventCallBack(const std::function<void(Event&)> &eventFunc) {
        data.eventCallBack = eventFunc;
    }

    void MacOsWindow::setVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        data.isVSync = enabled;
    }

    bool MacOsWindow::isVSync() const {
        return data.isVSync;
    }

    void MacOsWindow::init(const WindowProperties &properties) {
        data.title = properties.title;
        data.height = properties.height;
        data.width = properties.width;
        //logging
        EG_ENGINE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);
        if (!isGlfwInitialized) {
            int success = glfwInit();
            EG_ENGINE_ASSERT(success, "Could not intialize GLFW!");
            isGlfwInitialized = true;
        }
        window = glfwCreateWindow((int)properties.width, (int)properties.height, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
        setVSync(true);
    }

    void MacOsWindow::shutdown() {
        glfwDestroyWindow(window);
    }
}
