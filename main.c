#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorisme_genetic.h"

#define NUM_GENS 30

int main(void) {
    int N = 40;
    srand(time(NULL));

    int **poblacio = crear_poblacio(N);

    for (int i = 0; i < N; i++) {
        printf("Cromosoma %d: ", i);
        for (int j = 0; j < NUM_GENS; j++) {
            printf("%d", poblacio[i][j]);
        }
        printf("\n");
    }

    alliberar_poblacio(poblacio, N);

    return 0;
}
