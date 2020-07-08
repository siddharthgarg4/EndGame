//
//  SandboxApp2D.hpp
//  EndGame
//
//  Created by Siddharth on 07/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef SandboxApp2D_hpp
#define SandboxApp2D_hpp
#include <EndGame/EndGame.h>

class Sandbox2D : public EndGame::Layer {
    public:
        Sandbox2D();
        ~Sandbox2D();
        //overriding layer methods
        void onAttach() override;
        void onDetach() override;
        void onImguiRender() override;
        void onEvent(EndGame::Event &event) override;
        void onUpdate(const float &timeSinceStart, const float &dtime) override;
        void onRender(const float &alpha, const float &dtime) override;
    private:
        EndGame::ShaderLibrary shaderLib;
        std::shared_ptr<EndGame::VertexArray> vertexArray;
        EndGame::OrthographicCameraController cameraController;
        glm::vec4 squareColor = {0.8f, 0.2f, 0.3f, 1.0f};
};

#endif