#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* board_state;
    int last_move;
    char move_player;
} FEN;

char* itoa(int num) {
    char* str = malloc(sizeof(char) * 3);
    sprintf(str, "%d", num);
    return str;
}

FEN initFEN(char **argv) {
    FEN fen;
    
    fen.board_state = argv[1];
    fen.last_move = atoi(argv[2]);
    fen.move_player = argv[3][0];

    return fen;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return b > a ? a : b;
}

int minimax(char *board, int depth, int isMaximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return 0;
    }
    if (isMaximizingPlayer) {
        int bestScore = -1000000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '.') {
                board[i] = 'x';
                int score = minimax(board, depth - 1, 0, alpha, beta);
                board[i] = '.';
                bestScore = max(score, bestScore);
                alpha = max(alpha, score);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 1000000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '.') {
                board[i] = 'o';
                int score = minimax(board, depth - 1, 1, alpha, beta);
                board[i] = '.';
                bestScore = min(score, bestScore);
                beta = min(beta, score);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return bestScore;
    }
}

char    **board2Dto3D(char *board_state) {
    char **board = malloc(sizeof(char *) * 10);
    int j = 0;
    int i = 0;
    for (; j < 9; j++) {
        board[j] = malloc(sizeof(char) * 10);
        for (int k = 0; k < 9; k++) {
            board[j][k] = board_state[i];
            i++;
        }
        board[j][9] = '\0';
    }
    board[j] = NULL;
    return board;
}

char    *parseBoardState(char *board_state) {
    char *board = malloc(sizeof(char *) * 82);
    int j = 0;
    for (int i = 0; board_state[i]; i++) {
        if (isdigit(board_state[i])) {
            int num = board_state[i] - '0';
            for (int k = 0; k < num; k++) {
                board[j] = '.';
                j++;
            }
        }
        else if (board_state[i] == 'x' || board_state[i] == 'o') {
            board[j] = board_state[i];
            j++;
        }
        else if (board_state[i] == 'X' || board_state[i] == 'O') {
            for (int k = 0; k < 9; k++) {
                board[j] = board_state[i];
                j++;
            }
        }
    }
    board[j] = '\0';
    return board;
}

char    **parseBoard(char *board_state) {
    char *board_2d = parseBoardState(board_state);
    char **board = board2Dto3D(board_2d);
    return board;
}

int minimax (char** position, int boardToPlayOn, int alpha, int beta, maximizingPlayer) {
    int calcEval = evaluateGame(position, boardToPlayOn);
    if (depth <= 0 ||abs(calcEval) < 5000) {
        return calcEval;
    }

    // If the board to play on is -1, it means you can play on any board
    if (boardToPlayOn != -1  && checkWinCondition(position[boardToPlayOn]) != 0) {
        boardToPlayOn = -1;
    }

    // If a board is full(doesn't include 0), it also sets the board to -1
    if (boardToPlayOn != -1 && checkFullBoard(position[boardToPlayOn])) {
        boardToPlayOn = -1;
    }
    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (int i = 0; i < 9; i++) {
            // If you can play on any board you go through all of them
            if (boardToPlayOn == -1) {
                for (int j = 0; j < 9; j++) {
                    // Except te ones which arer won
                    if (checkWinCondition(position(i)) == 0) {
                        if (position[i][j] == '.') {
                            position[i][j] = AI;
                            maxEval = max(evalut, minimax(position, i, depth - 1, alpha, beta, 0));
                            position[i][j] = '.';
                        }
                        alpha = max(alpha, maxEval);
                    }
                
                }
                if(beta <= alpha){
                    break;
                }
            } else {

            }
        }
        return bestScore;
    }
    else {
        int bestScore = 1000000;
        for (int i = 0; i < 9; i++) {
            if (boardToPlayOn == -1 || boardToPlayOn == i) {
                for (int j = 0; j < 9; j++) {
                    if (position[i][j] == 0) {
                        position[i][j] = 'o';
                        int score = minimax(position, i, depth - 1, alpha, beta, 1);
                        position[i][j] = 0;
                        bestScore = min(score, bestScore);
                        beta = min(beta, score);
                        if (beta <= alpha) {
                            break;
                        }
                    }
                }
            }
        }
        return bestScore;
    }
}
  


// Function to calculate the best move using negamax and alpha-beta pruning
char    *calculateBestMove(char **argv) {
    FEN fen = initFEN(argv);
    char *board_state = fen.board_state;
    int last_move = fen.last_move;
    char move_player = fen.move_player;

    char *board = parseBoardState(board_state);

    int bestScore = -1000000;
    int bestMove = -1;
    for (int i = 0; i < &; i++) {
        if (board[i] == '.') {
            board[i] = 'x';
            int score = minimax(board, 0, -1000000, 1000000);
            board[i] = '.';
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    
    char *bestMoveStr = itoa(bestMove);
    return bestMoveStr;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <board> <last_move> <player>\n", argv[0]);
        return 1;
    }

    char* position = argv[1];
    int timeRemaining = atoi(argv[2]);

    char *bestMove = calculateBestMove(argv);

    printf("%s\n", bestMove);

    return 0;
}
