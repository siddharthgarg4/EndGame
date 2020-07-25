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
    return areCharacterPositionsOverlapping(currentPosition.first, currentPosition.second, otherPosition.first, otherPosition.second);
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
            characterNewPositionX=board.roundIfNeeded(currentPosition.first);
            break;
        case down:
            characterNewPositionY+=movementPerDtime;
            characterNewPositionX=board.roundIfNeeded(currentPosition.first);
            break;
        case left:
            characterNewPositionX-=movementPerDtime;
            characterNewPositionY=board.roundIfNeeded(currentPosition.second);
            break;
        case right:
            characterNewPositionX+=movementPerDtime;
            characterNewPositionY=board.roundIfNeeded(currentPosition.second);
            break;
        case noDirection:
            break;
    }
    return std::make_pair(characterNewPositionX, characterNewPositionY);
}

//MARK: Player methods
Player::Player(const std::pair<float, float> &defaultPosition, const std::vector<std::shared_ptr<EndGame::Texture2D>> &textures) : Character(defaultPosition, textures) {}

void Player::move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions) {
    //change directions if needed
    if (EndGame::Input::isKeyPressed(EG_KEY_UP)) {
        currentFacingDirection = Direction::up;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_DOWN)) {
        currentFacingDirection = Direction::down;
    }else if (EndGame::Input::isKeyPressed(EG_KEY_LEFT)) {
        currentFacingDirection = Direction::left;
    } else if (EndGame::Input::isKeyPressed(EG_KEY_RIGHT)) {
        currentFacingDirection = Direction::right;
    }
    //get next frame position
    currentPosition = nextFramePosition(board, dtime);
    board.updateBoardForPlayerMove(currentPosition.first, currentPosition.second);
}

void Player::render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime, const CharacterPositions &positions){
    std::pair<float, float> nextFramePlayerCoord = nextFramePosition(board, dtime);
    float interpolatedPlayerX = (currentPosition.first * (1-alpha)) + (nextFramePlayerCoord.first * alpha);
    float interpolatedPlayerY = (currentPosition.second * (1-alpha)) + (nextFramePlayerCoord.second * alpha);
    float playerX = interpolatedPlayerX * board.renderedCellSize;
    //-1 since it should go from 19 to 0
    float playerY = (board.rowCellSize - interpolatedPlayerY - 1) * board.renderedCellSize;
    EG_ASSERT(characterTextures.size()<3, "Too few character textures provided for player!");
    static int renderingCount = 0;
    static const int pacManTextureEatingInterval = 15;  //simulate animation by changing textures every 10 frames
    std::shared_ptr<EndGame::Texture2D> playerTexture;
    if (currentFacingDirection == Direction::noDirection) {
        playerTexture = characterTextures.at(0);
    } else if ((renderingCount/pacManTextureEatingInterval)%2==0) {
        playerTexture = characterTextures.at(1);
    } else {
        playerTexture = characterTextures.at(2);
    }
    //z based on power up or not and who can eat who
    float zIndex = isPowerUpActive ? 0.2f : 0.1f;
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({playerX, playerY, zIndex}, static_cast<std::underlying_type<Direction>::type>(currentFacingDirection), 
        {board.renderedCellSize*1.5, board.renderedCellSize*1.5}, playerTexture, 1.0f), true);
    renderingCount++;
}

void Player::reset() {
    currentPosition = defaultPosition;
    currentFacingDirection = Direction::noDirection;
}

std::pair<float, float> Player::nextFramePosition(PacManBoard &board, const float &dtime) {
    //returns next frame position for player
    const float movementPerDtime = movementSpeed*dtime;
    std::pair<float, float> playerNextFramePosition = characterNewPosition(currentPosition.first, currentPosition.second, currentFacingDirection, board, movementPerDtime);
    //if move is valid return the move else return current position (i.e. no move if not valid)
    return board.isMoveValid(playerNextFramePosition.first, playerNextFramePosition.second) ? playerNextFramePosition : currentPosition;
}

//MARK: Monster methods
Monster::Monster(const std::pair<float, float> &defaultPosition, const std::vector<std::shared_ptr<EndGame::Texture2D>> &textures, uint16_t monsterId, MonsterChaseStrategy defaultStrategy) : 
    Character(defaultPosition, textures), monsterId(monsterId), directionLock(false), defaultStrategy(defaultStrategy), targetPosition(std::make_pair(-1.0f, -1.0f)) {
        //starts off with default strategy
        currentStrategy = defaultStrategy;
    }

void Monster::move(PacManBoard &board, bool isPowerUpActive, const float &timeSinceStart, const float &dtime, const CharacterPositions &positions) {
    //also change current chase strategy based on timeSinceStart
    MonsterMove nextMove = nextFramePosition(dtime, board, positions);
    currentFacingDirection = nextMove.newDirection;
    currentPosition = nextMove.newPosition;
    directionLock = nextMove.isDirectionLock;
    targetPosition = nextMove.targetPosition;
}

