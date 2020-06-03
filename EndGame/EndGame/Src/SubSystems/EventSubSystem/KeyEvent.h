//
//  KeyEvent.h
//  EndGame
//
//  Created by Siddharth on 27/05/20.
//

#ifndef KeyEvent_h
#define KeyEvent_h
#include <EndGame/Src/SubSystems/EventSubSystem/Event.h>

namespace EndGame {

    class KeyEvent : public Event {
        public:
            inline int getKeyCode() const { return keyCode; }
            EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)

        protected:
            KeyEvent(int keyCode) : keyCode(keyCode) {}
            int keyCode;
    };

    class KeyPressedEvent : public KeyEvent {
        public:
            KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}
            inline int getRepeatCount() { return repeatCount; }
            std::string toString() const override { 
                std::stringstream ss;
                ss << "KeyPressedEvent: " << keyCode << " (repeats: " << repeatCount << ")";
                return ss.str();
            }
            EVENT_CLASS_TYPE(KeyPressed)
            
        private:
            int repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
        public:
            KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}
            std::string toString() const override { 
                std::stringstream ss;
                ss << "KeyPressedEvent: " << keyCode;
                return ss.str();
            }
            EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
        public:
            KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}
            std::string toString() const override {
                std::stringstream ss;
                ss << "KeyTypedEvent: " << keyCode;
                return ss.str();
            }
            EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif
