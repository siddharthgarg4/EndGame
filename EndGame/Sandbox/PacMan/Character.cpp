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

void Player::move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions) {
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
    std::pair<float, float> nextFramePlayerCoord = nextFramePosition(board, dtime);
    if (board.makeMoveIfValid(nextFramePlayerCoord.first, nextFramePlayerCoord.second)){
        position = std::make_pair(nextFramePlayerCoord.first, nextFramePlayerCoord.second);
    }
}

void Player::render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime){
    glm::vec4 playerColor = {0.705f, 0.4f, 1.0f, 1.0f};
    std::pair<float, float> nextFramePlayerCoord = nextFramePosition(board, dtime);
    float interpolatedPlayerX = (position.first * (1-alpha)) + (nextFramePlayerCoord.first * alpha);
    float interpolatedPlayerY = (position.second * (1-alpha)) + (nextFramePlayerCoord.second * alpha);
    //checking validity of interpolated position
    bool isInterpolatedCoordValid = board.isMoveValid(interpolatedPlayerX, interpolatedPlayerY);
    float playerX = (isInterpolatedCoordValid ? interpolatedPlayerX : position.first) * board.renderedCellSize;
    //-1 since it should go from 19 to 0
    float playerY = (board.rowCellSize - (isInterpolatedCoordValid ? interpolatedPlayerY : position.second) - 1) * board.renderedCellSize;
    //rotation based on direction facing!!
    //rotation = directionFacing
    //z based on power up or not and who can eat who
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({playerX, playerY, 0.6f}, 0, {board.renderedCellSize*1.5, board.renderedCellSize*1.5}, playerColor), true);
}

std::pair<float, float>Player::nextFramePosition(PacManBoard &board, const float &dtime) {
    //returns next frame position for player
    float nextFrameX = position.first;
    float nextFrameY = position.second;
    const float movementPerDtime = movementSpeed*dtime;
    switch(currentFacing) {
        case up:
            nextFrameY-=movementPerDtime;
            nextFrameX=board.roundIfNeeded(position.first);
            break;
        case down:
            nextFrameY+=movementPerDtime;
            nextFrameX=board.roundIfNeeded(position.first);
            break;
        case left:
            nextFrameX-=movementPerDtime;
            nextFrameY=board.roundIfNeeded(position.second);
            break;
        case right:
            nextFrameX+=movementPerDtime;
            nextFrameY=board.roundIfNeeded(position.second);
            break;
        case noDirection:
            break;
    }
    return std::make_pair(nextFrameX, nextFrameY);
}

//MARK: Monster methods
Monster::Monster(const std::pair<float, float> &startingPosition, uint16_t monsterId) : Character(startingPosition), monsterId(monsterId) {}

void Monster::render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime) {
    //needs to be updated properly like player
    //based on direction facing change rotation
    glm::vec4 monsterColor;
    float monsterX = position.first * board.renderedCellSize;
    //since it should go from 19 to 0
    float monsterY = (board.rowCellSize - position.second -1) * board.renderedCellSize;
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
        {board.renderedCellSize*1.5, board.renderedCellSize*1.5}, monsterColor));
}

void Monster::move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions) {

}

std::pair<float, float>Monster::nextFramePosition(PacManBoard &board, const float &dtime) {

}