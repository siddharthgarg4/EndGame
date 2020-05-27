//
//  Event.h
//  EndGame
//
//  Created by Siddharth on 26/05/20.
//

#ifndef Event_h
#define Event_h
#include <EndGame/Src/Core.h>
#include <EndGame/Src/EndGamePCH.hpp>

namespace EndGame {

    //currently events are blocking

    enum class EventType {
        None = 0,
        WindowClose, WindowFocus, WindowLostFocus, WindowResize, WindowMoved,
        AppTick, AppRender, AppUpdate,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    class Event {
        friend class EventDispatcher;

        public:
            virtual EventType getEventType() const = 0;
            virtual const char *getEventName() const = 0;
            virtual int getCategoryFlags() const = 0;
            //toString can be overriden for more details
            virtual std::string toString() const { return getEventName(); }
            inline bool isEventInCategory(EventCategory category) { return getCategoryFlags() & category; }

        protected:
            bool isHandled = false;
    };
    inline std::ostream &operator<<(std::ostream &out, const Event &event) { return out << event.toString(); }

    class EventDispatcher {
        public:
            EventDispatcher(Event &event) : event(event) {}
            template<typename T>
            bool dispatch(std::function<bool(T&)> func) {
                if (event.getEventType() == T::getEventType()) {
                    event.isHandled = func(*(T*)&event);
                    return true;
                }
                return false;
            }

        private:
            Event &event;
    };

//MARK: Event Macros
#define EVENT_CLASS_TYPE(type)                                                       \
    static EventType getStaticEventType() { return EventType::type; }                \
    virtual EventType getEventType() const override { return getStaticEventType(); } \
    virtual const char *getEventName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int getCategoryFlags() const override { return category; }
}

#endif
