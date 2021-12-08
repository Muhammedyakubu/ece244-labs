//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
    auto row = game_state.get_selectedRow();
    auto col = game_state.get_selectedColumn();
    int val; // represents X or O

    if (game_state.get_turn()) val = 1;
    else val = -1;

    //plays the move if the location is empty
    if (game_state.get_gameBoard(row, col) == 0){
        game_state.set_moveValid(true);
        game_state.set_gameBoard(row, col, val);
        game_state.set_turn(!game_state.get_turn());
    }
    else game_state.set_moveValid(false);

    //checking if game is over

    //for wincodes 1 - 3
    for (int i = 0; i <= boardSize - 1; i++){
        if (!game_state.get_gameOver() && game_state.get_gameBoard(i, 0) == val && game_state.get_gameBoard(i, 1) == val && game_state.get_gameBoard(i, 2) == val){
            game_state.set_winCode(i + 1);
            break;
        }
    }

    //for wincodes 4-6
    for (int j = 0; j <= boardSize - 1; j++) {
        if (!game_state.get_gameOver() && game_state.get_gameBoard(0, j) == val && game_state.get_gameBoard(1, j) == val && game_state.get_gameBoard(2, j) == val) {
            game_state.set_winCode(j + 4);
            break;
        }
    }
    if (!game_state.get_gameOver() && game_state.get_gameBoard(0,0) == val && game_state.get_gameBoard(1,1) == val && game_state.get_gameBoard(2,2) == val)
        game_state.set_winCode(7);

    if (!game_state.get_gameOver() && game_state.get_gameBoard(0,2) == val && game_state.get_gameBoard(1,1) == val && game_state.get_gameBoard(2,0) == val)
        game_state.set_winCode(8);

    if (game_state.get_winCode() != 0)
        game_state.set_gameOver(true);

    //checking for a draw
    bool tie = true;
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            if (!game_state.get_gameOver() && game_state.get_gameBoard(i,j) == 0)
                tie = false;

    if (tie) game_state.set_gameOver(true);

}

