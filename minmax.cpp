#include "minmax.h"
#include <iostream>
#include <vector>
#include "element.h"
#include <algorithm>
#include <limits>

using namespace std;

MinMax::MinMax(int winCondition,int user_d) : win(winCondition),user_d(user_d) {}

bool MinMax::isMovesLeft(vector<vector<Element>>& board) {
    for (int i= 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++){
            if (board[i][j] == EMPTY) return true;
        }
    }
    return false;
}

int MinMax::evaluate(vector<vector<Element>>& board) {
    // Same evaluation function as provided earlier
    int score = 0;
    // Check rows
    for (int i = 0; i < board.size(); i++) {
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
            if (computerCount == win) {
                return 10;
            } else if (humanCount == win) {
                return -10;
            } else if (computerCount == win - 1 && humanCount == 0) {
                score += 5;
            } else if (humanCount == win - 1 && computerCount == 0) {
                score -= 5;
            }
        }
    }
    for (int i = 0; i <= board.size() - win; i++) {
        for (int j = 0; j < board.size(); j++) {
            int computerCount = 0;
            int humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j] ==COMPUTER) {
                    computerCount++;
                } else if (board[i + k][j] == HUMAN) {
                    humanCount++;
                }
            }
            if (computerCount == win) {
                return 10;
            } else if (humanCount == win) {
                return -10;
            } else if (computerCount == win - 1 && humanCount == 0) {
                score += 5;
            } else if (humanCount == win - 1 && computerCount == 0) {
                score -= 5;
            }
        }
    }
    for (int i = 0; i <= board.size() - win; i++) {
        for (int j = 0; j <= board.size() - win; j++) {
            int computerCount = 0;
            int humanCount = 0;
            for (int k = 0; k < win; k++) {
                if (board[i + k][j + k]==COMPUTER) {
                    computerCount++;
                } else if (board[i + k][j + k] == HUMAN) {
                    humanCount++;
                }
            }
            if (computerCount == win) {
                return 10;
            } else if (humanCount == win) {
                return -10;
            } else if (computerCount == win - 1 && humanCount == 0) {
                score += 5;
            } else if (humanCount == win - 1 && computerCount == 0) {
                score -= 5;
            }
        }
    }
    for (int i = win - 1; i < board.size(); i++) {
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
            if (computerCount == win) {
                return 10;
            } else if (humanCount == win) {
                return -10;
            } else if (computerCount == win - 1 && humanCount == 0) {
                score += 5;
            } else if (humanCount == win - 1 && computerCount == 0) {
                score -= 5;
            }
        }
    }
    return score;
}

int MinMax::min_max(vector<vector<Element>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 10) return score - depth; // Prefer faster wins
    if (score == -10) return score + depth; // Prefer slower losses
    if (!isMovesLeft(board)) return 0;
    if(depth>=user_d) return evaluate(board);
    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = max(best, min_max(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = EMPTY;
                    alpha = max(alpha, best);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            if (beta <= alpha) break; // Alpha-beta pruning
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, min_max(board, depth + 1, !isMax, alpha, beta));
                    board[i][j] = EMPTY;
                    beta = min(beta, best);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            if (beta <= alpha) break; // Alpha-beta pruning
        }
        return best;
    }
}

pair<int, int> MinMax::findBestMove(vector<vector<Element>>& board) {
    int bestVal = -2147483648;
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = min_max(board, 0, false, -2147483648, 2147483647);//-infinity, infinity
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
