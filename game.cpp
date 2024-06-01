#include "game.h"
#include <iostream>

using namespace std;


Game::Game(int size, int win) : size(size), win(win),board(size,vector<Element>(size,EMPTY)) {}

void Game::printBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch (board[i][j]) {
                case EMPTY:
                    cout << " ";
                    break;
                case COMPUTER:
                    cout << "O";
                    break;
                case HUMAN:
                    cout << "X";
                    break;
            }
            if (j < size - 1) {
                cout << "|";
            }
        }
        cout <<endl;
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                std::cout << "-";
                if (j < size - 1) {
                    std::cout << "+";
                }
            }
            cout <<endl;
        }
    }
}