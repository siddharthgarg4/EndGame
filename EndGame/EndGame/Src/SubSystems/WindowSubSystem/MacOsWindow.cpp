//
//  MacOsWindow.cpp
//  EndGame
//
//  Created by Siddharth on 28/05/20.
//

#include "MacOsWindow.hpp"
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/EventSubSystem/KeyEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/MouseEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

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
        if (data.isMinimized) {
            glfwWaitEvents();
        } else {
            glfwPollEvents();
        }
        context->swapBuffers();
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

    void MacOsWindow::init(const WindowProperties &properties) {
        data.title = properties.title;
        data.height = properties.height;
        data.width = properties.width;
        //logging
        EG_ENGINE_INFO("Creating window: {0} ({1}, {2})", properties.title, properties.width, properties.height);
        if (!isGlfwInitialized) {
            //init once per program run
            __unused int glfwInitSuccess = glfwInit();
            EG_ENGINE_ASSERT(glfwInitSuccess, "Could not intialize GLFW!");
            //setting glfw error callback
            glfwSetErrorCallback([](int error, const char* description) {
                EG_ENGINE_ERROR("GLFW Error ({0}): {1}", error, description);
            });
            isGlfwInitialized = true;
            //OSX specific glfw properties
            #ifdef EG_PLATFORM_OSX
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
                glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
                glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            #endif
        }
        window = glfwCreateWindow((int)properties.width, (int)properties.height, properties.title.c_str(), nullptr, nullptr);
        context = RenderApiFactory::createRenderContext(window);
        context->init();
		glfwSetWindowUserPointer(window, &data);
        setVSync(true);
        //setting initial value of window minimization to false
        data.isMinimized = false;

        //MARK: setting event callbacks to the window
        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            data->width = width;
            data->height = height;
            WindowResizeEvent event(width, height);
            data->eventCallBack(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data->eventCallBack(event);
        });

        glfwSetWindowIconifyCallback(window, [](GLFWwindow *window, int iconified) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            if (iconified) {
                data->isMinimized = true;
            } else {
                data->isMinimized = false;
            }
            WindowMinimizeEvent event(data->isMinimized);
            data->eventCallBack(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            switch(action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key,0);
                    data->eventCallBack(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data->eventCallBack(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key,1);
                    data->eventCallBack(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow *window, unsigned int key) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(key);
            data->eventCallBack(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            switch(action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data->eventCallBack(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data->eventCallBack(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event(xOffset, yOffset);
            data->eventCallBack(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
            WindowData *data = (WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event(x,y);
            data->eventCallBack(event);
        });
    }

    void MacOsWindow::shutdown() {
        glfwDestroyWindow(window);
    }
}
