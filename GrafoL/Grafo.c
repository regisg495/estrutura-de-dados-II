//
// Created by regis on 08/05/2020.
//

#include "Grafo.h"


Vertice *inicializa() {
    return NULL;
}

bool criaAresta(int chaveAresta, Aresta *prox, Aresta **pAresta) {
    Aresta *aresta = (Aresta *) malloc(sizeof(Aresta));

    if (!aresta) return false;

    aresta->chaveAresta = chaveAresta;
    aresta->prox = prox;

    *pAresta = aresta;

    return true;
}

bool criaVertice(int chaveVertice, Vertice *prox, Vertice **pVertice) {
    Vertice *temp;
    temp = (Vertice *) malloc(sizeof(Vertice));

    if (!temp) return false;

    temp->chaveVertice = chaveVertice;
    temp->prox = prox;
    temp->inicio = NULL;

    *pVertice = temp;

    return true;
}

bool buscaVertice(int chaveVertice, Vertice *vertice, Vertice **pVertice) {

    for (Vertice *temp = vertice; temp != NULL; temp = temp->prox)
        if (temp->chaveVertice == chaveVertice) {
            *pVertice = temp;
            return true;
        }

    return false;
}

bool buscaAresta(int chaveVertice, int chaveAresta, Vertice *vertice, Aresta **pAresta) {
    Vertice *verticeInicio;

    if (!buscaVertice(chaveVertice, vertice, &verticeInicio)) {
        printf("\nCaiu aqui");
        return false;

    } else {

        for (Aresta *temp = verticeInicio->inicio; temp != NULL; temp = temp->prox)
            if (temp->chaveAresta == chaveAresta) {
                *pAresta = temp;
                return true;
            }

        return false;
    }

}

bool insereVertice(Vertice **pVertice, int chaveVertice) {
    Vertice *temp;

    if (!buscaVertice(chaveVertice, *pVertice, &temp)) {

        if (criaVertice(chaveVertice, *pVertice, &temp)) {
            *pVertice = temp;
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }

}

bool insereAresta(Vertice *vertice, int chaveVertice, int chaveAresta) {
    Vertice *temp;

    if (!buscaVertice(chaveVertice, vertice, &temp)) {
        return false;
    } else {

        Aresta *nodo = NULL;

        if (!criaAresta(chaveAresta, temp->inicio, &nodo)) return false;
        else temp->inicio = nodo;
    }
}

void visualiza(Vertice *vertice) {

    for (Vertice *temp = vertice; temp != NULL; temp = temp->prox) {
        printf("\nVertice: %d\nAresta:", temp->chaveVertice);
        for (Aresta *aux = temp->inicio; aux != NULL; aux = aux->prox)
            printf(" [%d]", aux->chaveAresta);
        printf("\n");
    }
}

bool removeAresta(Vertice *vertice, int chaveVertice, int chaveAresta) {
    Vertice *temp;

    if (buscaVertice(chaveVertice, vertice, &temp)) {

        Aresta *anterior = NULL;
        Aresta *atual = temp->inicio;
        Aresta *aux;

        if (!buscaAresta(chaveVertice, chaveAresta, vertice, &aux)) return false;

        while ((atual) && (atual->chaveAresta != chaveAresta)) {
            anterior = atual;
            atual = atual->prox;
        }

        if (anterior == NULL) temp->inicio = atual->prox;
        else anterior->prox = atual->prox;

        free(atual);
    }
}

Vertice *removeVertice(Vertice *vertice, int chaveVertice) {
    Vertice *atual = vertice;
    Vertice *anterior = NULL;
    Vertice *aux;

    if (!buscaVertice(chaveVertice, vertice, &aux)) return false;

    while ((atual) && (atual->chaveVertice) != chaveVertice) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        while (atual->inicio != NULL) removeAresta(vertice, chaveVertice, atual->inicio->chaveAresta);

        if (anterior == NULL) vertice = vertice->prox;
        else anterior->prox = atual->prox;

        free(atual);
    }

    return vertice;

}
