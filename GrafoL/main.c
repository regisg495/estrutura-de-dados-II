#include <stdio.h>

#include "Grafo.h"

int main() {

    Vertice *vertice = inicializa();

    Vertice *temp;

    insereVertice(&vertice, 2);
    insereVertice(&vertice, 1);
    insereVertice(&vertice, 3);

    insereAresta(vertice, 1, 5);
    insereAresta(vertice, 1, 2);
    insereAresta(vertice, 1, 3);
    insereAresta(vertice, 1, 7);

    visualiza(vertice);

    return 0;
}