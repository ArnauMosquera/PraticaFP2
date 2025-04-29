#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorisme_genetic.h"

#define NUM_GENS 30

int command_line(int argc, char *argv[], 


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

int calcular_error(int *cromosoma){
    int suma = 0;
    int error=0;
    for(int i = 0; i<30;i++){
        suma+=cromosoma[i]*(i+1)*(i+1);
    }
    error = abs(suma-1977);
    return error;
}

int **seleccio_tournament(int **poblacio, int N, int K) {
    if (K > N) {
        printf("Error: K no pot ser més gran que N.\n");
        exit(1);
    }

    int **seleccionats = (int **)malloc(N * sizeof(int *));
    if (seleccionats == NULL) {
        printf("Error reservant memòria per a la població seleccionada.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        int millor_index = rand() % N;  // Comença triant un cromosoma aleatori
        int millor_error = calcular_error(poblacio[millor_index]);

        for (int j = 1; j < K; j++) {
            int index = rand() % N;
            int error = calcular_error(poblacio[index]);

            if (error < millor_error) {
                millor_error = error;
                millor_index = index;
            }
        }

        // Copiar el millor cromosoma seleccionat
        seleccionats[i] = (int *)malloc(NUM_GENS * sizeof(int));
        if (seleccionats[i] == NULL) {
            printf("Error reservant memòria per un cromosoma seleccionat.\n");
            exit(1);
        }

        for (int g = 0; g < NUM_GENS; g++) {
            seleccionats[i][g] = poblacio[millor_index][g];
        }
    }

    return seleccionats;
}
