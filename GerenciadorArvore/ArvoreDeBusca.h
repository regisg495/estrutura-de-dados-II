//
// Created by regis on 08/04/2020.
//

#ifndef GERENCIADORARVORE_ARVOREDEBUSCA_H
#define GERENCIADORARVORE_ARVOREDEBUSCA_H

#include <iostream>
#include "ArvoreAVL.h"

using namespace std;

template<class T>
class NodoBusca;

template<class T>
class ArvoreDeBusca;

template<class T>
class NodoBusca {

    friend class ArvoreDeBusca<T>;

public:

    T chave;
    NodoBusca<T> *esq;
    NodoBusca<T> *dir;

    explicit NodoBusca(T chave = T(), NodoBusca<T> *esq = nullptr, NodoBusca<T> *dir = nullptr);

    virtual ~NodoBusca();

};

template<class T>
NodoBusca<T>::NodoBusca(T chave, NodoBusca<T> *esq, NodoBusca<T> *dir) {
    this->chave = chave;
    this->esq = esq;
    this->dir = dir;
}

template<class T>
NodoBusca<T>::~NodoBusca() {
    if (esq) delete (esq);
    if (dir) delete (dir);
}

template<class T>
class ArvoreDeBusca {

public:

    bool busca(T chave, NodoBusca<T> **result, int &numChamadas);

    ArvoreDeBusca() : raiz(nullptr) {}

    virtual ~ArvoreDeBusca();

    ArvoreDeBusca(const ArvoreDeBusca<T> &rhs) : raiz(nullptr) { *this = rhs; }

    int getAltura();

    bool buscaAnterior(T chave, NodoBusca<T> **result);

    bool remove(T chave);

    void printEmPosOrdem();

    void printEmPreOrdem();

    void printEmOrdem();

    bool insere(T chave);

    ArvoreAVL<T> *toAVL();

    NodoBusca<T> *getRaiz() const;

    unsigned int getSize() const;

private:

    NodoBusca<T> *raiz;

    unsigned int size{0};

    bool insere(NodoBusca<T> **pNodoBusca, T chave);

    bool busca(NodoBusca<T> *nodoBusca, T chave, NodoBusca<T> **result, int &numChamadas);

    bool remove(NodoBusca<T> **pNodoBusca, T chave);

    int alturaRec(NodoBusca<T> *nodoBusca);

    bool buscaAnterior(NodoBusca<T> *nodoBusca, T chave, NodoBusca<T> **result);

    void printEmPosOrdem(NodoBusca<T> *nodoBusca);

    void printEmPreOrdem(NodoBusca<T> *nodoBusca);

    void printEmOrdem(NodoBusca<T> *nodoBusca);

    ArvoreAVL<T> *toAVL(NodoBusca<T> *nodoBusca, ArvoreAVL<T> *arvoreAvl);

};

template<class T>
NodoBusca<T> *ArvoreDeBusca<T>::getRaiz() const {
    return raiz;
}

template<class T>
unsigned int ArvoreDeBusca<T>::getSize() const {
    return size;
}

template<class T>
bool ArvoreDeBusca<T>::insere(NodoBusca<T> **pNodoBusca, T chave) {
    NodoBusca<T> **temp = pNodoBusca;

    while (*temp != nullptr) {
        if (chave < (*temp)->chave)
            temp = &(*temp)->esq;
        else if (chave > (*temp)->chave)
            temp = &(*temp)->dir;
        else return false;
    }

    *temp = new NodoBusca<T>(chave);
    return true;
}

template<class T>
bool ArvoreDeBusca<T>::remove(NodoBusca<T> **pNodoBusca, T chave) {
    if ((*pNodoBusca)->chave == chave) {
        delete (*pNodoBusca);
        *pNodoBusca = nullptr;
        return true;
    }

    NodoBusca<T> *toDeleteChildrens;

    if (!buscaAnterior((*pNodoBusca), chave, &toDeleteChildrens)) {
        return false;
    } else {
        if (toDeleteChildrens->esq != nullptr && toDeleteChildrens->esq->chave == chave) {
            delete (toDeleteChildrens->esq);
            toDeleteChildrens->esq = nullptr;
        }
        if (toDeleteChildrens->dir != nullptr && toDeleteChildrens->dir->chave == chave) {
            delete (toDeleteChildrens->dir);
            toDeleteChildrens->dir = nullptr;
        }
        return true;
    }
}

