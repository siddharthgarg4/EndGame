//
//  Application.hpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/WindowSubSystem/Window.h>
#include <EndGame/Src/SubSystems/LayerSubSystem/LayerStack.hpp>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>
#include <EndGame/Src/SubSystems/DebugSubSystem/DebugOverlay.hpp>

namespace EndGame {

    class Application {
        public:
            Application(bool shouldAddDebugOverlay);
            virtual ~Application();
            void run();
            static inline Application &getApplication() { return *appInstance; }
            inline Window &getWindow() { return *window; }
            //layer functions
            void pushLayer(Layer *layer);
            void pushOverlay(Layer *overlay);
        private:
            std::unique_ptr<Window> window;
            bool isRunning = true;
            bool isMinimized = false;
            bool hasDebugOverlay = false;
            LayerStack applicationLayers;
            static Application *appInstance;
    };
    //to be defined in client application
    Application *createApplication();
}

#endif
