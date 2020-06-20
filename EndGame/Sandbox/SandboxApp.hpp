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

class ExampleLayer : public EndGame::Layer {
    public:
        ExampleLayer();
        void onUpdate(float timestep) override;
        void onEvent(EndGame::Event &event) override {}
    private:
        //rendering objects
        std::shared_ptr<EndGame::Shader> shader;
        std::shared_ptr<EndGame::VertexArray> vertexArray;
        std::shared_ptr<EndGame::Shader> blueShader;
        std::shared_ptr<EndGame::VertexArray> blueVertexArray;
        EndGame::OrthographicCamera camera;
        //event objects
        glm::vec3 cameraPosition = {0.0f, 0.0f, 0.0f};
        float cameraRotation = 0.0f;
        float cameraMoveSpeed = 5.0f;
        float cameraRotationSpeed = 180.0f;

};

class Sandbox : public EndGame::Application {
    public:
        Sandbox(bool shouldAddDebugOverlay) : Application(shouldAddDebugOverlay) {
            pushLayer(new ExampleLayer());
        }
        ~Sandbox() {}
};

//custom run the application as per the client
EndGame::Application *EndGame::createApplication() {
    return new Sandbox(true);
}

#endif
