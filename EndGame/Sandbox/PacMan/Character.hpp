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
    down = 270
};

struct CharacterPositions {
    std::pair<float, float> playerPosition;
    std::vector<std::pair<float, float>> monsterPositions;
    Direction playerDirection = Direction::noDirection;
    //constructors
    CharacterPositions() : playerPosition({0, 0}), monsterPositions() {}
    CharacterPositions(Direction playerDirection, std::pair<float, float> &playerPosition, std::vector<std::pair<float, float>> &monsterPositions) :
        playerDirection(playerDirection), playerPosition(playerPosition), monsterPositions(monsterPositions) {}
};

class Character {
    public:
        Character(const std::pair<float, float> &startingPosition) : position(startingPosition) {}
        virtual ~Character() = default;
        virtual const std::pair<float, float> &getPosition() { return position; }
        virtual const Direction &getDirection() { return currentFacing; }
        virtual void move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions = CharacterPositions()) = 0;
        virtual void render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime) = 0;
        virtual void reset() = 0;
        bool isOverlappingWith(const std::pair<float, float> &otherPosition);
    protected:
        static constexpr float movementSpeed = 2.5f;
        std::pair<float, float> position;
        Direction currentFacing = Direction::noDirection;
        //utility methods
        bool areCharacterPositionsOverlapping(float x1, float y1, float x2, float y2);
        Direction oppositeDirection(Direction currentFacingDirection);
        std::pair<float, float> characterNewPosition(float x, float y, Direction direction, PacManBoard &board, const float movementPerDtime);
};

class Player : public Character {
    public:
        Player(const std::pair<float, float> &startingPosition);
        ~Player() = default;
        void move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions = CharacterPositions()) override;
        void render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime) override;
        void reset() override {};
    private:
        //returns the valid position else returns current positin
        std::pair<float, float> nextFramePosition(PacManBoard &board, const float &dtime);
};

enum MonsterChaseStrategy {
    randomStrategy, //monster moves randomly
    chaseStrategy, //monster chases current position of player
    trapStrategy, //monster tries to move towards player direction + 4 spaces
    scatterStrategy, //monster moves towards predefined areas
    frightenedStrategy //monster tries to move away from the player
};

struct MonsterMove {
    std::pair<float, float> newPosition;
    Direction newDirection;
    bool isDirectionLock;
    std::pair<float, float> targetPosition;
    //constructors
    MonsterMove(std::pair<float, float> &newPosition, Direction newDirection, bool isDirectionLock = false, std::pair<float, float> targetPosition = std::make_pair(-1.0f, -1.0f)) :
        newPosition(newPosition), newDirection(newDirection), isDirectionLock(isDirectionLock), targetPosition(targetPosition) {}
};

class Monster : public Character {
    public:
        Monster(const std::pair<float, float> &startingPosition, uint16_t monsterId, MonsterChaseStrategy defaultStrategy = MonsterChaseStrategy::randomStrategy);
        ~Monster() = default;
        //first two will move randomly, second two will chase
        void move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions = CharacterPositions()) override;
        void render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime) override;
        void reset() override {};
    private:
        //elements
        uint16_t monsterId;
        bool directionLock;                         //ensure the monster moves atleast one block once decision is made
        MonsterChaseStrategy defaultStrategy;       //default chase strategy
        MonsterChaseStrategy currentStrategy;       //current chase strategy
        // std::pair<float, float> defaultPosition;    //if monster is eaten during power up
        // std::pair<float, float> scatterPosition;    //scatter
        std::pair<float, float> targetPosition;     //trap/chase/random
        //methods
        //returns the best valid move dependant on current chase strategy
        MonsterMove nextFramePosition(const float &dtime, PacManBoard &board, const CharacterPositions &positions);
        //returns direction lock + target position
        bool shouldTurnOffDirectionLockForMove(const std::pair<float, float> &newPosition);
        std::pair<float, float> targetPositionForDirection(Direction newDirection);
        //checks if the monster position is valid in case of board movement as well as in relation to other monster positions
        bool isMonsterMoveValid(std::pair<float, float> &move, PacManBoard &board, const CharacterPositions &positions);
};

#endif
