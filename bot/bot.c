#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define TIME 0

int AI;
int PLAYER;
int COUNT=0;

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

int concatenate (int i, int j) {
    return i*10+j;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return b > a ? a : b;
}

FEN initFEN(char **argv) {
    FEN fen;
    char * chaine = argv[1]; // chaine fen contenue dans des guillemets
    // fen.board_state = argv[1];
    // int num = atoi(argv[2]);
    // fen.last_move = num % 10;
    // fen.move_player = argv[3][0];

    int i=0;
    int id=0;
    char * tab[3];
    
    // Allocations mémoire pour chaque élément de tab
    for (int k = 0; k < 3; k++) {
        tab[k] = malloc(strlen(chaine) + 1);
        if (tab[k] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            fprintf(stderr, "Erreur d'allocation mémoire.\n");
            exit(1);
        }
    }

    while (chaine[i] != '\0' && id < 3) {
        int j = 0;

        // Allocation mémoire pour copie
        char *copie = malloc(strlen(chaine) + 1);
        if (copie == NULL) {
            // Gestion d'erreur si l'allocation échoue
            fprintf(stderr, "Erreur d'allocation mémoire.\n");
            exit(1);
        }

        while (chaine[i + j] != ' ' && chaine[i + j] != '\0') {
            copie[j] = chaine[i + j];
            j++;
        }

        copie[j] = '\0';  // Assurez-vous de terminer la chaîne copie

        strcpy(tab[id], copie);

        free(copie);  // Libérez la mémoire allouée pour la copie
        i = i + j + 1;
        id++;
    }

        //printf("fen : \"%s\" %s %s\n", tab[0], tab[1], tab[2]);

    if (id==3) {
        fen.board_state = tab[0];
        int num = atoi(tab[1]);
        fen.last_move = num % 10;
        fen.move_player = tab[2][0];
        return fen;
    }
    else { //on n'a pas le bon nombre d'éléments dans le tableau
        printf("il n'y a pas le bon nombre d'éléments fournis\n");
        printf("Usage: %s <board> <last_move> <player> \n", argv[0]);
        return fen;
    }
}


void show_morpion(char *morpion) {
     for (int i=0; i<9; i+=3) {
        printf(" %d%d%d\n", morpion[i], morpion[i+1], morpion[i+2]);
     }
    printf("\n");
}
 
// Fonction pour transformer une chaîne de 81 caractères en 9 chaînes de 9 caractères
char    **board2Dto3D(char *board_state) {
    char **board = malloc(sizeof(char*) * 10);
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

int FENvalide (char *board_state){
    int i = 0;
    int number = 0;
	
    while (board_state[i] != '\0'){
    	//printf("%c\n",board_state[i]);
        if (isdigit(board_state[i])){
        	number += board_state[i] - '0';	
        	i+=1;
        }
    
        else if ((board_state[i])=='o'||board_state[i]=='x') {
	    i += 1;
	    number+=1;
	}
	else if ((board_state[i])=='O'||board_state[i]=='X') {
            i += 1;
            number+=9;
        }
	else 
	    return 1;
    }
    //return i != 81; //on veut que la fonction retourne 0 quand tout va bien
     if (number!=81) {
    	return number;
    } else {
        return 0;
    } 
} 

// Fonction pour transformer une FEN en chaine de 81 caractères
char    *parseBoardState(char *board_state) {
   if (FENvalide(board_state)){
   	printf("fen invalide\n");
    	exit(1);
    }
    
    char *board = malloc(sizeof(char *) * 82);
    if (board == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }
    
    int j = 0;
    for (int i = 0; board_state[i]; i++) {
        if (isdigit(board_state[i])) {
            int num = board_state[i] - '0';
            for (int k = 0; k < num; k++) {
                board[j] = 0;
                j++;
            }
        }
        else if (board_state[i] == 'o') {
            board[j] = AI;
            j++;
        } else if (board_state[i] == 'x') {
            board[j] = PLAYER;
            j++;
        } else if (board_state[i] == 'O') {
            for (int k = 0; k < 9; k++) {
                board[j] = AI;
                j++;
            }
        } else if (board_state[i] == 'X') {
            for (int k = 0; k < 9; k++) {
                board[j] = PLAYER;
                j++;
            }
        }
    }
    board[j] = '\0';
    return board;
}

// Fonction transformant la FEN en supermorpion
char    **parseBoard(char *board_state) {
    char *board_2d = parseBoardState(board_state);
    char **board = board2Dto3D(board_2d);
    return board;
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

#define DEPTH_MAX 1


int negamax_alphabeta (char** position, int boardToPlayOn, int alpha, int beta, int depth, int maximizingPlayer) {
    int calcEval = evaluateGame(position, boardToPlayOn);

    COUNT++;
    printf("COUNT = %d\t", COUNT);
    printf("depth = %d\n", depth);
    if (depth <= 0 || abs(calcEval) > 5000) {
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
                            maxEval = max(maxEval, negamax_alphabeta(position, i, alpha, beta, depth - 1, 0));
                            position[i][j] = 0;
                        }
                        alpha = max(alpha, maxEval);
                        // printf("alpha: %d\n", alpha);
                    }
                }
                if(beta <= alpha){
                    break;
                }
            // S'il y a un plateau sur lequel jouer, vous ne passez que par ce plateau
            } else {
                for (int j=0; j<9; j++) {
                    if (position[boardToPlayOn][j] == 0) {
                        position[boardToPlayOn][j] = AI;
                        maxEval = max(maxEval, negamax_alphabeta(position, boardToPlayOn, alpha, beta, depth - 1, 0));
                        position[boardToPlayOn][j] = 0;
                    }
                }
                alpha = max(alpha, maxEval);
                // printf("alpha: %d\n", alpha);
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
                            minEval = max(minEval, -negamax_alphabeta(position, i, alpha, beta, depth - 1, 1));
                            position[i][j] = 0;
                        }
                        beta = min(beta, minEval);
                        // printf("beta: %d\n", beta);
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
                        minEval = max(minEval, -negamax_alphabeta(position, boardToPlayOn, alpha, beta, depth - 1, 1));
                        position[boardToPlayOn][j] = 0;
                    }
                }
                beta = min(beta, minEval);
                // printf("beta: %d\n", beta);
                if(beta <= alpha){
                    break;
                }
                }
            }
        return minEval;
    }
}

