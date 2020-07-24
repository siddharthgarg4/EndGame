//
//  PacManBoard.hpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef PacManBoard_hpp
#define PacManBoard_hpp
#include <array>
#include <EndGame/EndGame.h>

struct PacManBoardTextures {
    std::shared_ptr<EndGame::Texture2D> blockTexture = nullptr;
    std::shared_ptr<EndGame::Texture2D> foodTexture = nullptr;
    std::shared_ptr<EndGame::Texture2D> strawberryTexture = nullptr;
    std::shared_ptr<EndGame::Texture2D> cherryTexture = nullptr;
    glm::vec4 emptyColor = glm::vec4(0.0f);
    //constructors
    PacManBoardTextures() {}
    PacManBoardTextures(const std::shared_ptr<EndGame::Texture2D> blockTexture, const std::shared_ptr<EndGame::Texture2D> foodTexture, 
        const std::shared_ptr<EndGame::Texture2D> strawberryTexture, const std::shared_ptr<EndGame::Texture2D> cherryTexture, const glm::vec4 &baseColor) :
        blockTexture(blockTexture), foodTexture(foodTexture), strawberryTexture(strawberryTexture), cherryTexture(cherryTexture), emptyColor(baseColor) {}
};

class PacManBoard {
    public:
        //information about the board
        static const int numBoardCells = 400; //20 * 20
        static const int rowCellSize = 20;
        //since -1.0f to 1.0f
        static constexpr float renderedCellSize = (2.0f/rowCellSize);
        //methods
        PacManBoard(const PacManBoardTextures &textures = PacManBoardTextures());
        ~PacManBoard() = default;
        void reset();
        void render();
        bool isFoodLeft();
        //modifies the board if valid
        bool isMoveValid(float x, float y);
        //this method is only called if move is made and thus has been checked for validity
        void updateBoardForPlayerMove(float x, float y);
        float roundIfNeeded(float i);
        std::array<char, numBoardCells> &getBoard();
    private:
        //number of cells to check for every movement
        const static int cellsToCheck = 4;
        int numOfFoodLeft = 0;
        //e - empty, o - obstacle, f - food, c - cherry, s - strawberry, p - player, m - monster
        std::array<char, numBoardCells> board;
        //textures
        PacManBoardTextures boardTextures;
};

#endif