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

PacManLayer::PacManLayer() : Layer("PacMan"), cameraController((800.0f/800.0f)) {}

void PacManLayer::onImguiRender() {}

void PacManLayer::onEvent(EndGame::Event &event) {
    //pause, unpause, reset, end
    cameraController.onEvent(event);
    game.onEvent(event);
}

void PacManLayer::onUpdate(const float &timeSinceStart, const float &dtime) {
    //check if game has ended if it has, 
    cameraController.onUpdate(timeSinceStart, dtime);
    game.update();
}

void PacManLayer::onRender(const float &alpha, const float &dtime) {
    cameraController.onRender(alpha, dtime);
    EndGame::RenderCommand::clear();
    EndGame::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    EndGame::Renderer2D::beginScene(cameraController.getCamera());
    game.render();
    EndGame::Renderer2D::endScene();
}
