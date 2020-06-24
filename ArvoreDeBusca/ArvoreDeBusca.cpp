//
// Created by regis on 29/03/2020.
//

#include "ArvoreDeBusca.h"

ArvoreDeBusca::ArvoreDeBusca() {
    raiz = nullptr;
}

ArvoreDeBusca::ArvoreDeBusca(NodoArvore *nodoArvore) {
    raiz = nodoArvore;
}

ArvoreDeBusca::~ArvoreDeBusca() {
    if (raiz) delete (raiz);
    raiz = nullptr;
}

NodoArvore::~NodoArvore() {
    delete (lista);
    if (esq) delete (esq);
    if (dir) delete (dir);
}

bool ArvoreDeBusca::novoNodoArvore(Lista *lista, NodoArvore **pNodoArvore) {
    if (lista == nullptr) return false;

    NodoArvore *temp;
    temp = (NodoArvore *) malloc(sizeof(NodoArvore));

    if (!temp) return false;

    temp->lista = new Lista();

    temp->lista = lista;
    temp->dir = nullptr;
    temp->esq = nullptr;

    *pNodoArvore = temp;

    return true;
}

bool ArvoreDeBusca::insere(NodoArvore **nodoArvore, Lista *lista) {
    NodoArvore *insert;
    if (!novoNodoArvore(lista, &insert)) return false;
    NodoArvore **temp = nodoArvore;

    while (*temp != nullptr) {
        if (insert->lista->getCount() < (*temp)->lista->getCount())
            temp = &(*temp)->esq;
        else if (insert->lista->getCount() > (*temp)->lista->getCount())
            temp = &(*temp)->dir;
        else return false;
    }

    *temp = insert;
    return true;
}

bool ArvoreDeBusca::remove(NodoArvore **nodoArvore, unsigned int count) {

    if ((*nodoArvore)->lista->getCount() == count) {
        delete (*nodoArvore);
        *nodoArvore = nullptr;
        return true;
    }

    NodoArvore *toDeleteChildrens;

    if (!buscaAnterior((*nodoArvore), count, &toDeleteChildrens)) {
        return false;
    } else {
        if (toDeleteChildrens->esq != nullptr && toDeleteChildrens->esq->lista->getCount() == count) {
            delete (toDeleteChildrens->esq);
            toDeleteChildrens->esq = nullptr;
        }
        if (toDeleteChildrens->dir != nullptr && toDeleteChildrens->dir->lista->getCount() == count) {
            delete (toDeleteChildrens->dir);
            toDeleteChildrens->dir = nullptr;
        }
        return true;
    }

}

bool ArvoreDeBusca::remove(unsigned int count) {
    return remove(&raiz, count);
}

bool ArvoreDeBusca::vazia() {
    return vazia(raiz);
}

bool ArvoreDeBusca::vazia(NodoArvore *nodoArvore) {
    return nodoArvore == nullptr;
}

unsigned int ArvoreDeBusca::menor(NodoArvore *nodoArvore) {
    if (nodoArvore == nullptr) return INT_MAX;

    unsigned int count = nodoArvore->lista->getCount();
    unsigned int countEsq = menor(nodoArvore->esq);
    unsigned int countDir = menor(nodoArvore->dir);

    if (count > countEsq)
        count = countEsq;
    if (count > countDir)
        count = countDir;

    return count;
}

unsigned int ArvoreDeBusca::maximo(NodoArvore *nodoArvore) {
    if (nodoArvore == nullptr) return INT_MIN;

    unsigned int count = nodoArvore->lista->getCount();
    unsigned int countEsq = maximo(nodoArvore->esq);
    unsigned int countDir = maximo(nodoArvore->dir);

    if (countEsq > count)
        count = countEsq;
    if (countDir > count)
        count = countDir;

    return count;
}


unsigned int ArvoreDeBusca::maximo() {
    return maximo(raiz);
}

unsigned int ArvoreDeBusca::menor() {
    return menor(raiz);
}

unsigned int ArvoreDeBusca::count(NodoArvore *nodoArvore) {
    if (nodoArvore == nullptr) return 0;
    return 1 + count(nodoArvore->esq) + count(nodoArvore->dir);
}

unsigned int ArvoreDeBusca::count() {
    return count(raiz);
}

void ArvoreDeBusca::getListas(NodoArvore *nodoArvore, Lista **result) {
    if (!vazia(nodoArvore)) {
        (*result)->mergeNoInicio(nodoArvore->lista->getInicio());
        getListas(nodoArvore->esq, result);
        getListas(nodoArvore->dir, result);
    }
}

