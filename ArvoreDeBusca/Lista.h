//
// Created by regis on 29/03/2020.
//

#ifndef LISTAENCADEADAOBJECT_LISTA_H
#define LISTAENCADEADAOBJECT_LISTA_H

#include <iostream>

using namespace std;

struct NodoLista {
    int val;
    NodoLista *prox;

    ~NodoLista();

};

class Lista {

private:

    unsigned int count;
    NodoLista *inicio;

    static bool novoNodo(int val, NodoLista **pNodoLista);

public:

    Lista();

    virtual ~Lista();

    unsigned int getCount() const;

    NodoLista *getInicio() const;

    bool operator==(const Lista &rhs) const;

    bool operator!=(const Lista &rhs) const;

    bool vazia();

    bool insereNoInicio(int val);

    void mergeNoInicio(NodoLista *nodoLista);

    bool insereNoFim(int val);

    void mergeNoFim(NodoLista *nodoLista);

    void print();

    bool contem(int val);

    unsigned int iguaisNaPropriaLista();

};


#endif //LISTAENCADEADAOBJECT_LISTA_H
