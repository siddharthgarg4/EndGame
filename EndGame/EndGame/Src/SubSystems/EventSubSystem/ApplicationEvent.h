//
//  ApplicationEvent.h
//  EndGame
//
//  Created by Siddharth on 27/05/20.
//

#ifndef ApplicationEvent_h
#define ApplicationEvent_h
#include <EndGame/Src/SubSystems/EventSubSystem/Event.h>

namespace EndGame {
    class WindowResizeEvent : public Event {
        public:
            WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}
            inline unsigned int getWidth() { return width; }
            inline unsigned int getHeight() { return height; }
            std::string toString() const override { 
                std::stringstream ss;
                ss << "WindowResizeEvent: (width: " << width << ", height: " << height << ")";
                return ss.str();
            }
            EVENT_CLASS_TYPE(EventType::WindowResize)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
        private:
            unsigned int width, height;
    };

    class WindowMinimizeEvent : public Event {
        public:
            WindowMinimizeEvent(bool isMinimized) : isMinimized(isMinimized) {}
            inline bool isWindowMinimized() { return isMinimized; }
            std::string toString() const override {
                std::stringstream ss;
                ss << "WindowMinimizeEvent: (" << isMinimized << ")";
                return ss.str();
            }
            EVENT_CLASS_TYPE(EventType::WindowMinimize)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
        private:
            bool isMinimized;
    };

    class WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() {}
            EVENT_CLASS_TYPE(EventType::WindowClose)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    class AppTickEvent : public Event {
        public:
            AppTickEvent() {}
            EVENT_CLASS_TYPE(EventType::AppTick)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    class AppUpdateEvent : public Event {
        public:
            AppUpdateEvent() {}
            EVENT_CLASS_TYPE(EventType::AppUpdate)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    class AppRenderEvent : public Event {
        public:
            AppRenderEvent() {}
            EVENT_CLASS_TYPE(EventType::AppRender)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };
}

#endif
