
#include "algorisme_genetic.h"

#define NUM_GENS 30

int main(const int argc, const char *argv[]) {
    arguments arg = {G_DEFAULT, N_DEFAULT, PROB_DEFAULT, K_DEFAULT};

    // Leer parámetros de la línea de comandos
    command_line(argc, argv, &arg);

    srand(time(NULL));

    // 1. Inicialitzar la població
    int **poblacio = crear_poblacio(arg.n);

    // 2. Inicialitzar el millor cromosoma
    int *millor_cromosoma = (int *)malloc(NUM_GENS * sizeof(int));
    if (millor_cromosoma == NULL) {
        printf("Error reservant memòria per al millor cromosoma.\n");
        exit(1);
    }
    int millor_error = calcular_error(poblacio[0]); // Inicialitzar amb el primer cromosoma
    for (int i = 0; i < NUM_GENS; i++) {
        millor_cromosoma[i] = poblacio[0][i];
    }

    // 3. Bucle principal de l'algorisme genètic
    for (int generacio = 0; generacio < arg.g; generacio++) {
        // a. Selecció
        int **seleccionats = seleccio_tournament(poblacio, arg.n, arg.k);

        // b. Crossover
        int **descendents = crossover(seleccionats, arg.n);

        // c. Mutació
        mutacio(descendents, arg.n, arg.prob);

        // d. Avaluació i actualització de la població
        for (int i = 0; i < arg.n; i++) {
            int error_descendent = calcular_error(descendents[i]);
            actualitzar_millor(millor_cromosoma, descendents[i], &millor_error, error_descendent);

            // Alliberar la memòria del cromosoma antic i reemplaçar-lo amb el descendent
            free(poblacio[i]);
            poblacio[i] = descendents[i]; // Assignem la direcció de memoria de descendents a poblacio
        }

        // Alliberar la memòria de la població seleccionada
        alliberar_poblacio(seleccionats, arg.n);

        printf("Generació %d: Millor error = %d\n", generacio, millor_error);
    }

    // 4. Imprimir el millor cromosoma trobat
    printf("\nMillor cromosoma trobat:\n");
    for (int i = 0; i < NUM_GENS; i++) {
        printf("%d", millor_cromosoma[i]);
    }
    printf("\nError: %d\n", millor_error);

    // 5. Alliberar la memòria
    free(millor_cromosoma);
    alliberar_poblacio(poblacio, arg.n);

    return 0;
}
