#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "entête.h"

int max (int i, int j) {
    if (i>j) return i;
    return j;
}

int min (int i, int j) {
    if (i<j) return i;
    return j;
}


// Vérifier si un morpion ou un supermorpion a été gagné
int check_won (char* morpion) {
    // Vérification des lignes
    for (int i=0; i<SIZE; i+=3) {
        if ( (morpion[i] == morpion[i+1]) && (morpion[i] == morpion[i+2]) && (morpion[i] == 'o')) return PLAYER_O;
        if ( (morpion[i] == morpion[i+1]) && (morpion[i] == morpion[i+2]) && (morpion[i] == 'x')) return PLAYER_X;
        if ( (morpion[i] == morpion[i+1]) && (morpion[i] == morpion[i+2]) && (morpion[i] == 'O')) return PLAYER_O;
        if ( (morpion[i] == morpion[i+1]) && (morpion[i] == morpion[i+2]) && (morpion[i] == 'X')) return PLAYER_X;
    }
    // Vérification des colonnes
    for (int i=0; i<3; i++) {
        if ( (morpion[i] == morpion[i+3]) && (morpion[i] == morpion[i+6]) && (morpion[i] == 'o')) return PLAYER_O;
        if ( (morpion[i] == morpion[i+3]) && (morpion[i] == morpion[i+6]) && (morpion[i] == 'x')) return PLAYER_X;
        if ( (morpion[i] == morpion[i+3]) && (morpion[i] == morpion[i+6]) && (morpion[i] == 'O')) return PLAYER_O;
        if ( (morpion[i] == morpion[i+3]) && (morpion[i] == morpion[i+6]) && (morpion[i] == 'X')) return PLAYER_X;
    }
    // Vérification de la diagonale
    if ( (morpion[0] == morpion[4]) && (morpion[0] == morpion[8]) && (morpion[0] == 'o')) return PLAYER_O;
    if ( (morpion[0] == morpion[4]) && (morpion[0] == morpion[8]) && (morpion[0] == 'x')) return PLAYER_X;
    if ( (morpion[0] == morpion[4]) && (morpion[0] == morpion[8]) && (morpion[0] == 'O')) return PLAYER_O;
    if ( (morpion[0] == morpion[4]) && (morpion[0] == morpion[8]) && (morpion[0] == 'X')) return PLAYER_X;
    // Vérification de l'autre diagonale
    if ( (morpion[2] == morpion[4]) && (morpion[2] == morpion[6]) && (morpion[2] == 'o')) return PLAYER_O;
    if ( (morpion[2] == morpion[4]) && (morpion[2] == morpion[6]) && (morpion[2] == 'x')) return PLAYER_X;
    if ( (morpion[2] == morpion[4]) && (morpion[2] == morpion[6]) && (morpion[2] == 'O')) return PLAYER_O;
    if ( (morpion[2] == morpion[4]) && (morpion[2] == morpion[6]) && (morpion[2] == 'X')) return PLAYER_X;
    return 0;
}

// Vérifier si le morpion est plein
int check_full (char* morpion) {
    for (int i=0; i<SIZE; i++) {
        if (morpion[i] == '.') return 0;
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int concatenate (int i, int j) {
    return i*10+j;
}

// Fonction pour vérifier si un morpion est plein ou non
int checkFullBoard(char *board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            return 0;
        }
    }
    return 1;
}

