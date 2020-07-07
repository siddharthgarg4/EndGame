//
//  MacOsWindow.hpp
//  EndGame
//
//  Created by Siddharth on 28/05/20.
//

#ifndef MacOsWindow_hpp
#define MacOsWindow_hpp
#include <GLFW/glfw3.h>
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/WindowSubSystem/Window.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/GraphicsContext.h>

namespace EndGame {
    
    class MacOsWindow : public Window {
        public:
            MacOsWindow(const WindowProperties &properties);
            virtual ~MacOsWindow();
            void onUpdate() override;
            inline unsigned int getWidth() override { return data.width; }
            inline unsigned int getHeight() override { return data.height; }
            inline void *getNativeWindow() const override { return window; }
            //window attributes
            void setEventCallBack(const std::function<void(Event&)> &eventFunc) override;
            void setVSync(bool enabled) override;
            bool isVSync() const override { return data.isVSync; }
            const bool isMinimized() const override { return data.isMinimized; }

        private:
            virtual void init(const WindowProperties &properties);
            virtual void shutdown();
            GLFWwindow *window;
            //defining WindowData structure for use specifically within class
            struct WindowData {
                std::string title;
                unsigned int width, height;
                bool isMinimized;
                bool isVSync;
                std::function<void(Event&)> eventCallBack;
            };
            std::unique_ptr<GraphicsContext> context;
            WindowData data;
    };
}

#endif
