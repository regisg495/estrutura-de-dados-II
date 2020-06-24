//
// Created by regis on 09/05/2020.
//

#ifndef GRAFOLISTAADJACENTE_GRAFO_H
#define GRAFOLISTAADJACENTE_GRAFO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Aresta {
    int chaveAresta;
    struct Aresta *prox;
    struct Aresta *ant;
} Aresta;

typedef struct Vertice {
    int chaveVertice;
    Aresta *inicio;
    struct Vertice *prox;
    size_t numArestas;
} Vertice;

typedef struct Grafo {
    Vertice *inicio;
    size_t numVertices;
} Grafo;

bool criaAresta(int chaveAresta, Aresta **pAresta);

bool criaVertice(int chaveVertice, Vertice **pVertice);

bool inicializaGrafo(Grafo **pGrafo);

bool buscaVertice(Grafo *grafo, int chaveVertice, Vertice **pVertice);

bool buscaVerticeEmLargura(Grafo *grafo, Vertice *vertice);

bool buscaAresta(Grafo *grafo, int chaveVertice, int chaveAresta, Aresta **pAresta);

bool insereVertice(Grafo *grafo, int chaveVertice);

bool insereAresta(Grafo *grafo, int chaveVertice, int chaveAresta);

bool removeAresta(Grafo *grafo, int chaveVertice, int chaveAresta);

bool removeVertice(Grafo *grafo, int chaveVertice);

void deletaGrafo(Grafo **pGrafo);

void visualiza(Grafo *grafo);

#endif //GRAFOLISTAADJACENTE_GRAFO_H
