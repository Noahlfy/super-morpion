#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "entête.h"

#define AI 'o'
#define PLAYER 'x'
#define PLAYER_O 1
#define PLAYER_X 2


char* init_morpion() {
    char* morpion = (char*)malloc(SIZE*sizeof(char));
    for (int i=0; i<SIZE; i++) {
        morpion[i]='.';
    }
    return morpion;
}

char** init_superMorpion() {
    char** superMorpion = (char**)malloc(SIZE*sizeof(char*));
    for (int i=0; i<SIZE; i++) {
        superMorpion[i] = init_morpion();
    }
    return superMorpion; 
}

void show_morpion(char* morpion) {
    for (int i=0; i<SIZE; i+=3) {
        printf( "%c%c%c\n", morpion[i], morpion[i+1], morpion[i+2]);
    }
}
void show_superMorpion (char** superMorpion) {
    for (int i=0; i<SIZE; i+=3) {
    printf(" %c%c%c   %c%c%c   %c%c%c \n", superMorpion[i][0], superMorpion[i][1], superMorpion[i][2], superMorpion[i+1][0], superMorpion[i+1][1], superMorpion[i+1][2], superMorpion[i+2][0], superMorpion[i+2][1], superMorpion[i+2][2]);
    printf(" %c%c%c   %c%c%c   %c%c%c \n", superMorpion[i][3], superMorpion[i][4], superMorpion[i][5], superMorpion[i+1][3], superMorpion[i+1][4], superMorpion[i+1][5], superMorpion[i+2][3], superMorpion[i+2][4], superMorpion[i+2][5]);
    printf(" %c%c%c   %c%c%c   %c%c%c \n", superMorpion[i][6], superMorpion[i][7], superMorpion[i][8], superMorpion[i+1][6], superMorpion[i+1][7], superMorpion[i+1][8], superMorpion[i+2][6], superMorpion[i+2][7], superMorpion[i+2][8]);
    printf("                          \n");
    }
}

int convert(char* string) {
    int col = string[1] - 'a';
    int row = '3' - string[2];

    int i = col + 3 * row;
    return i;
}


// Vérifier si le morpion est vide
int check_empty (char* morpion) {
    for (int i=0; i<SIZE; i++) {
        if (morpion[i] != '.') return 0;
    }
    return 1;
}

//Transformer le supermorpion en morpion pour pouvoir lui appliquer le minimax
char* trans_superMorpion (char** superMorpion) {
    char* morpion = (char*)malloc(SIZE * sizeof(char));
    for (int i=0; i<SIZE; i++) {
        int winner = check_won(superMorpion[i]);
        if (winner == PLAYER_O) {
            morpion[i] = 'O';
        } else if (winner == PLAYER_X) {
            morpion[i] = 'X';
        } else if (check_full(superMorpion[i])) {
            morpion[i] = 'N';       // N pour nul
        } else if (check_empty(superMorpion[i])) {
            morpion[i] = '.';
        } else {
            morpion[i] = '.';  //Lettre au hasard
        }
    }
    return morpion;
}
