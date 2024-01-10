#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LENGTH 50

// Structure représentant l'état du morpion
typedef struct {
    char tableau[3][3];
    int size;
    int id;
    char trait;
} MorpionState;

int *globalList;
int id = 0;
int PLAYER_X;
int PLAYER_O;
char PLAY_O;
char PLAY_X;

void show_morpion(MorpionState *morpion) {
    for(int i=0; i<3; i++) {
        printf(" %c%c%c\n", morpion->tableau[i][0], morpion->tableau[i][1], morpion->tableau[i][2]);
    }
}


char *parseBoardState(char *board_state) {
    char *board = malloc(sizeof(char *) * 10);
    int j = 0;
    for (int i = 0; board_state[i]; i++) {
        if (isdigit(board_state[i])) {
            int num = board_state[i] - '0';
            for (int k = 0; k < num; k++) {
                board[j] = '.';
                j++;
            }
        } else if (board_state[i] == 'o') {
            board[j] = toupper('o');
            j++;
        } else if (board_state[i] == 'x') {
            board[j] = toupper('x');
            j++;
        } else if (board_state[i] == ' ') {
            board[j] = ' ';
            j++;
        }
    }
    board[j] = '\0';
    return board;
}

MorpionState genMorpionState(char *resultat) {
    MorpionState morpion;
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            morpion.tableau[i][j] = resultat[k];
            k++;
        }
    }
    morpion.trait = resultat[10];
    morpion.size = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (morpion.tableau[i][j] == 'O' || morpion.tableau[i][j] == 'X') {
                morpion.size += 1;
            }
        }
    }
    morpion.id = 0;
    return morpion;
}

int Current(char *resultat) {
    if (resultat[10] == 'O') {
        return 1;
    }
    return 0;
}

int Next(int i) {
    if (i == 1) return 0;
    return 1;
}

char *whatcolour(int isMaximizing) {
    if (isMaximizing == 1) return "green";
    else return "red";
}

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int min(int a, int b) {
    return (a <= b) ? a : b;
}

int check_won (MorpionState* morpion) {
    for (int i=0; i<3; i++) {
        // Vérification des lignes
        if ( (morpion->tableau[i][0] == morpion->tableau[i][1]) && (morpion->tableau[i][0] == morpion->tableau[i][2]) && (morpion->tableau[i][0] == 'x')) return PLAYER_X;
        if ( (morpion->tableau[i][0] == morpion->tableau[i][1]) && (morpion->tableau[i][0] == morpion->tableau[i][2]) && (morpion->tableau[i][0] == 'o')) return PLAYER_O;
        // Vérification des colonnes
        if ( (morpion->tableau[0][i] == morpion->tableau[1][i]) && (morpion->tableau[0][i] == morpion->tableau[2][i]) && (morpion->tableau[0][i] != 'x')) return PLAYER_X;
        if ( (morpion->tableau[0][i] == morpion->tableau[1][i]) && (morpion->tableau[0][i] == morpion->tableau[2][i]) && (morpion->tableau[0][i] != 'o')) return PLAYER_O;
    }
    // Vérification de la diagonale
    if ( (morpion->tableau[0][0] == morpion->tableau[1][1]) && (morpion->tableau[0][0] == morpion->tableau[2][2]) && (morpion->tableau[0][0] != 'x')) return PLAYER_X;
    if ( (morpion->tableau[0][0] == morpion->tableau[1][1]) && (morpion->tableau[0][0] == morpion->tableau[2][2]) && (morpion->tableau[0][0] != 'o')) return PLAYER_O;

    // Vérification de l'autre diagonale
    if ( (morpion->tableau[0][2] == morpion->tableau[1][1]) && (morpion->tableau[0][2] == morpion->tableau[2][0]) && (morpion->tableau[0][2] != 'x')) return PLAYER_X;
    if ( (morpion->tableau[0][2] == morpion->tableau[1][1]) && (morpion->tableau[0][2] == morpion->tableau[2][0]) && (morpion->tableau[0][2] != 'o')) return PLAYER_O;
    return 0;
}

// Vérifier si le morpion est plein
int check_full (MorpionState* morpion) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (morpion->tableau[i][j] == '.') return 0;
        }
    }
    return 1;
}

// Fonction pour évaluer l'état du morpion
int morpion_state (MorpionState* morpion) {
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
int minimax (MorpionState* morpion, int depth, int isMaximizing) {       // La variable depth n'est pas utile pour le morpion car il n'y a que 9 étapes de jeu
    printf("isMaximising = %d\n", isMaximizing);

    int score = morpion_state(morpion);

    if (score == -1 || score == 1 || check_full(morpion)) {
        return score;
    }

    // C'est au tour de l'IA (le maximisant) 
    if (isMaximizing) {
        int val = -1000;
        // Parcourir chaque cellule du morpion
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                // Vérifier que la cellule est vide 
                if (morpion->tableau[i][j] == '.') {
                    // Jouer dans cette  cellule
                    morpion->tableau[i][j] = PLAY_O;
                    // Appel récursif
                    val = max (val, minimax( morpion, depth + 1, !isMaximizing));
                    // On annule le coup pour les suivants
                    morpion->tableau[i][j] = '.';
                }
            }
        }
        return val;
    } else {
        int val = 1000;
        // Parcourir chaque cellule du morpion
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                // Vérifier que la cellule est vide 
                if (morpion->tableau[i][j] == '.') {
                    // Jouer dans cette  cellule
                    morpion->tableau[i][j] = PLAY_X;
                    // Appel récursif
                    val = min (val, minimax( morpion, depth + 1, !isMaximizing));
                    // On annule le coup pour les suivants
                    morpion->tableau[i][j] = '.';
                }
            }
        }
        return val;
    }
}

