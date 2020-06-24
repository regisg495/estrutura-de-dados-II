#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "Grafo.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);

    srand(time(NULL));

    Grafo *grafo;

    unsigned int verticesNaoInseridos = 0;
    unsigned int arestasNaoInseridas = 0;

    if (inicializaGrafo(&grafo)) {

        for (int i = 0; i < 50; i++) {
            int chaveVertice = rand() % 51;
            if (!insereVertice(grafo, chaveVertice)) verticesNaoInseridos++;
        }

    }

    for (int i = 0; i < 500; i++) {
        int chaveAresta = rand() % 501;
        int chaveVertice = rand() % 101;
        if (!insereAresta(grafo, chaveVertice, chaveAresta)) arestasNaoInseridas++;
    }

    visualiza(grafo);

    printf("\n\nChaves não inseridas: %d", verticesNaoInseridos);
    printf("\nArestas não inseridas: %d", arestasNaoInseridas);

    deletaGrafo(&grafo);

    return 0;
}