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
        void onUpdate(const float &timeSinceStart, const float &dtime) override;
        void onRender(const float &alpha, const float &dtime) override;
        void onEvent(EndGame::Event &event) override {}
        void onImguiRender() override;
    private:
        //rendering objects
        EndGame::ShaderLibrary shaderLib;
        std::shared_ptr<EndGame::VertexArray> vertexArray;
        std::shared_ptr<EndGame::VertexArray> flatColorVertexArray;
        EndGame::OrthographicCamera camera;
        //event objects
        float cameraRotation = 0.0f;
        float cameraMoveSpeed = 5.0f;
        float cameraRotationSpeed = 180.0f;
        glm::vec3 cameraPosition = {0.0f, 0.0f, 0.0f};
        glm::vec3 flatColor = {0.2f, 0.3f, 0.8f};
        std::pair<glm::vec3, float> cameraTransformAfterUpdate(const float &dtime);
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
