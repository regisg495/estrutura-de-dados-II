//
// Created by regis on 08/05/2020.
//

#ifndef GRAFOL_GRAFO_H
#define GRAFOL_GRAFO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Aresta {
    int chaveAresta;
    struct Aresta *prox;
} Aresta;

typedef struct Vertice {
    int chaveVertice;
    Aresta *inicio;
    struct Vertice *prox;
} Vertice;

Vertice *inicializa();

bool criaAresta(int chaveAresta, Aresta *prox, Aresta **pAresta);

bool criaVertice(int chaveVertice, Vertice *prox, Vertice **pVertice);

bool buscaVertice(int chaveVertice, Vertice *vertice, Vertice **pVertice);

bool buscaAresta(int chaveVertice, int chaveAresta, Vertice *vertice, Aresta **pAresta);

bool insereVertice(Vertice **pVertice, int chaveVertice);

bool insereAresta(Vertice *vertice, int chaveVertice, int chaveAresta);

bool removeAresta(Vertice *vertice, int chaveVertice, int chaveAresta);

Vertice* removeVertice(Vertice* vertice, int chaveVertice);

void visualiza(Vertice *vertice);

#endif //GRAFOL_GRAFO_H
