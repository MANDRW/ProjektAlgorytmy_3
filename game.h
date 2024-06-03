#ifndef PROJEKTALGORYTMY_3_GAME_H
#define PROJEKTALGORYTMY_3_GAME_H
#include <vector>
#include "minmax.h"
#include "element.h"
class Game {
private:
    std::vector<std::vector<Element>> board;
    int size;
    int capacity;
    int win;

public:
    Game(int size, int win);
    void printBoard(bool s);
    int isWin();
    void humanMove(int x, int y);
    void computerMove();

};
#endif