// Pour savoir si un joueur a gagné
int checkWinCondition(char *morpion) {
    int a = 1;
    if (morpion[0] + morpion[1] + morpion[2] == a * 3 || morpion[3] + morpion[4] + morpion[5] == a * 3 || morpion[6] + morpion[7] + morpion[8] == a * 3 || morpion[0] + morpion[3] + morpion[6] == a * 3 || morpion[1] + morpion[4] + morpion[7] == a * 3 ||
        morpion[2] + morpion[5] + morpion[8] == a * 3 || morpion[0] + morpion[4] + morpion[8] == a * 3 || morpion[2] + morpion[4] + morpion[6] == a * 3) {
        return a;
    }
    a = -1;
    if (morpion[0] + morpion[1] + morpion[2] == a * 3 || morpion[3] + morpion[4] + morpion[5] == a * 3 || morpion[6] + morpion[7] + morpion[8] == a * 3 || morpion[0] + morpion[3] + morpion[6] == a * 3 || morpion[1] + morpion[4] + morpion[7] == a * 3 ||
        morpion[2] + morpion[5] + morpion[8] == a * 3 || morpion[0] + morpion[4] + morpion[8] == a * 3 || morpion[2] + morpion[4] + morpion[6] == a * 3) {
        return a;
    }
    return 0;
}

// Cette fonction évalue un morpion
double realEvaluateSquare(char *pos) {
    double evaluation = 0;
    double points[9] = {0.2, 0.17, 0.2, 0.17, 0.22, 0.17, 0.2, 0.17, 0.2};

    for(int i=0; i<9; i++){
        evaluation -= pos[i]*points[i];
    }

    // Cas si l'adversaire a deux symboles alignés
    int a = 2;
    if(pos[0] + pos[1] + pos[2] == a || pos[3] + pos[4] + pos[5] == a || pos[6] + pos[7] + pos[8] == a) {
        evaluation -= 6;
    }
    if(pos[0] + pos[3] + pos[6] == a || pos[1] + pos[4] + pos[7] == a || pos[2] + pos[5] + pos[8] == a) {
        evaluation -= 6;
    }
    if(pos[0] + pos[4] + pos[8] == a || pos[2] + pos[4] + pos[6] == a) {
        evaluation -= 7;
    }

    //Cas si on s'est fait bloqué un coup
    a = -1;
    if((pos[0] + pos[1] == 2*a && pos[2] == -a) || (pos[1] + pos[2] == 2*a && pos[0] == -a) || (pos[0] + pos[2] == 2*a && pos[1] == -a)
        || (pos[3] + pos[4] == 2*a && pos[5] == -a) || (pos[3] + pos[5] == 2*a && pos[4] == -a) || (pos[5] + pos[4] == 2*a && pos[3] == -a)
        || (pos[6] + pos[7] == 2*a && pos[8] == -a) || (pos[6] + pos[8] == 2*a && pos[7] == -a) || (pos[7] + pos[8] == 2*a && pos[6] == -a)
        || (pos[0] + pos[3] == 2*a && pos[6] == -a) || (pos[0] + pos[6] == 2*a && pos[3] == -a) || (pos[3] + pos[6] == 2*a && pos[0] == -a)
        || (pos[1] + pos[4] == 2*a && pos[7] == -a) || (pos[1] + pos[7] == 2*a && pos[4] == -a) || (pos[4] + pos[7] == 2*a && pos[1] == -a)
        || (pos[2] + pos[5] == 2*a && pos[8] == -a) || (pos[2] + pos[8] == 2*a && pos[5] == -a) || (pos[5] + pos[8] == 2*a && pos[2] == -a)
        || (pos[0] + pos[4] == 2*a && pos[8] == -a) || (pos[0] + pos[8] == 2*a && pos[4] == -a) || (pos[4] + pos[8] == 2*a && pos[0] == -a)
        || (pos[2] + pos[4] == 2*a && pos[6] == -a) || (pos[2] + pos[6] == 2*a && pos[4] == -a) || (pos[4] + pos[6] == 2*a && pos[2] == -a)){
        evaluation-=9;
    }

    // Cas si l'on a deux symboles alignés
    a = -2;
    if(pos[0] + pos[1] + pos[2] == a || pos[3] + pos[4] + pos[5] == a || pos[6] + pos[7] + pos[8] == a) {
        evaluation += 6;
    }
    if(pos[0] + pos[3] + pos[6] == a || pos[1] + pos[4] + pos[7] == a || pos[2] + pos[5] + pos[8] == a) {
        evaluation += 6;
    }
    // Sur une diagonale
    if(pos[0] + pos[4] + pos[8] == a || pos[2] + pos[4] + pos[6] == a) {
        evaluation += 7;
    }

    // Si l'on a bloqué l'adversaire
    a = 1;
    if((pos[0] + pos[1] == 2*a && pos[2] == -a) || (pos[1] + pos[2] == 2*a && pos[0] == -a) || (pos[0] + pos[2] == 2*a && pos[1] == -a)
        || (pos[3] + pos[4] == 2*a && pos[5] == -a) || (pos[3] + pos[5] == 2*a && pos[4] == -a) || (pos[5] + pos[4] == 2*a && pos[3] == -a)
        || (pos[6] + pos[7] == 2*a && pos[8] == -a) || (pos[6] + pos[8] == 2*a && pos[7] == -a) || (pos[7] + pos[8] == 2*a && pos[6] == -a)
        || (pos[0] + pos[3] == 2*a && pos[6] == -a) || (pos[0] + pos[6] == 2*a && pos[3] == -a) || (pos[3] + pos[6] == 2*a && pos[0] == -a)
        || (pos[1] + pos[4] == 2*a && pos[7] == -a) || (pos[1] + pos[7] == 2*a && pos[4] == -a) || (pos[4] + pos[7] == 2*a && pos[1] == -a)
        || (pos[2] + pos[5] == 2*a && pos[8] == -a) || (pos[2] + pos[8] == 2*a && pos[5] == -a) || (pos[5] + pos[8] == 2*a && pos[2] == -a)
        || (pos[0] + pos[4] == 2*a && pos[8] == -a) || (pos[0] + pos[8] == 2*a && pos[4] == -a) || (pos[4] + pos[8] == 2*a && pos[0] == -a)
        || (pos[2] + pos[4] == 2*a && pos[6] == -a) || (pos[2] + pos[6] == 2*a && pos[4] == -a) || (pos[4] + pos[6] == 2*a && pos[2] == -a)){
        evaluation+=9;
    }

    evaluation -= checkWinCondition(pos)*12;
    return evaluation;
}

