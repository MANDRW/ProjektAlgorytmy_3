#include "minmax.h"
#include <iostream>
#include <vector>
#include "element.h"
#include <algorithm>
#include <limits>

using namespace std;

MinMax::MinMax(int winCondition) : win(winCondition) {}

bool MinMax::isMovesLeft( vector<vector<Element>>& board)  {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

int MinMax::evaluate( vector<vector<Element>>& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j <= board.size() - win; j++) {
            int check = 0;
            for (int k = 0; k < win; k++) {
                if (board[i][j + k] != EMPTY && board[i][j] == board[i][j + k]) {
                    check++;
                }
            }
            if (check == win) {
                return (board[i][j] == HUMAN) ? -10 : 10;
            }
        }
    }
    for (int i = 0; i <= board.size() - win; i++) {
        for (int j = 0; j < board.size(); j++) {
            int check = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j] != EMPTY && board[i][j] == board[i + k][j]) {
                    check++;
                }
            }
            if (check == win) {
                return (board[i][j] == HUMAN) ? -10 : 10;
            }
        }
    }
    for (int i = 0; i <= board.size() - win; i++) {
        for (int j = 0; j <= board.size() - win; j++) {
            int check = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j + k] != EMPTY && board[i][j] == board[i + k][j + k]) {
                    check++;
                }
            }
            if (check == win) {
                return (board[i][j] == HUMAN) ? -10 : 10;
            }
        }
    }
    for (int i = win - 1; i < board.size(); i++) {
        for (int j = 0; j <= board.size() - win; j++) {
            int check = 0;
            for (int k = 0; k < win; k++) {
                if (board[i - k][j + k] != EMPTY && board[i][j] == board[i - k][j + k]) {
                    check++;
                }
            }
            if (check == win) {
                return (board[i][j] == HUMAN) ? -10 : 10;
            }
        }
    }
    return 0;
}

int MinMax::min_max(vector<vector<Element>>& board, int depth, bool isMax) {
    int s = evaluate(board);
    if (s == 10) return s - depth; // Prefer faster wins
    if (s == -10) return s + depth; // Prefer slower losses
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, min_max(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, min_max(board, depth + 1, !isMax));
                    board[i][j] = EMPTY;
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
                int moveVal = min_max(board, 0, false);
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
