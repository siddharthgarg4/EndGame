//
//  PacManLayer.cpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "PacManLayer.hpp"

//defining the PacMan window title
const std::string PacManLayer::pacManWindowTitle = "PacMan Game: Powered by EndGame Engine";
const glm::vec4 PacManLayer::baseColor = {0.0f, 0.0f, 0.0f, 1.0f};

PacManLayer::PacManLayer() : Layer("PacMan") {
    EndGame::OrthoCamControllerData data = EndGame::OrthoCamControllerData();
    //since positive coordinates (have to shift origin by 0.95 <- not 1 since drawing about origin so 0.05 left and right)
    data.cameraPosition = {0.95f, 0.95f, 0};
    data.aspectRatio = 1.0f;
    cameraController = EndGame::OrthographicCameraController(data);
}

void PacManLayer::onImguiRender() {}

void PacManLayer::onEvent(EndGame::Event &event) {
    //pause, unpause, reset, end
    game.onEvent(event);
}

void PacManLayer::onUpdate(const float &timeSinceStart, const float &dtime) {
    //check if game has ended if it has, 
    game.update(timeSinceStart, dtime);
}

void PacManLayer::onRender(const float &alpha, const float &dtime) {
    EndGame::RenderCommand::clear();
    EndGame::RenderCommand::setClearColor(baseColor);
    EndGame::Renderer2D::beginScene(cameraController.getCamera());
    game.render(alpha, dtime);
    EndGame::Renderer2D::endScene();
}
