#ifndef PROJEKTALGORYTMY_3_MINMAX_H
#define PROJEKTALGORYTMY_3_MINMAX_H

#include <vector>
#include "element.h"

class MinMax {
public:
    MinMax(int winCondition); // Constructor with win condition
    std::pair<int, int> findBestMove(std::vector<std::vector<Element>>& board);
    ~MinMax();

private:
    int min_max(std::vector<std::vector<Element>>& board, int depth, bool isMax);
    bool isMovesLeft( std::vector<std::vector<Element>>& board);
    int evaluate(std::vector<std::vector<Element>>& board);

    int win;
};

#endif // PROJEKTALGORYTMY_3_MINMAX_H