// Fonction pour calculer le meilleur mouvement en utilisant l'élagage negamax et alpha-bêta
int calculateBestMove(char **argv) {
    FEN fen = initFEN(argv);
    char *board_state = fen.board_state;
    int last_move = fen.last_move;
    char move_player = fen.move_player;

    char **board = parseBoard(board_state);

    int bestScore = -1000000;
    int grid = -1;
    int square = -1;

    //Calculates the remaining amount of empty squares
    int count = 0;
    for(int i=0; i<9; i++){
        if(checkWinCondition(board[i]) == 0){
            count++;
        }
    }


    char morpion[9];
    for (int i=0; i<9; i++) {
        morpion[i] = checkWinCondition(board[i]);
    }

    if (checkWinCondition(morpion) != 0) {
        printf("Invalid position: game already won\n");
        exit(1);
    }

    if (last_move==0) { // cas où le board est vide
        ///////////////////// on peut jouer n'importe où, mais position forte = milieu milieu
        square=5;
        grid=5;
        return concatenate(square, grid);
    }

    else { //le board n'est pas vide
        if (checkFullBoard(board[last_move-1]) == 1 || checkWinCondition(board[last_move-1]) != 0) {
            for (int i = 0; i < 9; i++) {
                if (checkFullBoard(board[i]) != 1 || checkWinCondition(board[i]) == 0) {
                    for (int j = 0; j < 9; j++) {
                        if (board[i][j] == 0) {
                            board[i][j] = AI;
                            printf("BLABLA1\n");
                            int score = negamax_alphabeta(board, i, -100000, 100000, 6, 0);
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
                    printf("BLABLA2\n");
                    int score = negamax_alphabeta(board, i, -100000, 100000, 6, 0);
                    board[last_move-1][i] = 0;
                    if (score > bestScore) {
                        bestScore = score;
                        square = i+1;
                        grid = last_move;
                    }
                }
            }
        }
    }
    return concatenate(grid, square);
}


int main (int argc, char* argv[]) {
    clock_t start_time, end_time;
    double elapsed_time;

    start_time = clock();   

    //printf("%d \n",argc); 
    
    if (argc != 3) {
        printf("Usage: %s \'<board> <last_move> <player>\' <time> \n", argv[0]);
        return 1;
    }

    FEN fen = initFEN(argv);

    //printf("fen : %s %d %c \n ",fen.board_state, fen.last_move, fen.move_player);

    if (fen.move_player == 'x') {
        AI = 1;
        PLAYER = -1;
    } else {
        AI = -1;
        PLAYER = 1;
    }
    
    char **board = parseBoard(fen.board_state);

    int bestMove = calculateBestMove(argv);
    printf("Best move: %d\n", bestMove);

    for (int i = 0; i < 9; i++) {
        free(board[i]);
    }
    
    end_time = clock();
    elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Convertir le temps en dixièmes de seconde
    int elapsed_tenths = (int)(elapsed_time * 10);

    printf("Le temps écoulé est de %.1f secondes ou %d dixièmes de seconde.\n", elapsed_time, elapsed_tenths);


    return 0;
}