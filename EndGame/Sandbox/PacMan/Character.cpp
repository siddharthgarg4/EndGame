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
#include <random>
#include <chrono>

//MARK: Character methods
 bool Character::areCharacterPositionsOverlapping(float x1, float y1, float x2, float y2) {
    //these floats are origin of the texture/square
    static const float halfWidth = 0.5f; //since width = height = 1.0f
    float top1 = x1 + halfWidth;
    float bottom1 = x1 - halfWidth;
    float right1 = y1 + halfWidth;
    float left1 = y1 - halfWidth;
    //other square
    float top2 = x2 + halfWidth;
    float bottom2 = x2 - halfWidth;
    float right2 = y2 + halfWidth;
    float left2 = y2 - halfWidth;
    return ((bottom1 <= top2 && top2 <= top1) || (bottom1 <= bottom2 && bottom2 <= top1)) &&
           ((left1 <= right2 && right2 <= right1) || (left1 <= left2 && left2 <= right1));
}

bool Character::isOverlappingWith(const std::pair<float, float> &otherPosition) {
    return areCharacterPositionsOverlapping(position.first, position.second, otherPosition.first, otherPosition.second);
}

Direction Character::oppositeDirection(Direction currentFacingDirection) {
    switch(currentFacingDirection) {
        case up: return Direction::down;
        case down: return Direction::up;
        case right: return Direction::left;
        case left: return Direction::right;
        case noDirection: default: return Direction::noDirection;
    }
}

std::pair<float, float> Character::characterNewPosition(float x, float y, Direction direction, PacManBoard &board, const float movementPerDtime) {
    float characterNewPositionX = x;
    float characterNewPositionY = y;
    switch(direction) {
        case up:
            characterNewPositionY-=movementPerDtime;
            characterNewPositionX=board.roundIfNeeded(position.first);
            break;
        case down:
            characterNewPositionY+=movementPerDtime;
            characterNewPositionX=board.roundIfNeeded(position.first);
            break;
        case left:
            characterNewPositionX-=movementPerDtime;
            characterNewPositionY=board.roundIfNeeded(position.second);
            break;
        case right:
            characterNewPositionX+=movementPerDtime;
            characterNewPositionY=board.roundIfNeeded(position.second);
            break;
        case noDirection:
            break;
    }
    return std::make_pair(characterNewPositionX, characterNewPositionY);
}

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
    //get next frame position
    position = nextFramePosition(board, dtime);
    board.updateBoardForPlayerMove(position.first, position.second);
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

std::pair<float, float> Player::nextFramePosition(PacManBoard &board, const float &dtime) {
    //returns next frame position for player
    const float movementPerDtime = movementSpeed*dtime;
    std::pair<float, float> playerNextFramePosition = characterNewPosition(position.first, position.second, currentFacing, board, movementPerDtime);
    //if move is valid return the move else return current position (i.e. no move if not valid)
    return board.isMoveValid(playerNextFramePosition.first, playerNextFramePosition.second) ? playerNextFramePosition : position;
}

//MARK: Monster methods
Monster::Monster(const std::pair<float, float> &startingPosition, uint16_t monsterId, MonsterChaseStrategy strategy) : 
    Character(startingPosition), monsterId(monsterId), defaultStrategy(strategy) {
        //starts off with default strategy
        currentStrategy = defaultStrategy;
        targetPosition = std::make_pair(-1.0f, -1.0f);
}

void Monster::move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions) {
    //also change current chase strategy based on timeSinceStart
    MonsterMove nextMove = nextFramePosition(dtime, board, positions);
    currentFacing = nextMove.newDirection;
    position = nextMove.newPosition;
    directionLock = nextMove.isDirectionLock;
    targetPosition = nextMove.targetPosition;
}

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

