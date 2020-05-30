//
//  MacOsWindow.hpp
//  EndGame
//
//  Created by Siddharth on 28/05/20.
//

#ifndef MacOsWindow_hpp
#define MacOsWindow_hpp
#include <EndGame/Src/SubSystems/WindowSubSystem/Window.h>
#include <GLFW/glfw3.h>

namespace EndGame {
    class MacOsWindow : public Window {
        public:
            MacOsWindow(const WindowProperties &properties);
            virtual ~MacOsWindow();
            void onUpdate() override;
            inline unsigned int getWidth() override { return data.width; }
            inline unsigned int getHeight() override { return data.height; }
            //window attributes
            virtual void setEventCallBack(const std::function<void(Event&)> &eventFunc) override;
            virtual void setVSync(bool enabled) override;
            virtual bool isVSync() const override;

        private:
            virtual void init(const WindowProperties &properties);
            virtual void shutdown();
            GLFWwindow *window;
            //defining WindowData structure for use specifically within class
            struct WindowData {
                std::string title;
                unsigned int width, height;
                bool isVSync;
                std::function<void(Event&)> eventCallBack;
            };
            WindowData data;
    };
}

#endif
