//
//  Application.hpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp
#include <EndGame/Src/SubSystems/LayerSubSystem/LayerStack.hpp>
#include <EndGame/Src/SubSystems/WindowSubSystem/Window.h>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>

namespace EndGame {

    class Application {
        public:
            Application();
            virtual ~Application();
            void run();
            //layer functions
            void pushLayer(Layer *layer);
            void pushOverlay(Layer *overlay);
        private:
            std::unique_ptr<Window> window;
            bool isRunning = true;
            LayerStack applicationLayers;
    };
    Application *createApplication();
}

#endif