unsigned int ArvoreDeBusca::repetidos() {
    if (raiz == nullptr || raiz->lista == nullptr) return 0;
    auto *lista = new Lista();
    getListas(raiz, &lista);
    unsigned int iguais = 0;

    if (lista != nullptr) iguais = lista->iguaisNaPropriaLista();

    delete (lista);
    return iguais;
}

bool ArvoreDeBusca::insere(Lista *lista) {
    if (lista == nullptr || lista->vazia()) return false;
    return insere(&raiz, lista);
}

bool ArvoreDeBusca::busca(Lista *lista, NodoArvore **result) {
    if (lista == nullptr || lista->getCount() == 0) return false;
    else return busca(raiz, lista->getCount(), result);
}

bool ArvoreDeBusca::busca(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result) {

    NodoArvore *temp = nodoArvore;

    while (temp != nullptr) {

        if (count < temp->lista->getCount()) {
            temp = temp->esq;
        } else if (count > temp->lista->getCount()) {
            temp = temp->dir;
        } else {
            *result = temp;
            return true;
        }
    }
    return false;

}

bool ArvoreDeBusca::buscaAnterior(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result) {

    NodoArvore *temp = nodoArvore;

    while (temp != nullptr) {
        if (temp->dir != nullptr && temp->dir->lista->getCount() == count) {
            *result = temp;
            return true;
        }
        if (temp->esq != nullptr && temp->esq->lista->getCount() == count) {
            *result = temp;
            return true;
        }

        if (count < temp->lista->getCount())
            temp = temp->esq;
        else temp = temp->dir;

    }

    return false;

}

bool ArvoreDeBusca::buscaAnterior(unsigned int count, NodoArvore **result) {
    return buscaAnterior(raiz, count, result);
}

bool ArvoreDeBusca::busca(unsigned int count, NodoArvore **result) {
    return busca(raiz, count, result);
}

void ArvoreDeBusca::printEmOrdem() {
    printEmOrdem(raiz);
}

void ArvoreDeBusca::printEmOrdem(NodoArvore *nodoArvore) {
    if (nodoArvore != nullptr) {
        printEmOrdem(nodoArvore->esq);
        nodoArvore->lista->print();
        printEmOrdem(nodoArvore->dir);
    }
}

void ArvoreDeBusca::printEmPosOrdem(NodoArvore *nodoArvore) {
    if (nodoArvore != nullptr) {
        printEmPosOrdem(nodoArvore->esq);
        printEmPosOrdem(nodoArvore->dir);
        nodoArvore->lista->print();
    }
}

void ArvoreDeBusca::printEmPosOrdem() {
    printEmPosOrdem(raiz);
}

void ArvoreDeBusca::printEmPreOrdem(NodoArvore *nodoArvore) {
    if (nodoArvore != nullptr) {
        nodoArvore->lista->print();
        printEmPreOrdem(nodoArvore->esq);
        printEmPreOrdem(nodoArvore->dir);
    }
}

void ArvoreDeBusca::printEmPreOrdem() {
    printEmPreOrdem(raiz);
}

bool ArvoreDeBusca::buscaRec(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result) {
    if (nodoArvore == nullptr) return false;
    if (nodoArvore->lista->getCount() == count) {
        *result = nodoArvore;
        return true;
    }

    if (count < nodoArvore->lista->getCount()) return buscaRec(nodoArvore->esq, count, result);
    else return buscaRec(nodoArvore->dir, count, result);
}

bool ArvoreDeBusca::buscaRec(unsigned int count, NodoArvore **result) {
    return buscaRec(raiz, count, result);
}

bool ArvoreDeBusca::buscaAnteriorRec(NodoArvore *nodoArvore, unsigned int count, NodoArvore **result) {
    if (nodoArvore == nullptr) return false;
    if (nodoArvore->dir != nullptr && nodoArvore->dir->lista->getCount() == count) {
        *result = nodoArvore;
        return true;
    } else if (nodoArvore->esq != nullptr && nodoArvore->esq->lista->getCount() == count) {
        *result = nodoArvore;
        return true;
    }

    if (count < nodoArvore->lista->getCount()) return buscaAnteriorRec(nodoArvore->esq, count, result);
    else return buscaAnteriorRec(nodoArvore->dir, count, result);
}

bool ArvoreDeBusca::buscaAnteriorRec(unsigned int count, NodoArvore **result) {
    return buscaAnteriorRec(raiz, count, result);
}



