//
//  PacMan.hpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef PacMan_hpp
#define PacMan_hpp
#include <EndGame/EndGame.h>
#include <Sandbox/PacMan/PacManBoard.hpp>
#include <Sandbox/PacMan/Character.hpp>

enum GameState {
    paused, running, ended, startScreen
};

enum PlayerState {
    none, powerUp
};

class PacMan {
    public:
        PacMan(const glm::vec4 &baseColor);
        ~PacMan() = default;
        void onEvent(EndGame::Event &event);
        void update(const float &timeSinceStart, const float &dtime);
        void render(const float &alpha, const float &dtime);
        bool isPlayerCaptured();
    private:
        //methods
        void reset();
        //game
        GameState currentGameState;
        PlayerState currentPlayerState;
        //board
        PacManBoard board;
        //player and monsters
        static const int numMonsters = 4;
        std::unique_ptr<Character> player;
        std::array<std::unique_ptr<Character>, numMonsters> monsters;
        //color
        glm::vec4 baseColor;
};

#endif