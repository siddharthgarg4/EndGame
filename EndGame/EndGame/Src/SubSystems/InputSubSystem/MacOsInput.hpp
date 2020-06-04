//
//  MacOsInput.hpp
//  
//
//  Created by Siddharth on 04/06/20.
//

#ifndef MacOsInput_hpp
#define MacOsInput_hpp
#include <EndGame/Src/SubSystems/InputSubSystem/Input.h>

namespace EndGame {

    class MacOsInput : public Input {
        protected:
            bool isNativeKeyPressed(int keyCode) override;
            bool isNativeMouseButtonPressed(int buttonCode) override;
            std::pair<double, double> getNativeMousePosition() override;
    };
}

#endif
