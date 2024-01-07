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

// Fonction pour évaluer l'état du morpion
int morpion_state (char* morpion) {
    int winner = check_won(morpion);
    // Si le joueur maximisant gagne, retourner une valeur positive
    if (winner == PLAYER_O) {
        return 1;
    } 
    if ((check_won(morpion) == 0) && check_full(morpion)) {
        // Si la partie est nulle, on retourne une valeur nulle
        return 0;
    } 
    if (winner == PLAYER_X) {
        // Si la partie pour le maximisant est perdue, on retourne une valeur négative
        return -1;
    }
    return 0;
}



// Implémentation de la fonction minimax
int minimax (char* morpion, int depth, int isMaximizing) {       // La variable depth n'est pas utile pour le morpion car il n'y a que 9 étapes de jeu
    int score = morpion_state(morpion);
    if (score == -1 || score == 1 || check_full(morpion)) {
        return score;
    }

    // C'est au tour de l'IA (le maximisant) 
    if (isMaximizing) {
        int val = -1000;
        // Parcourir chaque cellule du morpion
        for (int i=0; i<SIZE; i++) {
            // Vérifier que la cellule est vide 
            if (morpion[i] == '.') {
                // Jouer dans cette  cellule
                morpion[i] = AI;
                // Appel récursif
                val = max (val, minimax( morpion, depth + 1, !isMaximizing));
                // On annule le coup pour les suivants
                morpion[i] = '.';
            }
        }
        return val;
    } else {
        int val = 1000;
        // Parcourir chaque cellule du morpion
        for (int i=0; i<SIZE; i++) {
            // Vérifier que la cellule est vide 
            if (morpion[i] == '.') {
                // Jouer dans cette  cellule
                morpion[i] = PLAYER;
                // Appel récursif
                val = min (val, minimax( morpion, depth + 1, !isMaximizing));
                // On annule le coup pour les suivants
                morpion[i] = '.';
            }

        }
        return val;
    }
}

// Fonction pour déterminer le meilleur coup pour l'IA

int meilleurCoup (char* morpion) {
    int val = -1000;
    int number = -1;

    for (int i=0; i<SIZE; i++) {
        // Vérifier que la cellule est vide
        if (morpion[i] == '.') {
            // Jouer dans cette cellule
            morpion[i] = AI;
            int score = minimax(morpion, 0,0);

            // Annuler le coup
            morpion [i] = '.';
            if (score > val) {
                val = score;
                number = i;
            }
        }
    }
    return number; 
}
