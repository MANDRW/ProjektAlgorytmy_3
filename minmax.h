#ifndef PROJEKTALGORYTMY_3_MINMAX_H
#define PROJEKTALGORYTMY_3_MINMAX_H
#include <vector>
#include "element.h"

class MinMax {
private:
    int min_max(std::vector<std::vector<Element>>& board, int depth, bool isMax, int alpha, int beta);
    bool isMovesLeft(std::vector<std::vector<Element>>& board);
    int evaluate(std::vector<std::vector<Element>>& board);

    int win;//row for win
    int user_d;//depth
public:
    MinMax(int winCondition,int user_d); // Constructor with win and depth parameters
    std::pair<int, int> findBestMove(std::vector<std::vector<Element>>& board);
    ~MinMax();
};

#endif // PROJEKTALGORYTMY_3_MINMAX_H
