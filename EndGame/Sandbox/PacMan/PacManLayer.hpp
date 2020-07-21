//
//  PacManLayer.hpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef PacManLayer_hpp
#define PacManLayer_hpp
#include <EndGame/EndGame.h>
#include <Sandbox/PacMan/PacMan.hpp>

class PacManLayer : public EndGame::Layer {
    public:
        //static const variables for window
        static const std::string pacManWindowTitle;
        static const uint32_t pacManWindowHeight = 800;
        static const uint32_t pacManWindowWidth = 800;
        //methods
        PacManLayer();
        ~PacManLayer() = default;
        //overriding layer methods
        void onImguiRender() override;
        void onEvent(EndGame::Event &event) override;
        void onUpdate(const float &timeSinceStart, const float &dtime) override;
        void onRender(const float &alpha, const float &dtime) override;
    private:
        PacMan game = PacMan();
        EndGame::OrthographicCameraController cameraController;
};

#endif
