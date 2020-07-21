//
//  PacMan.cpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "PacMan.hpp"

PacMan::PacMan() {
    reset();
}

void PacMan::onEvent(EndGame::Event &event) {
    EndGame::EventDispatcher dispatcher(event);
    dispatcher.dispatch<EndGame::KeyPressedEvent>([this](EndGame::KeyEvent &event) {
        if (event.getKeyCode() == EG_KEY_P) {
            if (currentGameState == GameState::running) {
                currentGameState = GameState::paused;
            } else if (currentGameState == GameState::paused) {
                currentGameState = GameState::running;
            }
        }

        if (event.getKeyCode() == EG_KEY_SPACE) {
            if (currentGameState == GameState::paused || currentGameState == GameState::ended) {
                reset();
            } else if (currentGameState == GameState::startScreen) {
                currentGameState = GameState::running;
            }
        }
        return true;
    });
}

void PacMan::reset() {
    //reset board
    board.reset();
    //reset player
    player = std::make_unique<Player>(std::make_pair(11.0f, 16.0f));
    //reset monsters
    std::array<float, numMonsters * 2> startingMonsterPositions = {
        10.0f,  9.0f, //0
        9.0f,  10.0f, //1
        10.0f, 10.0f, //2
        11.0f, 10.0f  //3
    };
    for (int i=0; i<numMonsters; i++) {
        float monsterX = startingMonsterPositions[i*2];
        float monsterY = startingMonsterPositions[(i*2)+1];
        monsters[i] = std::make_unique<Monster>(std::make_pair(monsterX, monsterY), i);
    }
    currentGameState = GameState::startScreen;
    currentPlayerState = PlayerState::none;
}

void PacMan::update() {
    //check if game has ended, if not then pass command to board to update
    if (!board.isFoodLeft() || isPlayerCaptured()) {
        currentGameState = GameState::ended;
    } else if (currentGameState == GameState::running) {
        bool isPowerUpActive = currentPlayerState==PlayerState::powerUp;
        player->move(board, isPowerUpActive);
        for(auto &monster: monsters) {
            monster->move(board, isPowerUpActive);
        }
    }
}

bool PacMan::isPlayerCaptured() {
    for(auto &monster: monsters) {
        if (player->getPosition() == monster->getPosition() && currentPlayerState!=PlayerState::powerUp) {
            return true;
        }
    }
    return false;
}

void PacMan::render() {
    //only pass rendering commands if in running state
    //else render the appropriate quads from here with the messages
    switch(currentGameState) {
        case paused:
            break;
        case running:
        {
            bool isPowerUpActive = currentPlayerState==PlayerState::powerUp;
            board.render();
            player->render(isPowerUpActive, board.rowCellSize);
            for(auto &monster: monsters) {
                monster->render(isPowerUpActive, board.rowCellSize);
            }
            break;
        }
        case ended:
            break;
        case startScreen:
            break;
    }
}