MonsterMove Monster::nextFramePosition(const float &dtime, PacManBoard &board, const CharacterPositions &positions) {
    //static const variables
    static const int numDirections = 4;
    static const std::array<Direction, numDirections> directions = {Direction::down, Direction::up, Direction::right, Direction::left};
    //const variables
    const float movementPerDtime = movementSpeed*dtime;
    //variables
    std::vector<MonsterMove> possibleMoves;
    //every direction except moving backwards
    possibleMoves.reserve(numDirections-1); 
    Direction oppositeDirectionToFacing = oppositeDirection(currentFacing);
    for (auto &direction : directions) {
        if (oppositeDirectionToFacing != direction) {
            std::pair<float, float> monsterMoveNewPosition = characterNewPosition(position.first, position.second, direction, board, movementPerDtime);
            if (isMonsterMoveValid(monsterMoveNewPosition, board, positions)) {
                //only adds valid moves
                possibleMoves.emplace_back(monsterMoveNewPosition, direction);
            }
        }
    }
    //now based on different strategy differnt moves will be chosen (checks every direction except the opposite direction to currently facing direction)
    switch(currentStrategy) {
        case MonsterChaseStrategy::randomStrategy:
            if (directionLock) {
                //try to move in the same direction else error and return current position
                for (auto &move:possibleMoves) {
                    if (currentFacing == move.newDirection) {
                        //checking lock and target position
                        move.isDirectionLock = !shouldTurnOffDirectionLockForMove(move.newPosition);
                        move.targetPosition = move.isDirectionLock ? targetPosition : std::make_pair(-1.0f, -1.0f);
                        return move;
                    }
                }
            }
            if (possibleMoves.size() != 0) { 
                //shuffling the array for random moves
                std::shuffle(possibleMoves.begin(), possibleMoves.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
                MonsterMove currentMove = possibleMoves.at(0);
                if (possibleMoves.size() > 1 && !directionLock) {
                    //intersection and no direction lock
                    currentMove.isDirectionLock = true;
                    currentMove.targetPosition = targetPositionForDirection(currentMove.newDirection); 
                }
                return currentMove;
            }
            break;
        case MonsterChaseStrategy::chaseStrategy: break;
        case MonsterChaseStrategy::trapStrategy: break;
        case MonsterChaseStrategy::scatterStrategy: break;
        case MonsterChaseStrategy::frightenedStrategy: break;
    }
    //since none of front, left, right worked, need to try opposite direction
    std::pair<float, float> oppositeDirectionMove = characterNewPosition(position.first, position.second, oppositeDirectionToFacing, board, movementPerDtime);
    //if opposite direction move is valid return it else return current position and direction
    return isMonsterMoveValid(oppositeDirectionMove, board, positions) ? MonsterMove(oppositeDirectionMove, oppositeDirectionToFacing, true, targetPositionForDirection(oppositeDirectionToFacing)) 
        : MonsterMove(position, currentFacing, directionLock, targetPosition);
}

bool Monster::shouldTurnOffDirectionLockForMove(const std::pair<float, float> &newPosition) {
    int xBaseHundred = ((int)trunc(newPosition.first*100.0f))%100;
    int yBaseHundred = ((int)trunc(newPosition.second*100.0f))%100;
    int xRounded = round(position.first);
    int yRounded = round(position.second);
    int targetxRounded = round(targetPosition.first);
    int targetyRounded = round(targetPosition.second);
    if ((xBaseHundred >= 85 && currentFacing == Direction::right && xRounded == targetxRounded) ||
        (xBaseHundred <= 15 && currentFacing == Direction::left  && xRounded == targetxRounded) ||
        (yBaseHundred >= 85 && currentFacing == Direction::down  && yRounded == targetyRounded) ||
        (yBaseHundred <= 15 && currentFacing == Direction::up    && yRounded == targetyRounded)) {
        //checking if the monster has moved approximately one unit in the direction of lock, if it has then turn lock off
        return true;
    }
    //else keep lock so don't turn off
    return false;
}

std::pair<float, float> Monster::targetPositionForDirection(Direction newDirection) {
    switch(newDirection) {
        case Direction::up:
            return std::make_pair(position.first, position.second+1);
        case Direction::down:
            return std::make_pair(position.first, position.second-1);
        case Direction::right:
            return std::make_pair(position.first+1, position.second);
        case Direction::left:
            return std::make_pair(position.first-1, position.second);
        case Direction::noDirection: default:
            EG_WARNING("No direction detected in possible moves!");
            return position;
    }
}

bool Monster::isMonsterMoveValid(std::pair<float, float> &move, PacManBoard &board, const CharacterPositions &positions) {
    if (board.isMoveValid(move.first, move.second)) {
        //the move is valid by board, need to check overlap with other monsters
        for (auto &monsterPosition: positions.monsterPositions) {
            if (position != monsterPosition) {
                //ensure the position we are considering is another monster's
                if (areCharacterPositionsOverlapping(move.first, move.second, monsterPosition.first, monsterPosition.second)) {
                    return false;   //move overlapped with another monster position
                }
            }
        }
        return true;    //valid move and doesn't overlap with other monsters
    }
    return false;
}