void afficherNoeud(MorpionState *morpion, int moveId, int isMaximizing) {
    printf("  m%d [shape=none label=<<TABLE border='0' cellspacing='10' cellpadding='10' style='rounded' bgcolor='black'>\n", id);
    printf("    <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[0][0]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[0][1]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[0][2]);
    printf("    </TR>\n");
    printf("    <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[1][0]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[1][1]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[1][2]);
    printf("    </TR>\n");
    printf("    <TR>\n");
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[2][0]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[2][1]);
    printf("    <TD bgcolor=\"white\">%c</TD>\n", morpion->tableau[2][2]);
    printf("    </TR>\n");
    printf("    <TR><TD bgcolor= '%s' colspan='3'>m%d</TD></TR>\n", whatcolour(isMaximizing), id);
    printf("</TABLE>>];\n");
    printf("\n");
    if (id > 0) {
        if (morpion->size > globalList[id - 1]) {
            printf("  m%d -> m%d ;\n", id - 1, id);
        } else {
            int i = 1;
            while (id - i >= 0 && morpion->size <= globalList[id - i]) {
                i++;
            }
            printf("  m%d -> m%d ;\n", id - i, id);
        }
    }
}

int Howmany(MorpionState *morpion) {
    int s = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (morpion->tableau[i][j] == 'O' || morpion->tableau[i][j] == 'X') s += 1;
        }
    }
    return s;
}

void construireArbreDecisionRecursive(MorpionState *morpion, char *resultat, int who, int moveId, int isMaximizing) {
    afficherNoeud(morpion, moveId, isMaximizing);
    printf("m%d [xlabel=\"%d\"]", id, minimax(morpion, moveId, isMaximizing));
    id++;
    if (morpion_state(morpion) != 0) {
        return;
    }
    // Génère les positions possibles et appelle récursivement pour chaque position
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (morpion->tableau[i][j] == '.') {
                MorpionState nouveauMorpion = *morpion;
                nouveauMorpion.tableau[i][j] = (who == 1) ? 'O' : 'X';
                nouveauMorpion.size = Howmany(&nouveauMorpion);
                nouveauMorpion.id = id;
                int *nouveauGlobalList = (int *)realloc(globalList, (id + 1) * sizeof(int));
                if (nouveauGlobalList == NULL) {
                    fprintf(stderr, "Reallocation de mémoire a échoué. Quitter le programme.\n");
                }
                globalList = nouveauGlobalList;
                globalList[id] = nouveauMorpion.size;
                int nextPlayer = (who == 1) ? 0 : 1;
                construireArbreDecisionRecursive(&nouveauMorpion, resultat, nextPlayer, moveId + 1, 1 - isMaximizing);
            }
        }
    }
}


void construireArbreDecisionRecursiveBis(MorpionState *morpion, char *resultat, int who, int moveId, int isMaximizing) {
    show_morpion(morpion);
    printf("id : %d, minmax = %d\n", id, minimax(morpion, moveId, isMaximizing));
    printf("\n------------------\n\n");

    id++;
    if (morpion_state(morpion) != 0) {
        return;
    }
    // Génère les positions possibles et appelle récursivement pour chaque position
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (morpion->tableau[i][j] == '.') {
                MorpionState nouveauMorpion = *morpion;
                nouveauMorpion.tableau[i][j] = (who == 1) ? 'O' : 'X';
                nouveauMorpion.size = Howmany(&nouveauMorpion);
                nouveauMorpion.id = id;
                int *nouveauGlobalList = (int *)realloc(globalList, (id + 1) * sizeof(int));
                if (nouveauGlobalList == NULL) {
                    fprintf(stderr, "Reallocation de mémoire a échoué. Quitter le programme.\n");
                }
                globalList = nouveauGlobalList;
                globalList[id] = nouveauMorpion.size;
                int nextPlayer = (who == 1) ? 0 : 1;
                construireArbreDecisionRecursiveBis(&nouveauMorpion, resultat, nextPlayer, moveId + 1, 1 - isMaximizing);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Il n'a pas d'argument en ligne de commande\n");
        return 1;
    } else {
        MorpionState morpion = genMorpionState(parseBoardState(argv[1]));
        int who = Current(parseBoardState(argv[1]));

        if (who == 1) {
            PLAY_X = 'X';
            PLAY_O = 'O';
            PLAYER_O = 1;
            PLAYER_X = -1;
        } else {
            PLAY_X = 'O';
            PLAY_O = 'X';
            PLAYER_O = -1;
            PLAYER_X = 1;
        }
        printf("digraph  {\n");
        //construireArbreDecisionRecursive(&morpion, parseBoardState(argv[1]), who, 0, 1);
        
        construireArbreDecisionRecursiveBis(&morpion, parseBoardState(argv[1]), who, 0, 1);
        printf("}\n");
    }
}
 
