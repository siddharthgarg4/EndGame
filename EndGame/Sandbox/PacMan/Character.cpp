//
//  Character.cpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "Character.hpp"
#include <EndGame/EndGame.h>
#include <glm/glm.hpp>

//MARK: Player methods
Player::Player(const std::pair<uint16_t, uint16_t> &startingPosition) : Character(startingPosition) {}

void Player::move(PacManBoard &board, bool isPowerUpActive) {
    if (EndGame::Input::isKeyPressed(EG_KEY_UP)) {
        currentFacing = Direction::up;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_DOWN)) {
        currentFacing = Direction::down;
    }
    if (EndGame::Input::isKeyPressed(EG_KEY_LEFT)) {
        currentFacing = Direction::left;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_RIGHT)) {
        currentFacing = Direction::right;
    }
    int newX = position.first;
    int newY = position.second;
    switch(currentFacing) {
        case up:
            newY--;
            break;
        case down:
            newY++;
            break;
        case left:
            newX--;
            break;
        case right:
            newX++;
            break;
        case noDirection:
            break;
    }
    if (board.isValidMove(newX, newY)){
        position = std::make_pair(newX, newY);
    }
}

void Player::render(bool isPowerUpActive, uint8_t rowCellSize) {
    glm::vec4 playerColor = {0.705f, 0.4f, 1.0f, 1.0f};
    int8_t playerX = position.first * 2.0f;
    int8_t playerY = (rowCellSize - position.second) * 2.0f;
    //rotation based on direction facing!!
    //rotation = directionFacing
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({playerX, playerY, 0.6f}, 0, {2.0f, 2.0f}, playerColor), true);
}

//MARK: Monster methods
Monster::Monster(const std::pair<uint16_t, uint16_t> &startingPosition, uint16_t monsterId) : Character(startingPosition), monsterId(monsterId) {}

void Monster::render(bool isPowerUpActive, uint8_t rowCellSize) {
    //based on direction facing change rotation
    glm::vec4 monsterColor;
    int8_t monsterX = position.first * 2.0f;
    int8_t monsterY = (rowCellSize - position.second) * 2.0f;
    switch(monsterId) {
        case 0:
            monsterColor = {0.078f, 0.662f, 0.960f, 1.0f};
            break;
        case 1:
            monsterColor = {0.96f, 0.5f, 0.078f, 1.0f};
            break;
        case 2:
            monsterColor = {0.96f, 0.91f, 0.078f, 1.0f};
            break;
        case 3:
            monsterColor = {0.2f, 0.078f, 0.96f, 1.0f};
            break;
        case 4:
            monsterColor = {1.0f, 0.0f, 1.0f, 1.0f};
            break;
        default:
            EG_ENGINE_ASSERT(false, "invalid monster id, maximum monsters = 5");
    }
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({monsterX, monsterY, 0.6f}, false, {2.0f, 2.0f}, monsterColor));
}
