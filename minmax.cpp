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
    int boardSize = board.size();

    // Define weights
    const int win = 10000;
    const int off = 1000;
    const int def = 500;

    // Check rows and columns
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize - win + 1; j++) {
            // Rows
            int computerCount = 0, humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i][j + k] == COMPUTER) computerCount++;
                if (board[i][j + k] == HUMAN) humanCount++;
            }
            if (computerCount == win) return win;
            if (humanCount == win) return -win;
            if (computerCount > 0 && humanCount == 0) score += computerCount * off;
            if (humanCount > 0 && computerCount == 0) score -= humanCount * def;

            // Columns
            computerCount = 0, humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[j + k][i] == COMPUTER) computerCount++;
                if (board[j + k][i] == HUMAN) humanCount++;
            }
            if (computerCount == win) return win;
            if (humanCount == win) return -win;
            if (computerCount > 0 && humanCount == 0) score += computerCount * off;
            if (humanCount > 0 && computerCount == 0) score -= humanCount * def;
        }
    }

    // Check diagonals
    for (int i = 0; i < boardSize - win + 1; i++) {
        for (int j = 0; j < boardSize - win + 1; j++) {
            int computerCount = 0, humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j + k] == COMPUTER) computerCount++;
                if (board[i + k][j + k] == HUMAN) humanCount++;
            }
            if (computerCount == win) return win;
            if (humanCount == win) return -win;
            if (computerCount > 0 && humanCount == 0) score += computerCount * off;
            if (humanCount > 0 && computerCount == 0) score -= humanCount * def;
        }
    }

    for (int i = win - 1; i < boardSize; i++) {
        for (int j = 0; j < boardSize - win + 1; j++) {
            int computerCount = 0, humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i - k][j + k] == COMPUTER) computerCount++;
                if (board[i - k][j + k] == HUMAN) humanCount++;
            }
            if (computerCount == win) return win;
            if (humanCount == win) return -win;
            if (computerCount > 0 && humanCount == 0) score += computerCount * off;
            if (humanCount > 0 && computerCount == 0) score -= humanCount * def;
        }
    }

    return score;
}



int MinMax::min_max(vector<vector<Element>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    // Terminal states
    if (score == 10000) return score - depth; // Prefer faster wins
    if (score == -10000) return score + depth; // Prefer slower losses
    if (!isMovesLeft(board)) return 0; // Draw

    if (depth >= user_d) return score; // Depth limit reached

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, min_max(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best; // Alpha-beta pruning
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
                    best = min(best, min_max(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = EMPTY;
                    beta = min(beta, best);
                    if (beta <= alpha) return best; // Alpha-beta pruning
                }
            }
        }
        return best;
    }
}



pair<int, int> MinMax::findBestMove(vector<vector<Element>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

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

    return bestMove;
}


MinMax::~MinMax() {}
