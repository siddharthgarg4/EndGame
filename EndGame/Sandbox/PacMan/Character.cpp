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
Player::Player(const std::pair<float, float> &startingPosition) : Character(startingPosition) {}

void Player::move(PacManBoard &board, bool isPowerUpActive, const CharacterPositions &positions) {
    //change directions if needed
    if (EndGame::Input::isKeyPressed(EG_KEY_UP)) {
        currentFacing = Direction::up;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_DOWN)) {
        currentFacing = Direction::down;
    }else if (EndGame::Input::isKeyPressed(EG_KEY_LEFT)) {
        currentFacing = Direction::left;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_RIGHT)) {
        currentFacing = Direction::right;
    }
    float newX = 0.0f;
    float newY = 0.0f;
    switch(currentFacing) {
        case up:
            newY=position.second-movementSpeed;
            newX=board.roundIfNeeded(position.first);
            break;
        case down:
            newY=position.second+movementSpeed;
            newX=board.roundIfNeeded(position.first);
            break;
        case left:
            newX=position.first-movementSpeed;
            newY=board.roundIfNeeded(position.second);
            break;
        case right:
            newX=position.first+movementSpeed;
            newY=board.roundIfNeeded(position.second);
            break;
        case noDirection:
            break;
    }
    if (board.makeMoveIfValid(newX, newY)){
        position = std::make_pair(newX, newY);
    }
}

void Player::render(bool isPowerUpActive, uint8_t rowCellSize, float renderedCellSize){
    glm::vec4 playerColor = {0.705f, 0.4f, 1.0f, 1.0f};
    float playerX = (position.first * renderedCellSize);
    //since it should go from 19 to 0
    float playerY = ((rowCellSize - position.second -1) * renderedCellSize);
    //rotation based on direction facing!!
    //rotation = directionFacing
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({playerX, playerY, 0.6f}, 0, 
        {renderedCellSize*1.5, renderedCellSize*1.5}, playerColor), true);
}

//MARK: Monster methods
Monster::Monster(const std::pair<float, float> &startingPosition, uint16_t monsterId) : Character(startingPosition), monsterId(monsterId) {}

void Monster::render(bool isPowerUpActive, uint8_t rowCellSize, float renderedCellSize) {
    //based on direction facing change rotation
    glm::vec4 monsterColor;
    float monsterX = position.first * renderedCellSize;
    //since it should go from 19 to 0
    float monsterY = (rowCellSize - position.second -1) * renderedCellSize;
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
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({monsterX, monsterY, 0.6f}, false, 
        {renderedCellSize*1.5, renderedCellSize*1.5}, monsterColor));
}

void Monster::move(PacManBoard &board, bool isPowerUpActive, const CharacterPositions &positions) {

}