#include "game.h"
#include <iostream>
#include "minmax.h"

using namespace std;


Game::Game(int size, int win) : size(size),capacity(0), win(win),board(size,vector<Element>(size,EMPTY)) {}

void Game::printBoard(bool s) {
    char c_s;
    char h_s;
    if(s==0){
        h_s='O';
        c_s='X';
    }
    else{
        h_s='X';
        c_s='O';
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch (board[i][j]) {
                case EMPTY:
                    cout << " ";
                    break;
                case COMPUTER:
                    cout << c_s;
                    break;
                case HUMAN:
                    cout << h_s;
                    break;
            }
            if (j < size - 1) {
                cout << "|";
            }
        }
        cout <<endl;
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                cout << "-";
                if (j < size - 1) {
                    cout << "+";
                }
            }
            cout <<endl;
        }
    }
}

int Game::isWin() {
}



void Game::humanMove(int x, int y) {
    if (board[x][y] == EMPTY) {
        board[x][y] = HUMAN;
        capacity++;
    }
    else {
        cout << "Nieprawidlowy ruch" << endl;
    }
}

void Game::computerMove() {

}

