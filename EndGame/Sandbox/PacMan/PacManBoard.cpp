//
//  PacManBoard.cpp
//  EndGame
//
//  Created by Siddharth on 18/07/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#include "PacManBoard.hpp"
#include <math.h>
#include <glm/glm.hpp>
#include <EndGame/EndGame.h>

PacManBoard::PacManBoard(const PacManBoardTextures &textures) : boardTextures(textures) {
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
        'o', 'o', 'o', 'f', 'o', 'f', 'o', 'f', 'o', 'f', 'o', 'o', 'f', 'o', 'o', 'o', 'o', 'f', 'o', 'f',
        'o', 'o', 'o', 'f', 'f', 'f', 'f', 'f', 'o', 'f', 'f', 'o', 'f', 'f', 'f', 'o', 'o', 'f', 'f', 'f',
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

bool PacManBoard::isMoveValid(float x, float y) {
    if (0.0f <= x && x < (float)rowCellSize && 0.0f <= y && y < (float)rowCellSize) {
        //valid values
        int xfloor = floor(x);
        int xceil = ceil(x);
        int yfloor = floor(y);
        int yceil = ceil(y);
        //cells to check
        std::array<char, cellsToCheck> cellObjects;
        for(int i=0; i<cellsToCheck; i++) {
            //different combinations of x and y
            cellObjects[i] = board[((i<2 ? yfloor : yceil)*rowCellSize+(i%2==0 ? xfloor : xceil))];
        }
        for (auto &cellObject: cellObjects) {
            //checking object in each cell
            switch(cellObject) {
                case 'f': case 's': case 'c': case 'e':
                    break;
                case 'o':
                    return false;
                default:
                    EG_ENGINE_ASSERT(false, "invalid character in pacman board");
                    return false;
            }
        }
        //all cellObjects are valid
        return true;
    }
    //invalid coordinates
    return false;
}

void PacManBoard::updateBoardForPlayerMove(float x, float y) {
    //round to nearest value if close to an int value to ensure it has actually reached that grid square
    float roundedX = roundIfNeeded(x);
    float roundedY = roundIfNeeded(y);
    int roundedXInt = (int) roundedX;
    int roundedYInt = (int) roundedY;
    if (roundedXInt == roundedX && roundedY == roundedYInt) {
        char currentCellObject = board[(roundedYInt * rowCellSize)+roundedXInt];
        switch(currentCellObject) {
            case 'f': case 's': case 'c':
                board[(roundedYInt * rowCellSize)+roundedXInt] = 'e';
                numOfFoodLeft--;
                break;
            case 'e': case 'o':
                break;
        }
    }
}

float PacManBoard::roundIfNeeded(float i) {
    int iBaseHundred = ((int)trunc(i*100.0f))%100;
    if (85 <= iBaseHundred || iBaseHundred <= 15) {
        return round(i);
    }
    return i;
}

void PacManBoard::render() {
    //render board
    int x, y = 0;
    for (int i=0; i<numBoardCells; i++) {
        x = i%rowCellSize;
        //needs to go from 19 to 0
        y = (rowCellSize-1) - i/rowCellSize;
        char currentCellState = board[i];
        switch(currentCellState) {
            case 'o':
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x*renderedCellSize, y*renderedCellSize}, 
                    0.0f, {renderedCellSize, renderedCellSize}, boardTextures.blockTexture, 1.0f));
                break;
            case 'f':
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x*renderedCellSize, y*renderedCellSize}, 
                    0.0f, {renderedCellSize, renderedCellSize}, boardTextures.foodTexture, 1.0f));
                break;
            case 'c':
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x*renderedCellSize, y*renderedCellSize}, 
                    0.0f, {renderedCellSize, renderedCellSize}, boardTextures.cherryTexture, 1.0f));
                break;
            case 's':
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x*renderedCellSize, y*renderedCellSize}, 
                    0.0f, {renderedCellSize, renderedCellSize}, boardTextures.strawberryTexture, 1.0f));
                break;
            case 'e': default:
                EndGame::Renderer2D::drawQuad(EndGame::QuadRendererData({x*renderedCellSize, y*renderedCellSize}, 
                    0.0f, {renderedCellSize, renderedCellSize}, boardTextures.emptyColor));
                break;
        }
    }
}

bool PacManBoard::isFoodLeft() {
    return numOfFoodLeft!=0;
}