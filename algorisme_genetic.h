#ifndef ALGORISME_GENETIC_H
#define ALGORISME_GENETIC_H


#define NUM_GENS 30


int **crear_poblacio(int N);
void alliberar_poblacio(int **poblacio, int N);
int calcular_error(int *cromosoma);
int **seleccio_tournament(int **poblacio, int N, int K);
int **crossover(int **seleccionats, int N);
void mutacio(int **poblacio, int N, float prob_mutacio);
void actualitzar_millor(int *millor_cromosoma, int *candidat, int *millor_error, int error_candidat);

#endif
