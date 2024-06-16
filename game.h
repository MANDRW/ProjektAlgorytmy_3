#ifndef PROJEKTALGORYTMY_3_GAME_H
#define PROJEKTALGORYTMY_3_GAME_H
#include <vector>
#include "minmax.h"
#include "element.h"
using namespace std;
class Game {//class with board printing, winning checking and human and computer moves
private:
    int size;//quantity of moves
    int capacity;//capacity of board
    int win;//strike for win
public:
    std::vector<std::vector<Element>> board;
    Game(int size, int win);
    void printBoard(bool s);
    int isWin();
    void humanMove(int x, int y);
    void computerMove(pair<int, int> move);

};
#endif
