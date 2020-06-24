//
// Created by regis on 29/03/2020.
//

#include <windef.h>
#include "Lista.h"

Lista::Lista() {
    inicio = nullptr;
    count = 0;
}

Lista::~Lista() {
    delete (inicio);
    inicio = nullptr;
}

NodoLista::~NodoLista() {
    if (prox) delete (prox);
}

bool Lista::novoNodo(int val, NodoLista **pNodoLista) {
    NodoLista *temp;
    temp = (NodoLista *) malloc(sizeof(NodoLista));
    if (!temp) return false;
    temp->val = val;
    temp->prox = nullptr;
    *pNodoLista = temp;
    return true;
}

unsigned int Lista::getCount() const {
    return count;
}

NodoLista *Lista::getInicio() const {
    return inicio;
}

bool Lista::operator==(const Lista &rhs) const {
    return count == rhs.count &&
           inicio == rhs.inicio;
}

bool Lista::operator!=(const Lista &rhs) const {
    return !(rhs == *this);
}

bool Lista::vazia() {
    return inicio == nullptr;
}

bool Lista::insereNoInicio(int val) {
    if (vazia()) {
        if (!novoNodo(val, &inicio)) return false;
        count++;
        return true;
    } else {
        NodoLista *nodoLista;
        if (!novoNodo(val, &nodoLista)) return false;
        nodoLista->prox = inicio;
        inicio = nodoLista;
        count++;
        return true;
    }
}

void Lista::mergeNoInicio(NodoLista *nodoLista) {
    if (nodoLista == nullptr) return;

    NodoLista *temp = nodoLista;
    while (temp != nullptr) {
        if (!insereNoInicio(temp->val)) return;
        temp = temp->prox;
    }
}

void Lista::print() {
    if (vazia()) return;

    cout << count << " (";
    for (NodoLista *nodoLista = inicio; nodoLista != nullptr; nodoLista = nodoLista->prox) {
        cout << nodoLista->val;
        if (nodoLista->prox != nullptr) cout << ", ";
    }
    cout << ")" << endl;
}

bool Lista::contem(int val) {
    if (!vazia()) {
        for (NodoLista *nodoLista = inicio; nodoLista != nullptr; nodoLista = nodoLista->prox) {
            if (nodoLista->val == val) return true;
        }
    }
    return false;
}

unsigned int Lista::iguaisNaPropriaLista() {
    if (vazia() || inicio->prox == nullptr) return 0;
    NodoLista *cur = inicio;
    NodoLista *temp;
    unsigned int rep = 0;
    while (cur->prox != nullptr) {
        temp = cur->prox;
        while (temp != nullptr) {
            if (cur->val == temp->val) {
                rep++;
                break;
            }
            temp = temp->prox;
        }
        cur = cur->prox;
    }
    return rep;
}

bool Lista::insereNoFim(int val) {
    if (vazia()) return insereNoInicio(val);

    NodoLista *temp = inicio;
    while (temp->prox != nullptr) {
        temp = temp->prox;
    }
    NodoLista *aux;
    if (!novoNodo(val, &aux)) return false;
    temp->prox = aux;
    count++;
    return true;
}

void Lista::mergeNoFim(NodoLista *nodoLista) {
    if (nodoLista == nullptr) return;

    NodoLista *temp = nodoLista;
    while (temp != nullptr) {
        if (!insereNoFim(temp->val)) return;
        temp = temp->prox;
    }

}