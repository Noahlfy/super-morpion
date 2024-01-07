#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


char* generateFEN (char**** superMorpion, int position, char tour) {
    char* FEN[90];    // La taille maximale est 86
    int a=0;
    for (int i=0, i<SIZE, i++) {
        for (int j=0, j<SIZE, i++){
            // On fait la FEN d'un morpion simple pour ensuite les concaténer
            char* morpionFEN[10];
            char** morpion = superMorpion[i][j];
            int m=0;
            for (int k=0, k<SIZE, k++) {
                for (int l=0, l<SIZE, l++) {
                    // Si il y'a des cases vides
                    if (morpion[i][j] == '.') {
                        int p=0;
                        for (int n=i; n<3; n++) {
                            for (int o=j; morpion[n][0] == '.'; o++) {
                                p++;
                            }     
                        }
                        morpionFEN[m]='p';
                        m++;
                    } else {
                        morpionFEN[m] = morpion[i][j];
                    m++;
                    }
                }
            }
            // Concaténation
            if (morpionFEN == 'xxxxxxxxx') {
                FEN[a]='X';
                a++;
            }
            if (morpionFEN == 'yyyyyyyyyy') {
                FEN[a]='Y';
                a++;
            }
            else {
                for (int b=0; morpionFEN[b]; b++) {
                    FEN[a]= morpionFEN[b];
                    a++;
                }
                
            }
        }
    }
}

// Lire la notation FEN pour l'implémenter dans generateDOT
char* convertFEN (char* FEN) {

    int size = strlen(FEN);
    char* converted = malloc(sizeof(char) * (pow(SIZE,4)+1));
    int i=0; 
    // Indice converted
    int j=0;

    // Savoir où le joueur a joué pour la dernière fois et à qui est le tour ne m'intéresse pas pour les fichiers dot
    while (FEN[i] != '.') {
        if (FEN[i] == 'X') {
            for (int l=0; l<9; l++) {
                converted[j]='X';
                j++;
            }
            i++;
        }
        if (FEN[i] == 'O') {
            for (int l=0; l<9; l++) {
                converted[j]='O';
                j++;
            }
            i++;
        }
        if (FEN[i] == 'x') {
            converted[j]='x';
            j++;
            i++;
        }
        if (FEN[i] == 'c') {
            converted[j]='c';
            j++;
            i++;
        }
        // Il ne reste plus que le cas où ce sont des int
        else { 
            int k=atoi(&FEN[i]);
            for (int l=0; l<k; l++) {
                converted[j]='.';
                j++;
            }
            i++;
        }
    }
    return converted;
}
