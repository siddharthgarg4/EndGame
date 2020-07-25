//
//  PacMan.cpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "PacMan.hpp"

PacMan::PacMan(const glm::vec4 &baseColor) : baseColor(baseColor) {
    //setting up board textures
    board = PacManBoard(PacManBoardTextures(
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/block.png"),
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/food.png"),
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/food.png"),
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/food.png"),
        baseColor
    ));
    //setting up player
    std::vector<std::shared_ptr<EndGame::Texture2D>> playerTextures = {
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/pacman-no-direction.png"),
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/pacman-one.png"),
        EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/pacman-two.png")
    };
    player = std::make_unique<Player>(std::make_pair(11.0f, 16.0f), playerTextures);
    //setting up monsters
    std::array<float, numMonsters * 2> startingMonsterPositions = {
        10.0f,  9.0f, //0
        9.0f,  10.0f, //1
        10.0f, 10.0f, //2
        11.0f, 10.0f  //3
    };
    static const std::array<std::string, numMonsters> monsterNumbers= {"one", "two", "three", "four"};
    std::vector<std::shared_ptr<EndGame::Texture2D>> monsterTexture;
    monsterTexture.reserve(numMonsters);
    for (int i=0; i<numMonsters; i++) {
        float monsterX = startingMonsterPositions[i*2];
        float monsterY = startingMonsterPositions[(i*2)+1];
        monsterTexture = {
            EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/monster-"+monsterNumbers[i]+"-right.png"),
            EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/monster-"+monsterNumbers[i]+"-up.png"),
            EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/monster-"+monsterNumbers[i]+"-left.png"),
            EndGame::RenderApiFactory::createTexture2D("Sandbox/PacMan/assets/monster-"+monsterNumbers[i]+"-down.png")
        };
        monsters[i] = std::make_unique<Monster>(std::make_pair(monsterX, monsterY), monsterTexture, i);
        monsterTexture.clear();
    }
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
    // reset board
    board.reset();
    player->reset();
    for (auto &monster: monsters) {
        //resetting every monster
        monster->reset();
    }
    currentGameState = GameState::startScreen;
    currentPlayerState = PlayerState::none;
}

void PacMan::update(const float &timeSinceStart, const float &dtime) {
    //check if game has ended, if not then pass command to board to update
    if (!board.isFoodLeft() || isPlayerCaptured()) {
        currentGameState = GameState::ended;
    } else if (currentGameState == GameState::running) {
        bool isPowerUpActive = currentPlayerState==PlayerState::powerUp;
        player->move(board, isPowerUpActive, timeSinceStart, dtime);
        for(auto &monster: monsters) {
            monster->move(board, isPowerUpActive, timeSinceStart, dtime);
        }
    }
}

bool PacMan::isPlayerCaptured() {
    for(auto &monster: monsters) {
        if (player->isOverlappingWith(monster->getCurrentPosition()) && currentPlayerState!=PlayerState::powerUp) {
            return true;
        }
    }
    return false;
}

void PacMan::render(const float &alpha, const float &dtime) {
    //only pass rendering commands if in running state
    //else render the appropriate quads from here with the messages
    switch(currentGameState) {
        case paused:
            break;
        case running:
        {
            bool isPowerUpActive = currentPlayerState==PlayerState::powerUp;
            //board does not move thus does not need dtime and alpha
            board.render();
            //rendering characters
            player->render(board, isPowerUpActive, alpha, dtime);
            for(auto &monster: monsters) {
                monster->render(board, isPowerUpActive, alpha, dtime);
            }
            break;
        }
        case ended:
            break;
        case startScreen:
            break;
    }
}