void Monster::render(PacManBoard &board, bool isPowerUpActive, const float &alpha, const float &dtime, const CharacterPositions &positions) {
    MonsterMove nextMove = nextFramePosition(dtime, board, positions);
    float interpolatedMonsterX = (currentPosition.first * (1-alpha)) + (nextMove.newPosition.first * alpha);
    float interpolatedMonsterY = (currentPosition.second * (1-alpha)) + (nextMove.newPosition.second * alpha);
    //should not interpolate if positions are too far apart [more than 2.0f] (in case of power up death of monster)
    float monsterX = (abs(currentPosition.first-nextMove.newPosition.first)<2.0f ? interpolatedMonsterX : currentPosition.first) * board.renderedCellSize;
    //since it should go from 19 to 0
    float monsterY = (board.rowCellSize - (abs(currentPosition.second-nextMove.newPosition.second)<2.0f ? interpolatedMonsterY : currentPosition.second) - 1) * board.renderedCellSize;
    EG_ASSERT(characterTextures.size()<4, "Too few character textures provided for monster!");
    std::shared_ptr<EndGame::Texture2D> monsterTexture;
    switch(currentFacingDirection) {
        case Direction::right:
            monsterTexture = characterTextures.at(0);
            break;
        case Direction::up: 
            monsterTexture = characterTextures.at(1);
            break;
        case Direction::left:
            monsterTexture = characterTextures.at(2);
            break;
        case Direction::noDirection: case Direction::down: default:
            monsterTexture = characterTextures.at(3);
            break;
    }
    float zIndex = isPowerUpActive ? 0.1f : 0.2f;
    //to render different monsters on different planes in case of overlap
    zIndex += monsterId * 0.01f;
    EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({monsterX, monsterY, zIndex}, 0.0f, 
        {board.renderedCellSize*1.5, board.renderedCellSize*1.5}, monsterTexture, 1.0f));
}

void Monster::reset() {
    currentPosition = defaultPosition;
    currentFacingDirection = Direction::noDirection;
    currentStrategy = defaultStrategy;
    directionLock = false;
    targetPosition = std::make_pair(-1.0f, -1.0f);
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
    Direction oppositeDirectionToFacing = oppositeDirection(currentFacingDirection);
    for (auto &direction : directions) {
        if (oppositeDirectionToFacing != direction) {
            std::pair<float, float> monsterMoveNewPosition = characterNewPosition(currentPosition.first, currentPosition.second, direction, board, movementPerDtime);
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
                    if (currentFacingDirection == move.newDirection) {
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
    std::pair<float, float> oppositeDirectionMove = characterNewPosition(currentPosition.first, currentPosition.second, oppositeDirectionToFacing, board, movementPerDtime);
    //if opposite direction move is valid return it else return current position and direction
    return isMonsterMoveValid(oppositeDirectionMove, board, positions) ? MonsterMove(oppositeDirectionMove, oppositeDirectionToFacing, true, targetPositionForDirection(oppositeDirectionToFacing)) 
        : MonsterMove(currentPosition, currentFacingDirection, directionLock, targetPosition);
}

bool Monster::shouldTurnOffDirectionLockForMove(const std::pair<float, float> &newPosition) {
    int xBaseHundred = ((int)trunc(newPosition.first*100.0f))%100;
    int yBaseHundred = ((int)trunc(newPosition.second*100.0f))%100;
    int xRounded = round(currentPosition.first);
    int yRounded = round(currentPosition.second);
    int targetxRounded = round(targetPosition.first);
    int targetyRounded = round(targetPosition.second);
    if ((xBaseHundred >= 85 && currentFacingDirection == Direction::right && xRounded == targetxRounded) ||
        (xBaseHundred <= 15 && currentFacingDirection == Direction::left  && xRounded == targetxRounded) ||
        (yBaseHundred >= 85 && currentFacingDirection == Direction::down  && yRounded == targetyRounded) ||
        (yBaseHundred <= 15 && currentFacingDirection == Direction::up    && yRounded == targetyRounded)) {
        //checking if the monster has moved approximately one unit in the direction of lock, if it has then turn lock off
        return true;
    }
    //else keep lock so don't turn off
    return false;
}

std::pair<float, float> Monster::targetPositionForDirection(Direction newDirection) {
    switch(newDirection) {
        case Direction::up:
            return std::make_pair(currentPosition.first, currentPosition.second+1);
        case Direction::down:
            return std::make_pair(currentPosition.first, currentPosition.second-1);
        case Direction::right:
            return std::make_pair(currentPosition.first+1, currentPosition.second);
        case Direction::left:
            return std::make_pair(currentPosition.first-1, currentPosition.second);
        case Direction::noDirection: default:
            EG_WARNING("No direction detected in possible moves!");
            return currentPosition;
    }
}

bool Monster::isMonsterMoveValid(std::pair<float, float> &move, PacManBoard &board, const CharacterPositions &positions) {
    if (board.isMoveValid(move.first, move.second)) {
        //the move is valid by board, need to check overlap with other monsters
        for (auto &monsterPosition: positions.monsterPositions) {
            if (currentPosition != monsterPosition) {
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