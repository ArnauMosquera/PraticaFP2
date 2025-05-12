#ifndef ALGORISME_GENETIC_H
#define ALGORISME_GENETIC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h> // Per strcmp
#include <stdbool.h> // Per bool

#define NUM_GENS 30
#define G_DEFAULT 100
#define N_DEFAULT 40
#define PROB_DEFAULT 0.05
#define K_DEFAULT 5

typedef struct arguments{
    int g;
    int n;
    float prob;
    int k;
}arguments;

int command_line(int argc, const char *argv[], arguments *arg);
int **crear_poblacio(int N);
void alliberar_poblacio(int **poblacio, int N);
int calcular_error(int *cromosoma);
int **seleccio_tournament(int **poblacio, int N, int K);
int **crossover(int **seleccionats, int N);
void mutacio(int **poblacio, int N, float prob_mutacio);
void actualitzar_millor(int *millor_cromosoma, int *candidat, int *millor_error, int error_candidat);

#endif
