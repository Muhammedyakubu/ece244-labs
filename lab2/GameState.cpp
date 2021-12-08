//
//  GameState.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include <iostream>
#include "globals.h"
#include "GameState.h"

using namespace std;

GameState::GameState() {
    selectedRow = 0;
    selectedColumn = 0;
    moveValid = true;
    gameOver = false;
    winCode = 0;
    turn = true;
    //initializing the gameBoard
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            gameBoard[i][j] = 0;
}

//Accessor methods
int GameState::get_selectedRow(){
    return selectedRow;
}

int GameState::get_selectedColumn() {
    return selectedColumn;
}

bool GameState::get_moveValid() {
    return moveValid;
}

bool GameState::get_gameOver() {
    return gameOver;
}

int GameState::get_winCode() {
    return winCode;
}

bool GameState::get_turn() {
    return turn;
}

int GameState::get_gameBoard(int row, int col) {
    if (row <= boardSize-1 && col <= boardSize-1 && row >= 0 && col >= 0) {
        return gameBoard[row][col];
    }else return 0;
}

//Mutator methods
void GameState::set_selectedRow(int value) {
    if (value <= boardSize-1 && value >= 0)
        selectedRow = value;
}

void GameState::set_selectedColumn(int value) {
    if (value <= boardSize-1 && value >= 0)
        selectedColumn = value;
}

void GameState::set_moveValid(bool value) {
    moveValid = value;
}

void GameState::set_gameOver(bool value) {
    gameOver = value;
}

void GameState::set_winCode(int value) {
    if (value >= 0 && value <= 8)
        winCode = value;
    else return;
}

void GameState::set_turn(bool value) {
    turn = value;
}

void GameState::set_gameBoard(int row, int col, int value) {
    if (row <= boardSize-1 && col <= boardSize-1 && row >= 0 && col >= 0 && (value == 1 || value == -1))
        gameBoard[row][col] = value;
}


// ECE244 Student: add you code below


