#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "algorisme_genetic.h"

void test_crear_poblacio() {
    int N = 10;
    int **poblacio = crear_poblacio(N);
    assert(poblacio != NULL);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < NUM_GENS; j++) {
            assert(poblacio[i][j] == 0 || poblacio[i][j] == 1);
        }
    }
    alliberar_poblacio(poblacio, N);
    printf("Test crear_poblacio: OK\n");
}

void test_calcular_error() {
    int cromosoma[NUM_GENS] = {
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }; // Aquesta combinació dona exactament 1977
    int error = calcular_error(cromosoma);
    assert(error == 0);
    printf("Test calcular_error: OK\n");
}

void test_seleccio_tournament() {
    int N = 10, K = 3;
    int **poblacio = crear_poblacio(N);
    int **seleccionats = seleccio_tournament(poblacio, N, K);
    assert(seleccionats != NULL);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < NUM_GENS; j++) {
            assert(seleccionats[i][j] == 0 || seleccionats[i][j] == 1);
        }
    }
    alliberar_poblacio(poblacio, N);
    alliberar_poblacio(seleccionats, N);
    printf("Test seleccio_tournament: OK\n");
}

void test_crossover() {
    int N = 10;
    int **seleccionats = crear_poblacio(N);
    int **descendents = crossover(seleccionats, N);
    assert(descendents != NULL);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < NUM_GENS; j++) {
            assert(descendents[i][j] == 0 || descendents[i][j] == 1);
        }
    }
    alliberar_poblacio(seleccionats, N);
    alliberar_poblacio(descendents, N);
    printf("Test crossover: OK\n");
}

void test_mutacio() {
    int N = 10;
    float prob = 1.0f; // 100% mutació per provar
    int **poblacio = crear_poblacio(N);
    
    // Copiem valors originals
    int **copia = crear_poblacio(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < NUM_GENS; j++)
            copia[i][j] = poblacio[i][j];

    mutacio(poblacio, N, prob);

    // Assegurem que hi ha hagut almenys un canvi
    int diferent = 0;
    for (int i = 0; i < N && !diferent; i++)
        for (int j = 0; j < NUM_GENS && !diferent; j++)
            if (poblacio[i][j] != copia[i][j]) diferent = 1;

    assert(diferent);
    alliberar_poblacio(poblacio, N);
    alliberar_poblacio(copia, N);
    printf("Test mutacio: OK\n");
}

void test_actualitzar_millor() {
    int millor[NUM_GENS] = {1};  // Cromosoma pitjor
    int candidat[NUM_GENS] = {0}; // Cromosoma millor
    int millor_error = 9999;
    int error_candidat = 1;
    
    actualitzar_millor(millor, candidat, &millor_error, error_candidat);
    
    assert(millor_error == 1);
    for (int i = 0; i < NUM_GENS; i++) assert(millor[i] == 0);
    printf("Test actualitzar_millor: OK\n");
}

int main() {
    srand(time(NULL));  // inicialitza generador aleatori
    
    test_crear_poblacio();
    test_calcular_error();
    test_seleccio_tournament();
    test_crossover();
    test_mutacio();
    test_actualitzar_millor();

    printf("TOTS ELS TESTS HAN PASSAT CORRECTAMENT ✅\n");
    return 0;
}
