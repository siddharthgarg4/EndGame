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
#include <vector>
#include <Sandbox/PacMan/PacManBoard.hpp>

enum Direction : int {
    noDirection = -1,
    right = 0, 
    up = 90, 
    left = 180, 
    down = 270,
};

struct CharacterPositions {
    std::pair<float, float> playerPosition;
    std::vector<std::pair<float, float>> monsterPositions;
    //constructors
    CharacterPositions() : playerPosition({0, 0}), monsterPositions() {}
    CharacterPositions(std::pair<float, float> &playerPosition, std::vector<std::pair<float, float>> &monsterPositions) :
        playerPosition(playerPosition), monsterPositions(monsterPositions) {}
};

class Character {
    public:
        Character(const std::pair<float, float> &startingPosition) : position(startingPosition) {}
        virtual ~Character() = default;
        virtual const std::pair<float, float> &getPosition() { return position; }
        virtual void move(PacManBoard &board, bool isPowerUpActive, const CharacterPositions &positions = CharacterPositions()) = 0;
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
        void move(PacManBoard &board, bool isPowerUpActive, const CharacterPositions &positions = CharacterPositions()) override;
        void render(bool isPowerUpActive, uint8_t rowCellSize) override;
        void reset() override {};
};

class Monster : public Character {
    public:
        Monster(const std::pair<float, float> &startingPosition, uint16_t monsterId);
        ~Monster() = default;
        //first two will move randomly, second two will chase
        void move(PacManBoard &board, bool isPowerUpActive, const CharacterPositions &positions = CharacterPositions()) override;
        void render(bool isPowerUpActive, uint8_t rowCellSize) override;
        void reset() override {};
    private:
        uint16_t monsterId;
};

#endif
