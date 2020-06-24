//
// Created by regis on 29/03/2020.
//

#ifndef LISTAENCADEADAOBJECT_ARVORE_H
#define LISTAENCADEADAOBJECT_ARVORE_H

#include <bits/stdc++.h>

#include "Lista.h"

struct NodoArvore {

    NodoArvore *dir;
    NodoArvore *esq;
    Lista *lista;

    ~NodoArvore();

};

class ArvoreDeBusca {

private:

    NodoArvore *raiz;

    static bool novoNodoArvore(Lista *lista, NodoArvore **result);

    static bool insere(NodoArvore **nodoArvore, Lista *lista);

    static bool remove(NodoArvore **nodoArvore, unsigned int count);

    static bool vazia(NodoArvore *nodoArvore);

    static unsigned int count(NodoArvore *nodoArvore);

    static unsigned int menor(NodoArvore *nodoArvore);

    static unsigned int maximo(NodoArvore *nodoArvore);

    static void getListas(NodoArvore *nodoArvore, Lista **result);

    static bool buscaRec(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result);

    static bool busca(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result);

    static bool buscaAnteriorRec(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result);

    static bool buscaAnterior(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result);

    static void printEmOrdem(NodoArvore *nodoArvore);

    static void printEmPosOrdem(NodoArvore *nodoArvore);

    static void printEmPreOrdem(NodoArvore *nodoArvore);

public:

    ArvoreDeBusca();

    ~ArvoreDeBusca();

    explicit ArvoreDeBusca(NodoArvore *nodoArvore);

    bool vazia();

    unsigned int count();

    unsigned int menor();

    unsigned int maximo();

    unsigned int repetidos();

    bool insere(Lista *lista);

    bool remove(unsigned int count);

    bool buscaRec(unsigned int count, NodoArvore **result);

    bool busca(Lista *lista, NodoArvore **result);

    bool busca(unsigned int count, NodoArvore **result);

    bool buscaAnteriorRec(unsigned int count, NodoArvore **result);

    bool buscaAnterior(unsigned int count, NodoArvore **result);

    void printEmOrdem();

    void printEmPosOrdem();

    void printEmPreOrdem();

};


#endif //LISTAENCADEADAOBJECT_ARVORE_H
