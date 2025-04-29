#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorisme_genetic.h"

#define NUM_GENS 30

int main(const int argc,const char *argv[]) {
    arguments arg = {G_DEFAULT, N_DEFAULT, PROB_DEFAULT, K_DEFAULT};

    // Leer parámetros de la línea de comandos
    command_line(argc, argv, &arg);

    srand(time(NULL));

    int **poblacio = crear_poblacio(arg.n);

    for (int i = 0; i < arg.n; i++) {
        printf("Cromosoma %d: ", i);
        for (int j = 0; j < NUM_GENS; j++) {
            printf("%d", poblacio[i][j]);
        }
        printf("\n");
    }

    alliberar_poblacio(poblacio, arg.n);

    return 0;
}
