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
            EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

        private:
            unsigned int width, height;
    };

    class WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() {}
            EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    class AppTickEvent : public Event {
        public:
            AppTickEvent() {}
            EVENT_CLASS_TYPE(AppTick)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    class AppUpdateEvent : public Event {
        public:
            AppUpdateEvent() {}
            EVENT_CLASS_TYPE(AppUpdate)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    class AppRenderEvent : public Event {
        public:
            AppRenderEvent() {}
            EVENT_CLASS_TYPE(AppRender)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };
}

#endif
