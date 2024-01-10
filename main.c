#include "entête.h"



int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: %s <horizon>\n", argv[0]);
        return 1; 
    }

    char *endptr;
    int num = strtol(argv[1], &endptr, 10);

    // Vérifier les erreurs de type
    if (*endptr != '\0' || endptr == argv[1]) {
        printf("Input invalid. Entrez un int.\n");
        return 1; 
    }


    char** superMorpion = init_superMorpion();
    int player;      // Indice pour savoir qui joue
    int grid = 0;        // Numéro de la grille qui se joue (de 0 à 9)
    int gridFull = 1;     // Numéro pour savoir si la grill dans laquelle on joue est gagnée ou pleine
    int prevGrid;        // Numéro de la grille qui a été jouée avant
    int tab[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Liste pour connaître les morpions plein (0 si plein)
    int horizon = num;

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
            if (gridFull == 1) {
                show_superMorpion(superMorpion);
                // Récupération de ce que le joueur veut jouer
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
                while (tab[string[0] - '0' - 1] == 0  || isValidMove(superMorpion, grid, col, row) == 0) {
                    printf("Coup inv alide, veuillez recommencer : ");
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
                gridFull = 0;
                player = 0;
            } else {
                prevGrid = grid;
                show_superMorpion(superMorpion);
                // Récupération de ce que le joueuer veut jouer
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
                while (isValidMove(superMorpion, grid, col, row) == 0 || prevGrid != grid) {
                    printf("Coup invalide, veuillez recommencer : ");
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
            char **superM = transfo_superMorpion(superMorpion);
            int play = calculateBestMove(superM, horizon, grid);
            if (grid != 0) {
                prevGrid = grid;
            } else {
                prevGrid = 1;       // Comme ça je n'ai pas à mettre de condition if dans la partie "Conséquences du coup"
            }
            grid = play % 10;
            superMorpion[play/10-1][grid-1] = AI;
            player = 1;
        }
        
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
        if (check_won(superMorpion[prevGrid-1]) == PLAYER_O) {
            printf("Vous avez perdu le morpion %d\n", prevGrid);

            // Vérifions si le supermorpion est gagné
            char* superM = trans_superMorpion(superMorpion);
            show_morpion(superM);   // Test
            if (check_won(superM) == PLAYER_O) {
                printf("Vous avez perdu le supermorpion, réessayez !!!\n");
                    break;
            }
        }
        if (check_won(superMorpion[prevGrid-1]) == PLAYER_X) {
            printf("Vous avez gagné le morpion %d\n", prevGrid);
            // Vérifions si le supermorpion est gagné
            char* superM = trans_superMorpion(superMorpion);
            if (check_won(superM) == PLAYER_X) {
                printf("Vous avez gagné le supermorpion !!!\n");
                    break;
            }
        }

        // Cas du morpion nul
        if (check_full(superMorpion[prevGrid-1]) && check_won(superMorpion[prevGrid-1]) == 0) {
            printf("Il y a égalité dans le morpion %d\n", prevGrid);
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
            printf("CountX = %d\nCountO = %d", CountX, CountO);
            if (CountX >= 5) {
                printf("Vous avez gagné le supermorpion!!!\n");
            } else if (CountO >= 5) {
                printf("Vous avez perdu le supermorpion, réessayez !!!\n");
            } else {
            printf("La partie est terminée, il y a égalité !!\n ");
            }
            break;
        }      

        // On change la valeur de tab si le morpion est fini
        if (check_full(superMorpion[prevGrid-1]) || check_won(superMorpion[prevGrid-1]) != 0) {
            // On note que le morpion est pris
            tab[prevGrid-1] = 0;  
        }

        // On change la valeur de gridFull si le morpion "suivant" est fini
        if (check_full(superMorpion[grid-1]) || check_won(superMorpion[grid-1]) != 0) {
            // On note le morpion gagner pour changer la valeur de gridFull 
            gridFull = 1;     
        } else {
            gridFull = 0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        free(superMorpion[i]);
    }
    free(superMorpion);
    
    return 0;
}
