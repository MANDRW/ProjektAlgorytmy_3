#ifndef PROJEKTALGORYTMY_3_GAME_H
#define PROJEKTALGORYTMY_3_GAME_H
#include <vector>
#include "player.h"
#include "human.h"
#include "computer.h"
#include "minmax.h"
#include "element.h"
class Game {
private:
    std::vector<std::vector<Element>> board;
    int size;
    int win;

public:
    Game(int size, int win);
    void printBoard();
    void isWin();
    void move(int x, int y, Player *player);
};
#endif
