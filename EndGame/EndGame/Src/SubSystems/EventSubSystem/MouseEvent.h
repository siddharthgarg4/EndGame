//
//  MouseEvent.h
//  EndGame
//
//  Created by Siddharth on 27/05/20.
//

#ifndef MouseEvent_h
#define MouseEvent_h
#include <EndGame/Src/SubSystems/EventSubSystem/Event.h>

namespace EndGame {
    
    class MouseMovedEvent : public Event {
        public:
            MouseMovedEvent(float x, float y) : x(x), y(y) {}
            inline float getX() { return x; }
            inline float getY() { return y; }
            std::string toString() const override { 
                std::stringstream ss;
                ss << "MouseMovedEvent: (x: " << x << ", y: " << y << ")";
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

        private:
            float x, y;
    };

    class MouseScrolledEvent : public Event {
        public:
        MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}
        inline float getXOffset() { return xOffset; }
        inline float getYOffset() { return yOffset; }
        std::string toString() const override { 
            std::stringstream ss;
            ss << "MouseScrolledEvent: (xOffset: " << xOffset << ", yOffset: " << yOffset << ")";
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

        private:
            float xOffset, yOffset;
    };

    class MouseButtonEvent : public Event {
        public:
            inline int getMouseButtonCode() { return buttonCode; }
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput)

        protected:
            MouseButtonEvent(int buttonCode) : buttonCode(buttonCode) {}
            int buttonCode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
        public:
            MouseButtonPressedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}
            std::string toString() const override {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << buttonCode;
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
        MouseButtonReleasedEvent(int buttonCode) : MouseButtonEvent(buttonCode) {}
        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << buttonCode;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}

#endif
