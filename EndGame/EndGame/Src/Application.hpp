//
//  Application.hpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp
#include <EndGame/Src/SubSystems/WindowSubSystem/Window.h>

namespace EndGame {

    class Application {
        public:
            Application();
            virtual ~Application();
            void run();
        private:
            std::unique_ptr<Window> window;
            bool isRunning = true;
    };
    Application *createApplication();
}

#endif