// La fonction la plus importante, renvoie une évaluation numérique de l'ensemble du jeu dans son état actuel
double evaluateGame(char **position, int currentBoard) {
    double evale = 0;
    char mainBd[9]; //supermorpion convertit en morpion normal avec des 0, des 1 et des -1
    double evaluatorMul[9] = {1.4, 1, 1.4, 1, 1.75, 1, 1.4, 1, 1.4};

    for (int i=0; i<9; i++){
        // Evaluation en fonction de la position des morpions
        evale += realEvaluateSquare(position[i])*1.5*evaluatorMul[i];
        if(i == currentBoard){
            // On évalue également en fonction le morpion actuel 
            evale += realEvaluateSquare(position[i])*evaluatorMul[i];
        }
        int tmpEv = checkWinCondition(position[i]);
        // On prend en compte si un morpion est gagné
        evale -= tmpEv*evaluatorMul[i];
        mainBd[i] = tmpEv;
    }
    // Le supermorpion est gagné
    evale -= checkWinCondition(mainBd) * 5000;
    // On évalue le supermorpion
    evale += realEvaluateSquare(mainBd) * 150;

    return evale;
}



int minimax_alphabeta (char** position, int boardToPlayOn, int alpha, int beta, int depth, int maximizingPlayer) {

    int calcEval = evaluateGame(position, boardToPlayOn);

    if (depth <= 0 || abs(calcEval) < 5000) {
        return calcEval;
    }

    // Si le plateau sur lequel jouer est -1, cela signifie que vous pouvez jouer sur n'importe quel plateau.
    if (boardToPlayOn != -1  && checkWinCondition(position[boardToPlayOn]) != 0) {
        boardToPlayOn = -1;
    }

    // Si un tableau est plein (n'inclut pas 0), cela définit également le tableau sur -1
    if (boardToPlayOn != -1 && checkFullBoard(position[boardToPlayOn])) {
        boardToPlayOn = -1;
    }
    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (int i = 0; i < 9; i++) {
            // Si vous pouvez jouer sur n'importe quel plateau, vous les parcourez tous
            if (boardToPlayOn == -1) {
                for (int j = 0; j < 9; j++) {
                    // Sauf ceux qui sont déjà gagnés
                    if (checkWinCondition(position[i]) == 0) {
                        if (position[i][j] == 0) {
                            position[i][j] = AI;
                            maxEval = max(maxEval, minimax_alphabeta(position, i, depth - 1, alpha, beta, 0));
                            position[i][j] = 0;
                        }
                        alpha = max(alpha, maxEval);
                    }
                }
                if(beta <= alpha){
                    break;
                }
            // S'il y a un plateau sur lequel jouer, vous ne passez que par ce plateau
            } else {
                for (int j=0; i<9; j++) {
                    if (position[boardToPlayOn][j] == 0) {
                        position[boardToPlayOn][j] = AI;
                        maxEval = max(maxEval, minimax_alphabeta(position, boardToPlayOn, depth - 1, alpha, beta, 0));
                        position[boardToPlayOn][j] = 0;
                    }
                }
                alpha = max(alpha, maxEval);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return maxEval;
    } else {
        // La même chose qu'au dessus pour le joueur minimisant
        int minEval = 1000000;  
        for (int i = 0; i < 9; i++) {
            if (boardToPlayOn == -1) {
                for (int j = 0; j < 9; j++) {
                    if (checkWinCondition(position[i]) == 0) {
                        if (position[i][j] == 0) {
                            position[i][j] = PLAYER;
                            minEval = min(minEval, minimax_alphabeta(position, i, depth - 1, alpha, beta, 1));
                            position[i][j] = 0;
                        }
                        beta = min(beta, minEval);
                    }
                }
                if(beta <= alpha){
                    break;
                }
            }
            else {
                for (int j=0; j<9; j++) {
                    if (position[boardToPlayOn][j] == 0) {
                        position[boardToPlayOn][j] = AI;
                        minEval = min(minEval, minimax_alphabeta(position, boardToPlayOn, depth - 1, alpha, beta, 1));
                        position[boardToPlayOn][j] = 0;
                    }
                }
                beta = min(beta, minEval);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return minEval;
    }
}

// Fonction pour calculer le meilleur mouvement en utilisant l'élagage negamax et alpha-bêta
int calculateBestMove(char **board, int horizon, int last_move) {
    int bestScore = -1000000;
    int grid = -1;
    int square = -1;

    if (last_move == 0) {
        grid = 5;
        square = 5;
        return concatenate(grid, square);
    }

    char morpion[9];
    for (int i=0; i<9; i++) {
        morpion[i] = checkWinCondition(board[i]);
    }

    if (checkWinCondition(morpion) != 0) {
        printf("Invalid position: game already won\n");
        exit(1);
    }

    if (checkFullBoard(board[last_move-1]) == 1 || checkWinCondition(board[last_move-1]) != 0) {
        for (int i = 0; i < 9; i++) {
            if (checkFullBoard(board[i]) != 1 || checkWinCondition(board[i]) == 0) {
                for (int j = 0; j < 9; j++) {
                    if (board[i][j] == 0) {
                        board[i][j] = AI;
                        int score = minimax_alphabeta(board, i, -100000, 100000, 5, 0);
                        board[i][j] = 0;
                        if (score > bestScore) {
                            bestScore = score;
                            square = j+1;
                            grid = i+1;
                        }
                    }
                }
            }
        } 
    } else {
        // Iterate through the 9 arrays of the board
        for (int i = 0; i < 9; i++) {
            if (board[last_move-1][i] == 0) {
                board[last_move-1][i] = AI;
                int score = minimax_alphabeta(board, i, -100000, 100000, horizon, 0);
                board[last_move-1][i] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    square = i+1;
                    grid = last_move;
                }
            }
        }
    }
    return concatenate(grid, square);
}
