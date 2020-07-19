//
//  PacManBoard.cpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "PacManBoard.hpp"
#include <glm/glm.hpp>
#include <EndGame/EndGame.h>

PacManBoard::PacManBoard() {
    reset();
}

void PacManBoard::reset() {
    //reset board
    board = {
        'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
        'o', 'c', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'o', 'o', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'o',
        'o', 'f', 'o', 'f', 'o', 'o', 'o', 'f', 'o', 'f', 'o', 'f', 'f', 'o', 'o', 'o', 'o', 'f', 'f', 'f',
        'o', 'f', 'f', 'f', 'f', 'f', 'o', 'f', 'o', 'f', 'f', 'f', 'o', 'o', 'o', 'o', 'o', 'f', 'o', 's',
        'o', 'o', 'o', 'f', 'o', 'f', 'o', 'f', 'f', 'f', 'o', 'o', 'f', 'f', 'f', 'f', 'f', 'f', 'o', 'f',
        'o', 'o', 'o', 'f', 'f', 'f', 'f', 'f', 'o', 'f', 'o', 'o', 'f', 'o', 'o', 'o', 'o', 'f', 'o', 'f',
        'o', 'o', 'o', 'f', 'o', 'o', 'f', 'f', 'o', 'f', 'f', 'o', 'f', 'f', 'f', 'o', 'o', 'f', 'f', 'f',
        'o', 'o', 'o', 'f', 'o', 'o', 'f', 'o', 'o', 'o', 'f', 'o', 'o', 'o', 'f', 'o', 'o', 'o', 'f', 'o',
        'o', 'f', 'f', 'f', 'o', 'o', 'f', 'o', 'f', 'f', 'f', 'c', 'f', 'f', 'f', 'f', 'o', 'o', 'f', 'o',
        'o', 'f', 'o', 'f', 'o', 'o', 'f', 'o', 'f', 'o', 'e', 'o', 'o', 'o', 'o', 'f', 'o', 'o', 'f', 'o',
        'o', 'f', 'o', 'f', 'f', 'f', 'f', 'o', 'f', 'e', 'e', 'e', 'o', 'o', 'o', 'f', 'o', 'o', 'f', 'o',
        'o', 'f', 'o', 'f', 'o', 'o', 'f', 'o', 'f', 'o', 'o', 'f', 'f', 'f', 'f', 'f', 'o', 'o', 'f', 'o',
        'o', 'f', 'f', 'f', 'o', 'o', 'f', 'o', 'f', 'o', 'o', 'f', 'o', 'o', 'o', 'f', 'o', 'f', 'f', 'f',
        'o', 'o', 'o', 'f', 'o', 'f', 'f', 'o', 'f', 'f', 'o', 'f', 'o', 'f', 'f', 'f', 'f', 'f', 'o', 'f',
        'o', 'o', 'o', 'f', 'f', 'f', 'o', 'o', 'o', 'f', 'o', 'f', 'o', 'f', 'o', 'o', 'o', 'f', 'o', 'f',
        'o', 'f', 'f', 'f', 'o', 'f', 'f', 'f', 'f', 'f', 'o', 'f', 'o', 'f', 'o', 'o', 'o', 'f', 'f', 'f',
        'o', 'f', 'o', 'f', 'o', 'o', 'f', 'o', 'o', 'f', 'f', 'e', 'f', 'f', 'o', 'o', 'o', 'f', 'o', 'f',
        'o', 'f', 'o', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'o', 'o', 'o', 'f', 'o', 'o', 'f', 'f', 'c', 'f',
        'o', 'f', 'f', 'f', 'o', 'o', 'f', 'o', 'o', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'o', 'o', 'o',
        'o', 'o', 'o', 'o', 'o', 'o', 'f', 'f', 'f', 'f', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'
    };
    //reset player and monster positions
    //resetting number of food left
    numOfFoodLeft = 0;
    for (char currentCellItem: board) {
        if (currentCellItem == 'f' || currentCellItem == 's' || currentCellItem == 'c') {
            numOfFoodLeft++;
        }
    }
}

bool PacManBoard::isValidMove(int x, int y) {
    if (0 <= x && x < rowCellSize && 0 <= y && y < rowCellSize) {
        char currentCellItem = board[(y*rowCellSize)+x];
        switch(currentCellItem) {
            case 'o':
                break;
            case 'f': case 's': case 'c':
                board[(y*rowCellSize)+x] = 'e';
                numOfFoodLeft--;
                return true;
            case 'e':
                return true;
        }
    }
    return false;
}

void PacManBoard::render() {
    //render board
    int x, y = 0;
    glm::vec4 cellColor;
    for (int i=0; i<numBoardCells; i++) {
        x = i%rowCellSize; 
        y = rowCellSize - i/rowCellSize;
        char currentCellState = board[i];
        switch(currentCellState) {
            case 'e':
                //black
                cellColor = {0.0f, 0.0f, 0.0f, 1.0f}; 
                break;
            case 'o':
                //white
                cellColor = {1.0f, 1.0f, 1.0f, 1.0f}; 
                break;
            case 'f':
                //green
                cellColor = {0.2f, 0.8, 0.2f, 1.0f}; 
                break;
            case 'c':
                //red
                cellColor = {0.8f, 0.3f, 0.4, 1.0f}; 
                break;
            case 's':
                //blue
                cellColor = {0.2f, 0.3f, 0.9f, 1.0f}; 
                break;
            defaul:
                cellColor = {1.0f, 0.0f, 1.0f, 1.0f}; 
                break;
        }
        EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x * 2.0f, y * 2.0f}, false, {2.0f, 2.0f}, cellColor));
    }
}

bool PacManBoard::isFoodLeft() {
    return numOfFoodLeft!=0;
}