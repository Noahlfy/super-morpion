#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef ENTETE_H
#define ENTETE_H

// Déclarations de fonctions, structures, etc.

#define SIZE 9
#define AI 'o'
#define PLAYER 'x'
#define PLAYER_O -1
#define PLAYER_X 1

int max (int i, int j);
int min (int i, int j);
int check_won (char* morpion);
int check_full (char* morpion);
int morpion_state (char* morpion);
int minimax (char* morpion, int depth, int isMaximizing);
int meilleurCoup (char* morpion);

int checkWinCondition(char *morpion);
int concatenate (int i, int j);
int checkFullBoard(char *board);
double realEvaluateSquare(char *pos);
double evaluateGame(char **position, int currentBoard);
int minimax_alphabeta (char** position, int boardToPlayOn, int alpha, int beta, int depth, int maximizingPlayer);
int calculateBestMove(char **board, int horizon, int last_move);

char* init_morpion();
char** init_superMorpion();
void show_morpion(char* morpion);
void show_superMorpion (char** superMorpion);
int convert(char* string);
int check_empty (char* morpion);
char* trans_superMorpion (char** superMorpion);
char **transfo_superMorpion (char** superMorpion);
int isValidMove(char** superMorpion, int grid, char col, int row);

void showMorpion(FILE *dotFile, char* chaine);
int generateDOT(FILE *dotFile, char** superMorpion);

#endif // ENTETE.H

