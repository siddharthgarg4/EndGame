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
        PacMan();
        ~PacMan() = default;
        void onEvent(EndGame::Event &event);
        void update();
        void render();
        bool isPlayerCaptured();
    private:
        //methods
        void reset();
        //game
        GameState currentGameState;
        PlayerState currentPlayerState;
        //board
        PacManBoard board = PacManBoard();
        //player and monsters
        static const int numMonsters = 4;
        std::unique_ptr<Character> player;
        std::array<std::unique_ptr<Character>, numMonsters> monsters;
};

#endif