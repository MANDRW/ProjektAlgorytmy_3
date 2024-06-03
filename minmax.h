#ifndef PROJEKTALGORYTMY_3_MINMAX_H
#define PROJEKTALGORYTMY_3_MINMAX_H
#include <vector>
#include "element.h"

class MinMax {
public:
    int evaluateBoard(std::vector<std::vector<Element>>& board, int size, int win);
    int minimax(std::vector<std::vector<Element>>& board, int depth, bool isMax, int size, int win);
    std::pair<int,int> findBestMove(std::vector<std::vector<Element>>& board, int size, int win);
};
#endif
