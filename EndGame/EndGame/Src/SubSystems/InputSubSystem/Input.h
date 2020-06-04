//
//  Input.h
//  EndGame
//
//  Created by Siddharth on 04/06/20.
//

#ifndef Input_h
#define Input_h
#include <EndGame/Src/Core.h>

namespace EndGame {

    class Input {
        public:
            //using EG keyCodes/buttonCodes -> check the accompanying files in folder
            inline static bool isKeyPressed(int keyCode) { return nativeInputInstance->isNativeKeyPressed(keyCode); }
            inline static bool isMouseButtonPressed(int buttonCode) { return nativeInputInstance->isNativeMouseButtonPressed(buttonCode); }
            inline static std::pair<double, double> getMousePosition() { return nativeInputInstance->getNativeMousePosition(); }
            inline static float getMouseXPosition() { return nativeInputInstance->getNativeMousePosition().first; }
            inline static float getMouseYPosition() { return nativeInputInstance->getNativeMousePosition().second; }
        protected:
            virtual bool isNativeKeyPressed(int keyCode) = 0;
            virtual bool isNativeMouseButtonPressed(int buttonCode) = 0;
            virtual std::pair<double, double> getNativeMousePosition() = 0;
        private:
            static Input *nativeInputInstance;
    };
}

#endif
