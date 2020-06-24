//
// Created by regis on 09/05/2020.
//

#include "Grafo.h"

bool criaAresta(int chaveAresta, Aresta **pAresta) {
    Aresta *temp = (Aresta *) malloc(sizeof(Aresta));

    if (!temp) return false;

    temp->prox = NULL;
    temp->ant = NULL;
    temp->chaveAresta = chaveAresta;

    *pAresta = temp;

    return true;

}

bool criaVertice(int chaveVertice, Vertice **pVertice) {
    Vertice *temp = (Vertice *) malloc(sizeof(Vertice));

    if (!temp) return false;

    temp->chaveVertice = chaveVertice;
    temp->prox = NULL;
    temp->inicio = NULL;
    temp->numArestas = 0;

    *pVertice = temp;

    return true;
}

bool inicializaGrafo(Grafo **pGrafo) {
    Grafo *temp = (Grafo *) malloc(sizeof(Grafo));

    if (!temp) return false;

    temp->inicio = NULL;
    temp->numVertices = 0;

    *pGrafo = temp;

    return true;
}

bool buscaVertice(Grafo *grafo, int chaveVertice, Vertice **pVertice) {
    if (grafo == NULL) return false;

    for (Vertice *temp = grafo->inicio; temp != NULL; temp = temp->prox) {
        if (temp->chaveVertice == chaveVertice) {
            *pVertice = temp;
            return true;
        }
    }
    return false;
}

bool buscaAresta(Grafo *grafo, int chaveVertice, int chaveAresta, Aresta **pAresta) {
    if (grafo == NULL) return false;

    Vertice *temp;
    if (buscaVertice(grafo, chaveVertice, &temp)) {
        for (Aresta *aux = temp->inicio; aux != NULL; aux = aux->prox) {
            if (aux->chaveAresta == chaveAresta) {
                *pAresta = aux;
                return true;
            }
        }
    } else {
        return false;
    }
}


bool insereVertice(Grafo *grafo, int chaveVertice) {
    if (grafo == NULL) return false;

    Vertice *temp;

    if (!buscaVertice(grafo, chaveVertice, &temp)) {

        if (!criaVertice(chaveVertice, &temp)) {
            return false;
        } else {

            temp->prox = grafo->inicio;
            grafo->inicio = temp;
            grafo->numVertices++;
            return true;
        }

    } else {
        return false;
    }
}

bool insereAresta(Grafo *grafo, int chaveVertice, int chaveAresta) {
    if (grafo == NULL) return false;

    Vertice *temp;

    if (!buscaVertice(grafo, chaveVertice, &temp)) {
        return false;
    } else {
        Aresta *aresta;

        if (!criaAresta(chaveAresta, &aresta) || buscaAresta(grafo, chaveVertice, chaveAresta, &aresta)) {
            return false;
        } else {

            if (temp->numArestas == 0) {
                temp->inicio = aresta;
                temp->numArestas++;
                return true;
            } else {
                temp->inicio->ant = aresta;
                aresta->prox = temp->inicio;
                temp->inicio = aresta;
                temp->numArestas++;
                return true;
            }

        }
    }
}

void visualiza(Grafo *grafo) {
    if (grafo != NULL) {
        for (Vertice *temp = grafo->inicio; temp != NULL; temp = temp->prox) {
            printf("\nArestas no Vértice %d: (%d)", temp->chaveVertice, temp->numArestas);
            for (Aresta *aux = temp->inicio; aux != NULL; aux = aux->prox)
                printf(" [%d]", aux->chaveAresta);
        }
    }
}

bool removeAresta(Grafo *grafo, int chaveVertice, int chaveAresta) {
    if (grafo == NULL) return false;

    Vertice *vertice;

    if (!buscaVertice(grafo, chaveVertice, &vertice)) return false;

    Aresta *temp;

    if (buscaAresta(grafo, chaveVertice, chaveAresta, &temp)) {

        if (temp->ant != NULL && temp->prox != NULL) {
            temp->ant->prox = temp->prox;
            temp->prox->ant = temp->ant;
            free(temp);
            temp = NULL;
            vertice->numArestas--;
            return true;
        } else if (temp->ant != NULL && temp->prox == NULL) {
            temp->ant->prox = NULL;
            free(temp);
            temp = NULL;
            vertice->numArestas--;
            return true;
        } else if (temp->ant == NULL && temp->prox != NULL) {
            temp = vertice->inicio->prox;
            free(vertice->inicio);
            temp->ant = NULL;
            vertice->inicio = temp;
            vertice->numArestas--;
            return true;
        } else {
            free(temp);
            temp = NULL;
            vertice->numArestas--;
            return true;
        }

    } else {
        return false;
    }
}

bool removeVertice(Grafo *grafo, int chaveVertice) {
    if (grafo == NULL) return false;

    Vertice *temp = grafo->inicio;
    Vertice *aux = NULL;

    while (temp != NULL && temp->chaveVertice != chaveVertice) {
        aux = temp;
        temp = temp->prox;
    }

    if (temp != NULL) {
        if (temp->numArestas > 0) {
            while (temp->numArestas != 0) {
                if (!removeAresta(grafo, temp->chaveVertice, temp->inicio->chaveAresta)) EXIT_FAILURE;
            }
            temp->inicio = NULL;
        }

        if (aux == NULL) grafo->inicio = grafo->inicio->prox;
        else aux->prox = temp->prox;

        free(temp);
        grafo->numVertices--;

        return true;

    } else {
        return false;
    }

}

void deletaGrafo(Grafo **pGrafo) {

    if ((*pGrafo) != NULL) {

        Grafo *grafo = *pGrafo;

        for (Vertice *temp = grafo->inicio; temp != NULL; temp = temp->prox)
            if (!removeVertice(grafo, temp->chaveVertice)) EXIT_FAILURE;

        grafo->inicio = NULL;

        free(grafo);

        *pGrafo = NULL;
    }

}
