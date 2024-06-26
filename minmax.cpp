#include "minmax.h"
#include <iostream>
#include <vector>
#include "element.h"
#include <algorithm>
#include <limits>

using namespace std;

MinMax::MinMax(int winCondition, int user_d) : win(winCondition), user_d(user_d) {}

bool MinMax::isMovesLeft(vector<vector<Element>>& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == EMPTY) return true;
        }
    }
    return false;
}

int MinMax::evaluate(vector<vector<Element>>& board) {
    int score = 0;
    for (int i = 0; i < board.size(); i++) { // checking rows
        for (int j = 0; j <= board.size() - win; j++) {
            int computerCount = 0;
            int humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i][j + k] == COMPUTER) {
                    computerCount++;
                } else if (board[i][j + k] == HUMAN) {
                    humanCount++;
                }
            }
            if (computerCount == win) return 10;
            if (humanCount == win) return -10;
            if (computerCount == win - 1 && humanCount == 0) score += 5;
            if (humanCount == win - 1 && computerCount == 0) score -= 5;
        }
    }

    for (int i = 0; i <= board.size() - win; i++) {//checking columns
        for (int j = 0; j < board.size(); j++) {
            int computerCount = 0;
            int humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j] == COMPUTER) {
                    computerCount++;
                } else if (board[i + k][j] == HUMAN) {
                    humanCount++;
                }
            }
            if (computerCount == win) return 10;
            if (humanCount == win) return -10;
            if (computerCount == win - 1 && humanCount == 0) score += 5;
            if (humanCount == win - 1 && computerCount == 0) score -= 5;
        }
    }

    for (int i = 0; i <= board.size() - win; i++) {//checking diagonal
        for (int j = 0; j <= board.size() - win; j++) {
            int computerCount = 0;
            int humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j + k] == COMPUTER) {
                    computerCount++;
                } else if (board[i + k][j + k] == HUMAN) {
                    humanCount++;
                }
            }
            if (computerCount == win) return 10;
            if (humanCount == win) return -10;
            if (computerCount == win - 1 && humanCount == 0) score += 5;
            if (humanCount == win - 1 && computerCount == 0) score -= 5;
        }
    }

    for (int i = win - 1; i < board.size(); i++) {//checking second diagonal
        for (int j = 0; j <= board.size() - win; j++) {
            int computerCount = 0;
            int humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i - k][j + k] == COMPUTER) {
                    computerCount++;
                } else if (board[i - k][j + k] == HUMAN) {
                    humanCount++;
                }
            }
            if (computerCount == win) return 10;
            if (humanCount == win) return -10;
            if (computerCount == win - 1 && humanCount == 0) score += 5;
            if (humanCount == win - 1 && computerCount == 0) score -= 5;
        }
    }

    return score;
}


int MinMax::min_max(vector<vector<Element>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);//evaluating weight of the board
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;
    if (depth >= user_d) return score;//depth limit

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, min_max(board, depth + 1, !isMax, alpha, beta));//maximizing
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);
                    if (beta <= alpha) break; // Alpha-beta
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, min_max(board, depth + 1, !isMax, alpha, beta));//minimizing
                    board[i][j] = EMPTY;
                    beta = min(beta, best);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
        }
        return best;
    }
}



pair<int, int> MinMax::findBestMove(vector<vector<Element>>& board) {
    int bestVal = numeric_limits<int>::min();//-2147483648
    pair<int, int> bestMove = {-1, -1};//the worst move
    bool auto_d=false;//without auto-depth
    if(user_d==0) {
        auto_d=true;//with auto-depth
        user_d=100/(100-board.size());//auto-depht function
    }
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = min_max(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    if(auto_d== true)user_d=100/(100-board.size());//auto-depth update
    return bestMove;
}


MinMax::~MinMax() {}
