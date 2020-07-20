//
//  Character.hpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp
#include <utility>
#include <Sandbox/PacMan/PacManBoard.hpp>

enum Direction : int {
    noDirection = -1,
    right = 0, 
    up = 90, 
    left = 180, 
    down = 270,
};

class Character {
    public:
        Character(const std::pair<float, float> &startingPosition) : position(startingPosition) {}
        virtual ~Character() = default;
        virtual const std::pair<float, float> &getPosition() { return position; }
        virtual void move(PacManBoard &board, bool isPowerUpActive) = 0;
        virtual void render(bool isPowerUpActive, uint8_t rowCellSize) = 0;
        virtual void reset() = 0;
    protected:
        static constexpr float movementSpeed = 0.025f;
        std::pair<float, float> position;
        Direction currentFacing = Direction::noDirection;
};

class Player : public Character {
    public:
        Player(const std::pair<float, float> &startingPosition);
        ~Player() = default;
        void move(PacManBoard &board, bool isPowerUpActive) override;
        void render(bool isPowerUpActive, uint8_t rowCellSize) override;
        void reset() override {};
};

class Monster : public Character {
    public:
        Monster(const std::pair<float, float> &startingPosition, uint16_t monsterId);
        ~Monster() = default;
        void move(PacManBoard &board, bool isPowerUpActive) override {};
        void render(bool isPowerUpActive, uint8_t rowCellSize) override;
        void reset() override {};
    private:
        static const uint8_t maxNumMonsters = 5;
        uint16_t monsterId;
};

#endif
