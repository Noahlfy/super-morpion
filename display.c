#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "entête.h"

void showMorpion(FILE *dotFile, char* chaine) {
    fprintf(dotFile, "<TD bgcolor=\"white\">\n");
    fprintf(dotFile, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">");

    for (int i = 0; i < 3; i++) {
        fprintf(dotFile, "\n<TR>\n");

        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            fprintf(dotFile, "<TD bgcolor=\"white\">%c</TD>\n", chaine[index]);
        }

        fprintf(dotFile, "</TR>\n");
    }

    fprintf(dotFile, "</TABLE>\n");
    fprintf(dotFile, "</TD>\n\n");
}

void showMorpionWon(FILE *dotFile, char* color) {
    if (!strncmp(color, "white", 5)) {
        fprintf(dotFile, "<TD bgcolor=\"black\">\n");
        fprintf(dotFile, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");

        for (int i = 0; i < 3; i++) {
            fprintf(dotFile, "<TR>\n");

            for (int j = 0; j < 3; j++) {
                fprintf(dotFile, "<TD bgcolor=\"white\">&nbsp;</TD>\n");
            }

            fprintf(dotFile, "</TR>\n\n");
        }

        fprintf(dotFile, "</TABLE>\n");
        fprintf(dotFile, "</TD>\n\n");
    }

    if (!strncmp(color, "black", 5)) {
        fprintf(dotFile, "<TD bgcolor=\"white\">\n");
        fprintf(dotFile, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");

        for (int i = 0; i < 3; i++) {
            fprintf(dotFile, "<TR>\n");

            for (int j = 0; j < 3; j++) {
                fprintf(dotFile, "<TD bgcolor=\"black\">&nbsp;</TD>\n");
            }

            fprintf(dotFile, "</TR>\n");
        }

        fprintf(dotFile, "</TABLE>\n");
        fprintf(dotFile, "</TD>\n\n");
    }
}

int generateDOT(FILE *dotFile, char** superMorpion) {
    fprintf(dotFile, "digraph  {\n");
    fprintf(dotFile, "a0 [shape=none label=<\n");
    fprintf(dotFile, "<TABLE border=\"0\" cellspacing=\"10\" cellpadding=\"10\" style=\"rounded\" bgcolor=\"black\">\n");
    fprintf(dotFile, "<TR>\n\n");

    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            fprintf(dotFile, "</TR>\n<TR>\n\n");
        }
        if (check_won(superMorpion[i]) == PLAYER_X) {
            showMorpionWon(dotFile, "black");
        } else if (check_won(superMorpion[i]) == PLAYER_O) {
            showMorpionWon(dotFile, "white");
        } else {
            char string[9];
            for (int j = 0; j < SIZE; j++) {
                string[j] = superMorpion[i][j];
            }
            showMorpion(dotFile, string);
        }
       
    }

    fprintf(dotFile, "</TR>\n");
    fprintf(dotFile, "</TABLE>\n\n");
    fprintf(dotFile, ">];\n\n");
    fprintf(dotFile, "}\n");
    return 0;
}

