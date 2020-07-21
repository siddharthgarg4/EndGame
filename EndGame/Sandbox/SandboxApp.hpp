//
//  SandboxApp.hpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef SandboxApp_hpp
#define SandboxApp_hpp
#include <glm/glm.hpp>
#include <EndGame/EndGame.h>
//need to include main only once thus user needs to include it
#include <EndGame/Src/EntryPoint.hpp>
#include <Sandbox/Sandbox2D.hpp>
#include <Sandbox/PacMan/PacManLayer.hpp>

class ExampleLayer : public EndGame::Layer {
    public:
        ExampleLayer();
        void onUpdate(const float &timeSinceStart, const float &dtime) override;
        void onRender(const float &alpha, const float &dtime) override;
        void onEvent(EndGame::Event &event) override;
        void onImguiRender() override;
    private:
        //rendering objects
        EndGame::ShaderLibrary shaderLib;
        std::shared_ptr<EndGame::VertexArray> vertexArray;
        std::shared_ptr<EndGame::VertexArray> flatColorVertexArray;
        EndGame::OrthographicCameraController cameraController;
        std::shared_ptr<EndGame::Texture2D> texture;
        std::shared_ptr<EndGame::Texture2D> semiTexture;
        //event objects
        glm::vec3 flatColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public EndGame::Application {
    public:
        Sandbox(bool shouldAddDebugOverlay) : Application(shouldAddDebugOverlay, PacManLayer::pacManWindowTitle, 
            PacManLayer::pacManWindowWidth, PacManLayer::pacManWindowHeight) {
            pushLayer(new PacManLayer());
        }
        ~Sandbox() {}
};

//custom run the application as per the client
EndGame::Application *EndGame::createApplication() {
    return new Sandbox(true);
}

#endif
