#include "game.h"
#include <iostream>
#include "minmax.h"

using namespace std;


Game::Game(int size, int win) : size(size),capacity(0), win(win),board(size,vector<Element>(size,EMPTY)) {}//constructor

int Game::isWin() {
    for(int i=0;i<size;i++){
        for(int j=0;j<=size-win;j++){
            int check=0;
            for(int k=0;k<win;k++){
                if(board[i][j+k]!=EMPTY && board[i][j]==board[i][j+k]){
                    check++;
                }
            }
            if(check==win){
                return 1;
            }
        }
    }
    for(int i=0;i<=size-win;i++){
        for(int j=0;j<size;j++){
            int check=0;
            for(int k=0;k<win;k++){
                if(board[i+k][j]!=EMPTY && board[i][j]==board[i+k][j]){
                    check++;
                }
            }
            if(check==win){
                return 1;
            }
        }
    }
    for(int i=0;i<=size-win;i++){
        for(int j=0;j<=size-win;j++){
            int check=0;
            for(int k=0;k<win;k++){
                if(board[i+k][j+k]!=EMPTY && board[i][j]==board[i+k][j+k]){
                    check++;
                }
            }
            if(check==win){
                return 1;
            }
        }
    }
    for(int i=win-1;i<size;i++){
        for(int j=0;j<=size-win;j++){
            int check=0;
            for(int k=0;k<win;k++){
                if(board[i-k][j+k]!=EMPTY && board[i][j]==board[i-k][j+k]){
                    check++;
                }
            }
            if(check==win){
                return 1;
            }
        }
    }
    if(capacity==size*size){
        return 2;
    }
    return 0;
}

void Game::printBoard(bool s) {
    char c_s;
    char h_s;
    if(s==0){//setting signs
        h_s='O';
        c_s='X';
    }
    if(s==1){
        h_s='X';
        c_s='O';
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch (board[i][j]) {
                case EMPTY:
                    cout << "   ";
                    break;
                case COMPUTER:
                    cout<<" ";
                    cout << c_s;
                    cout<<" ";
                    break;
                case HUMAN:
                    cout<<" ";
                    cout << h_s;
                    cout<<" ";
                    break;
            }
            if (j < size - 1) {
                cout << " | ";
            }
        }
        cout <<endl;
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                cout << " - ";
                if (j < size - 1) {
                    cout << " + ";
                }
            }
            cout <<endl;
        }
    }
}



void Game::humanMove(int x, int y) {
    if (board[x][y] == EMPTY) {
        board[x][y] = HUMAN;
        capacity++;
    }
}

void Game::computerMove(pair<int,int> move) {
    if (board[move.first][move.second] == EMPTY) {
        board[move.first][move.second] = COMPUTER;
        capacity++;
    }
}


