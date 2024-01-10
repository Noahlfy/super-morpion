#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "entête.h"



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

// Transformer le supermorpion avec des 1 des -1 et des 0
char **transfo_superMorpion (char** superMorpion) {
    char **superM = malloc(sizeof(char*)*SIZE);
    for (int i=0; i<SIZE; i++) {
        superM[i] = malloc(sizeof(char)*SIZE);
    }

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (superMorpion[i][j] == 'x') {
                superM[i][j] = PLAYER_X; 
            } else if (superMorpion[i][j] == 'o') {
                superM[i][j] = PLAYER_O;
            } else {
                superM[i][j] = 0;
            }
        }
    }
    return superM;
}


// Fonction pour vérifier si le coup entré est valide
int isValidMove(char** superMorpion, int grid, char col, int row) {
    // Vérifier si les valeurs de grille, colonne et ligne sont dans les plages valides
    if (grid < 1 || grid > SIZE || col < 'a' || col > 'c' || row < 1 || row > SIZE) {
        return 0; // Coup invalide
    }

    // Convertir l'entrée en indices du tableau
    int gridIndex = grid - 1;
    int colIndex = col - 'a';
    int rowIndex = row - 1;

    // Vérifier si la cellule est vide
    if (superMorpion[gridIndex][rowIndex * SIZE + colIndex] == '.') {
        return 1; // Coup valide
    } else {
        return 0; // La cellule n'est pas vide, coup invalide
    }
}