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

class PacManBoard {
    public:
        //information about the board
        static const int numBoardCells = 400; //20 * 20
        static const int rowCellSize = 20;
        //methods
        PacManBoard();
        ~PacManBoard() = default;
        void reset();
        void render();
        bool isFoodLeft();
        //modifies the board if valid
        bool isValidMove(float x, float y);
        std::array<char, numBoardCells> &getBoard();
    private:
        //number of cells to check for every movement
        const static int cellsToCheck = 4;
        int numOfFoodLeft = 0;
        //e - empty, o - obstacle, f - food, c - cherry, s - strawberry, p - player, m - monster
        std::array<char, numBoardCells> board;
};

#endif