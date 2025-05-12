
#include "algorisme_genetic.h"

#define NUM_GENS 30

int command_line(const int argc, const char *argv[], arguments *arg){
    if (argc > 1) {
        int i = 1;
        while (i < argc) {
            if (strcmp(argv[i], "-G") == 0 && i + 1 < argc) {
                arg->g = atoi(argv[i + 1]);
                i += 2;
            } else if (strcmp(argv[i], "-N") == 0 && i + 1 < argc) {
                arg->n = atoi(argv[i + 1]);
                i += 2;
            } else if (strcmp(argv[i], "-PROB") == 0 && i + 1 < argc) {
                arg->prob = atof(argv[i + 1]);
                i += 2;
            } else if (strcmp(argv[i], "-K") == 0 && i + 1 < argc) {
                arg->k = atoi(argv[i + 1]);
                i += 2;
            } else {
                printf("Opció incorrecta: %s\n", argv[i]);
                i++;
            }
        }
    }
    return 0;
}

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
        suma+=cromosoma[i]*pow(i+1,2);
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

int **crossover(int **seleccionats, int N){
    int **descendents = (int **)malloc(N * sizeof(int *));
    if (descendents == NULL) {
        fprintf(stderr, "Error: No s'ha pogut reservar memoria per als descendents.\n");
        exit(1);
    }

    // Processem els pares de dos en dos
    int i;
    for (i = 0; i < N - 1; i += 2) {
        int *pare1 = seleccionats[i];
        int *pare2 = seleccionats[i + 1];

        // Reservem memòria per als fills
        descendents[i] = (int*)malloc(NUM_GENS * sizeof(int));
        descendents[i + 1] = (int*)malloc(NUM_GENS * sizeof(int));
        if (descendents[i] == NULL || descendents[i + 1] == NULL) {
            fprintf(stderr, "Error: No s'ha pogut reservar memoria per als fills %d o %d.\n", i, i + 1);
            for (int j = 0; j < i; j++) {
                free(descendents[j]);
            }
            exit(1);
        }

        // Punt de creuament aleatori
        int punt_crossover = 1 + rand() % (NUM_GENS - 1);

        // Creació dels fills
        for (int j = 0; j < NUM_GENS; j++) {
            if (j < punt_crossover) {
                descendents[i][j] = pare1[j];
                descendents[i + 1][j] = pare2[j];
            } else {
                descendents[i][j] = pare2[j];
                descendents[i + 1][j] = pare1[j];
            }
        }
    }

    // Si N és senar, copiem l'últim individu sense creuament
    if (N % 2 != 0) {
        descendents[N - 1] = (int*)malloc(NUM_GENS * sizeof(int));
        if (descendents[N - 1] == NULL) {
            fprintf(stderr, "Error: No s'ha pogut reservar memoria per al darrer individu.\n");
            for (int j = 0; j < N - 1; j++) {
                free(descendents[j]);
            }
            exit(1);
        }
        for (int j = 0; j < NUM_GENS; j++) {
            descendents[N - 1][j] = seleccionats[N - 1][j];
        }
    }

    return descendents;
}

void mutacio(int **poblacio, int N, float prob_mutacio){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < NUM_GENS; j++) {
            //Generem un nombre aleatori entre 0.0 i 1.0 
            double prob_aleatoria = (double)rand() / RAND_MAX;
            if (prob_aleatoria < prob_mutacio) {
                //Camviem el bit
                poblacio[i][j] = 1 - poblacio[i][j];
            }
        }
    }
}

void actualitzar_millor(int *millor_cromosoma, int *candidat, int *millor_error, int error_candidat) {
    if (error_candidat < *millor_error) {
        *millor_error = error_candidat;
        for (int i = 0; i < NUM_GENS; i++) {
            millor_cromosoma[i] = candidat[i];
        }
    }
}