template<class T>
void ArvoreDeBusca<T>::printEmPosOrdem(NodoBusca<T> *nodoBusca) {
    if (nodoBusca != nullptr) {
        printEmPosOrdem(nodoBusca->esq);
        printEmPosOrdem(nodoBusca->dir);
        std::cout << nodoBusca->chave << std::endl;
    }
}

template<class T>
void ArvoreDeBusca<T>::printEmPreOrdem(NodoBusca<T> *nodoBusca) {
    if (nodoBusca != nullptr) {
        std::cout << nodoBusca->chave << std::endl;
        printEmPreOrdem(nodoBusca->esq);
        printEmPreOrdem(nodoBusca->dir);
    }

}

template<class T>
void ArvoreDeBusca<T>::printEmOrdem(NodoBusca<T> *nodoBusca) {
    if (nodoBusca != nullptr) {
        printEmOrdem(nodoBusca->esq);
        std::cout << nodoBusca->chave << std::endl;
        printEmOrdem(nodoBusca->dir);
    }
}

template<class T>
void ArvoreDeBusca<T>::printEmPosOrdem() {
    return printEmPosOrdem(raiz);
}

template<class T>
void ArvoreDeBusca<T>::printEmPreOrdem() {
    return printEmPreOrdem(raiz);
}

template<class T>
void ArvoreDeBusca<T>::printEmOrdem() {
    return printEmOrdem(raiz);
}

template<class T>
bool ArvoreDeBusca<T>::busca(NodoBusca<T> *nodoBusca, T chave, NodoBusca<T> **result, int &numChamadas) {

    NodoBusca<T> *temp = nodoBusca;

    while (temp != nullptr) {
        numChamadas++;
        if (chave < temp->chave) {
            temp = temp->esq;
        } else if (chave > temp->chave) {
            temp = temp->dir;
        } else {
            *result = temp;
            return true;
        }
    }
    return false;
}

template<class T>
bool ArvoreDeBusca<T>::buscaAnterior(T chave, NodoBusca<T> **result) {
    return buscaAnterior(raiz, chave, result);
}

template<class T>
bool ArvoreDeBusca<T>::busca(T chave, NodoBusca<T> **result, int &numChamadas) {
    return busca(raiz, chave, result, numChamadas);
}

template<class T>
bool ArvoreDeBusca<T>::buscaAnterior(NodoBusca<T> *nodoBusca, T chave, NodoBusca<T> **result) {
    NodoBusca<T> *temp = nodoBusca;

    while (temp != nullptr) {
        if (temp->dir != nullptr && temp->dir->chave == chave) {
            *result = temp;
            return true;
        }
        if (temp->esq != nullptr && temp->esq->chave == chave) {
            *result = temp;
            return true;
        }

        if (chave < temp->chave)
            temp = temp->esq;
        else temp = temp->dir;

    }
    return false;
}

template<class T>
bool ArvoreDeBusca<T>::remove(T chave) {
    if (remove(&raiz, chave)) {
        size--;
        return true;
    } else {
        return false;
    }
}

template<class T>
bool ArvoreDeBusca<T>::insere(T chave) {
    if (insere(&raiz, chave)) {
        size++;
        return true;
    } else {
        return false;
    }
}

template<class T>
ArvoreAVL<T> *ArvoreDeBusca<T>::toAVL(NodoBusca<T> *nodoBusca, ArvoreAVL<T> *arvoreAvl) {
    if (nodoBusca != nullptr) {
        arvoreAvl->insere(nodoBusca->chave);
        toAVL(nodoBusca->esq, arvoreAvl);
        toAVL(nodoBusca->dir, arvoreAvl);
    }
    return arvoreAvl;
}

template<class T>
ArvoreAVL<T> *ArvoreDeBusca<T>::toAVL() {
    return toAVL(raiz, new ArvoreAVL<T>(nullptr));
}

template<class T>
int ArvoreDeBusca<T>::alturaRec(NodoBusca<T> *nodoBusca) {
    if (nodoBusca == nullptr) {
        return 0;
    } else {
        int alturaEsq = alturaRec(nodoBusca->esq);
        int alturaDir = alturaRec(nodoBusca->dir);
        if (alturaDir >= alturaEsq) return 1 + alturaDir;
        else return 1 + alturaEsq;
    }
}

template<class T>
int ArvoreDeBusca<T>::getAltura() {
    return alturaRec(raiz);
}

template<class T>
ArvoreDeBusca<T>::~ArvoreDeBusca() {
    if (raiz) delete (raiz);
    raiz = nullptr;
}

#endif //GERENCIADORARVORE_ARVOREDEBUSCA_H