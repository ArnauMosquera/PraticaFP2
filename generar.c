#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorisme_genetic.h"

#define NUM_GENS 30

int **crear_poblacio(int N) {
    int **poblacio = (int **)malloc(N * sizeof(int *));
    if (poblacio == NULL) {
        printf("Error reservant memòria per la població.\n");
        exit(1);
    }
    
    for (int i = 0; i < N; i++) {
        poblacio[i] = (int *)malloc(NUM_GENS * sizeof(int));
        if (poblacio[i] == NULL) {
            printf("Error reservant memòria per un cromosoma.\n");
            exit(1);
        }
        
        for (int j = 0; j < NUM_GENS; j++) {
            poblacio[i][j] = rand() % 2;
        }
    }
    
    return poblacio;
}

void alliberar_poblacio(int **poblacio, int N) {
    for (int i = 0; i < N; i++) {
        free(poblacio[i]);
    }
    free(poblacio);
}
