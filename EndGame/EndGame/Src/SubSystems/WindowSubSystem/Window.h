//
//  Window.h
//  EndGame
//
//  Created by Siddharth on 28/05/20.
//

#ifndef Window_h
#define Window_h
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/EventSubSystem/Event.h>
#include <EndGame/Src/Core.h>

namespace EndGame {
    struct WindowProperties {
        std::string title;
        unsigned int width;
        unsigned int height;
        WindowProperties(std::string title="EndGame Engine", unsigned int width=1280, unsigned int height=720) :
            title(title), width(width), height(height) {}
    };

    //desktop based window
    class Window {
        public:
            virtual ~Window() {}
            virtual void onUpdate() = 0;
            virtual unsigned int getWidth() = 0;
            virtual unsigned int getHeight() = 0;
            virtual void *getNativeWindow() const = 0;
            //window attributes
            virtual void setEventCallBack(const std::function<void(Event&)> &eventFunc) = 0;
            virtual void setVSync(bool enabled) = 0;
            virtual bool isVSync() const = 0;
            static Window *create(const WindowProperties &properties = WindowProperties());
    };
}


#endif
