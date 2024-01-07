
#include "entête.h"

int main() {

    char** superMorpion = init_superMorpion();
    int player;      // Indice pour savoir qui joue
    int grid = 0;        // Numéro de la grille qui se joue (de 0 à 9, 0 pour aucune)
    int tab[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Liste pour connaître les morpions plein (0 si plein)

    // On demande si le joueur veut commencer
    char ans[3];
    printf("Voulez-vous commencer ? (O/N)");
    scanf("%s", ans);
    while (strncmp(ans,"O",1) && strncmp(ans,"N",1)) {
        printf("Erreur, veuillez recommencer (O/N): \n");
        scanf("%s", ans);
    }

    //Initialisation de l'indice
    if (!strncmp(ans,"O",1)) {
        player = 1;
    } else {
        player = 0;
    }
    printf("Vous jouez avec x\n");
    // Le jeu commence
    while (1) {
        if (player) {
            if (grid == 0) {
                // Récupération de ce que le joueur veut jouer
                show_superMorpion(superMorpion);
                char col;
                int row;
                printf("Jouez le coup souhaité (<#grille>(1..9) espace <#colonne>(a..c) <#ligne>(1..3))");
                scanf("%d %c%d", &grid, &col, &row);

                char string[4];
                string[0] = grid + '0';
                string[1] = col;
                string[2] = row + '0';
                string[3] = '\0'; 

                
                // On vérifie que le coup est valide
                while (tab[string[0] - '0' - 1] == 0  || superMorpion[grid-1][convert(string)] != '.' ) {
                scanf("%d %c%d", &grid, &col, &row);
                string[0] = grid + '0' ;
                string[1] = col;
                string[2] = row + '0';
                string[3] = '\0';  
                }

                // Le joueur joue
                superMorpion[grid-1][convert(string)] = PLAYER;

                // Changement de la valeur de grid
                grid = convert(string)+1;
                player = 0;
                printf("grid =  %d\n", grid);
            } else {
                // Récupération de ce que le joueuer veut jouer
                show_superMorpion(superMorpion);
                printf("Vous jouez dans le morpion n°%d\n", grid);
                char col;
                int row;
                printf("Jouez le coup souhaité (<#grille>%d espace <#colonne>(a..c) <#ligne>(1..3))", grid);
                scanf("%d %c%d", &grid, &col, &row);

                char string[4];
                string[0] = grid + '0';
                string[1] = col;
                string[2] = row + '0';
                string[3] = '\0'; 

                // On vérifie que le coup est valide
                while (superMorpion[grid-1][convert(string)] != '.' ) {
                printf("Coup invalide, veuillez recommencer\n");
                scanf("%d %c%d", &grid, &col, &row);
                string[0] = grid + '0' ;
                string[1] = col;
                string[2] = row + '0';
                string[3] = '\0';  
                }

                // Le joueur joue
                superMorpion[grid-1][convert(string)] = PLAYER;

                // Changement de la valeur de grid
                grid = convert(string)+1;
                player = 0;
            }
        } else {
            if (grid == 0) {
                //Transformer le supermorpion pour utiliser minimax
                char* superM = trans_superMorpion(superMorpion);
                show_morpion(superM);
                // On détermine le morpion qu'il faut jouer
                grid = meilleurCoup(superM) + 1;
                printf("Morpion choisi par l'IA : %d\n", grid);
                tab[grid-1] = 0;

                // On joue le meilleur coup possible
                int play = meilleurCoup(superMorpion[grid-1]);
                superMorpion[grid-1][play] = AI; 

                // On change la valeur de grid à l'endroit 
                grid = play+1;
                player = 1;
            } else {
                int play = meilleurCoup(superMorpion[grid-1]);
                superMorpion[grid-1][play] = AI;
                grid = play+1;
                player = 1;
            }
        }

        // Afficher le supermorpion 
        show_superMorpion(superMorpion);

        // Et dans un .dot

        unlink("g.dot");
        FILE *dotFile = fopen("g.dot", "a");
        if (dotFile == NULL) {
            perror("Erreur lors de l'ouverture du fichier DOT");
            return 1;
        }
        generateDOT(dotFile, superMorpion);
        // system("/usr/bin/dot -Tpng g.dot > g.png");
        fclose(dotFile);


        // Conséquences du coup

        // Cas du morpion gagné
        if (check_won(superMorpion[grid-1]) == PLAYER_O) {
            printf("Vous avez perdu le morpion %d\n", grid);

            // Vérifions si le supermorpion est gagné
            char* superM = trans_superMorpion(superMorpion);
            if (check_won(superM) == PLAYER_O) {
                printf("Vous avez perdu, réessayez !!!\n");
                    break;
            }
        }
        if (check_won(superMorpion[grid-1]) == PLAYER_X) {
            printf("Vous avez gagné le morpion %d\n", grid);
            // Vérifions si le supermorpion est gagné
            char* superM = trans_superMorpion(superMorpion);
            if (check_won(superM) == PLAYER_X) {
                printf("Vous avez gagné !!!\n");
                    break;
            }
        }

        // Cas du morpion nul
        if (check_full(superMorpion[grid-1]) && check_won(superMorpion[grid-1]) == 0) {
            printf("Il y a égalité dans le morpion %d\n", grid);
        }
        
        // On vérifie que le supermorpion n'est pas complet
        char* superM = trans_superMorpion(superMorpion);
        if (check_full(superM)) {
            // On vérifie si quelqu'un a gagné
            int CountX = 0;
            int CountO = 0;
            for (int i=0; i<SIZE; i++) {
                if ((superM[i] == 'X')) CountX++;
                if ((superM[i] == 'O')) CountO++;
            }
            if (CountX >= 5) {
                printf("Vous avez gagné !!!\n");
            } else if (CountO >= 5) {
                printf("Vous avez perdu, réessayez !!!\n");
            } else {
            printf("La partie est terminée, il y a égalité !!\n ");
            }
            break;
        }      

        // On change la valeur de grid si le morpion est fini
        if (check_full(superMorpion[grid-1]) || check_won(superMorpion[grid-1]) != 0) {
            // On note que le morpion est pris
            tab[grid-1] = 0; 
            // On note le morpion gagner pour changer la valeur de grid 
            grid = 0;     

        }
    }
    for (int i = 0; i < SIZE; i++) {
        free(superMorpion[i]);
    }
    free(superMorpion);
    
    return 0;
}
