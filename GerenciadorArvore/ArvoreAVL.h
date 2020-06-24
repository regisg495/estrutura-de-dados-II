//
// Created by regis on 10/04/2020.
//

#ifndef GERENCIADORARVORE_ARVOREAVL_H
#define GERENCIADORARVORE_ARVOREAVL_H

#include <iostream>

using namespace std;

template<class T>
class NodoAVL;

template<class T>
class ArvoreAVL;

template<class T>
class NodoAVL {

    friend class ArvoreAVL<T>;

public:

    T chave;
    int altura{1};
    NodoAVL<T> *esq;
    NodoAVL<T> *dir;

public:

    explicit NodoAVL(T chave = T(), NodoAVL<T> *esq = nullptr, NodoAVL<T> *dir = nullptr);

    virtual ~NodoAVL();

};

template<class T>
NodoAVL<T>::NodoAVL(T chave, NodoAVL<T> *esq, NodoAVL<T> *dir) {
    this->chave = chave;
    this->esq = esq;
    this->dir = dir;
    this->altura = 1;
}

template<class T>
NodoAVL<T>::~NodoAVL() {
    if (esq) delete (esq);
    if (dir) delete (dir);
}

template<class T>
class ArvoreAVL {

public:

    ArvoreAVL() : raiz(nullptr) {}

    explicit ArvoreAVL(NodoAVL<T> *r) : raiz(r) {}

    virtual ~ArvoreAVL();

    ArvoreAVL(const ArvoreAVL<T> &rhs) : raiz(nullptr) { *this = rhs; }

    int alturaReal(NodoAVL<T> *nodoAvl);

    int getAltura(NodoAVL<T> *nodoAvl);

    int getAltura();

    bool insere(T chave);

    void printEmPreOrdem();

    void estatisticas();

    bool busca(T chave, NodoAVL<T> **result, int &numChamadas);

    bool buscaAnterior(T chave, NodoAVL<T> **result);

    bool remove(T chave);

    void printEmOrdem();

    void printEmPosOrdem();

    NodoAVL<T> *getRaiz() const;

    unsigned int getSize() const;

private:

    NodoAVL<T> *raiz;
    unsigned int size{0};

    void estatisticas(NodoAVL<T> *nodoAvl);

    NodoAVL<T> *insere(NodoAVL<T> *nodoAvl, T chave);

    bool busca(NodoAVL<T> *nodoAvl, T chave, NodoAVL<T> **result, int &numChamadas);

    bool remove(NodoAVL<T> **pNodoAvl, T chave);

    bool buscaAnterior(NodoAVL<T> *nodoAvl, T chave, NodoAVL<T> **result);

    int recalculaAltura(NodoAVL<T> *nodoAvl);

    NodoAVL<T> *rotacionaDir(NodoAVL<T> *nodoAvl);

    NodoAVL<T> *rotacionaEsq(NodoAVL<T> *nodoAvl);

    NodoAVL<T> *balanceia(NodoAVL<T> *nodoAvl);

    void printEmOrdem(NodoAVL<T> *nodoAvl);

    void printEmPosOrdem(NodoAVL<T> *nodoAvl);

    void printEmPreOrdem(NodoAVL<T> *nodoAvl);

};

template<class T>
NodoAVL<T> *ArvoreAVL<T>::getRaiz() const {
    return raiz;
}

template<class T>
unsigned int ArvoreAVL<T>::getSize() const {
    return size;
}

template<class T>
int ArvoreAVL<T>::alturaReal(NodoAVL<T> *nodoAvl) {
    if (nodoAvl == nullptr) {
        return 0;
    } else {
        int alturaEsq = alturaReal(nodoAvl->esq);
        int alturaDir = alturaReal(nodoAvl->dir);
        if (alturaDir >= alturaEsq) return 1 + alturaDir;
        else return 1 + alturaEsq;
    }
}

template<class T>
int ArvoreAVL<T>::getAltura(NodoAVL<T> *nodoAvl) {
    if (nodoAvl == nullptr) return 0;
    else return nodoAvl->altura;
}

template<class T>
int ArvoreAVL<T>::recalculaAltura(NodoAVL<T> *nodoAvl) {
    if (nodoAvl == nullptr) return 0;
    int alturaEsq = getAltura(nodoAvl->esq);
    int alturaDir = getAltura(nodoAvl->dir);
    if (alturaDir >= alturaEsq) return 1 + alturaDir;
    else return 1 + alturaEsq;
}

template<class T>
NodoAVL<T> *ArvoreAVL<T>::rotacionaDir(NodoAVL<T> *nodoAvl) {
    if (nodoAvl == nullptr || nodoAvl->esq == nullptr) return nodoAvl;
    NodoAVL<T> *temp = nodoAvl->esq;

    nodoAvl->esq = temp->dir;
    temp->dir = nodoAvl;

    nodoAvl->altura = recalculaAltura(nodoAvl);
    temp->altura = recalculaAltura(temp);

    return temp;
}

template<class T>
NodoAVL<T> *ArvoreAVL<T>::rotacionaEsq(NodoAVL<T> *nodoAvl) {
    if (nodoAvl == nullptr) return nodoAvl;
    NodoAVL<T> *temp = nodoAvl->dir;

    nodoAvl->dir = temp->esq;
    temp->esq = nodoAvl;

    nodoAvl->altura = recalculaAltura(nodoAvl);
    temp->altura = recalculaAltura(temp);

    return temp;
}

template<class T>
NodoAVL<T> *ArvoreAVL<T>::balanceia(NodoAVL<T> *nodoAvl) {
    if (nodoAvl == nullptr) return nodoAvl;

    int alturaEsq = getAltura(nodoAvl->esq);
    int alturaDir = getAltura(nodoAvl->dir);
    int dif;
    if (alturaDir >= alturaEsq)
        dif = alturaDir - alturaEsq;
    else dif = alturaEsq - alturaDir;

    if (dif > 1) {

        if (alturaDir > alturaEsq) {
            int dirEsqaltura = getAltura(nodoAvl->dir->esq);
            int dirDirAltura = getAltura(nodoAvl->dir->dir);

            if (dirEsqaltura > dirDirAltura)
                nodoAvl->dir = rotacionaDir(nodoAvl->dir);

            nodoAvl->altura = recalculaAltura(nodoAvl);
            nodoAvl = rotacionaEsq(nodoAvl);

        } else {

            int esqEsqAltura = getAltura(nodoAvl->esq->esq);
            int esqDirAltura = getAltura(nodoAvl->esq->dir);

            if (esqDirAltura > esqEsqAltura) {

                nodoAvl = rotacionaEsq(nodoAvl->esq);
            }
            nodoAvl->altura = recalculaAltura(nodoAvl);
            nodoAvl = rotacionaDir(nodoAvl);
        }
    }

    return nodoAvl;
}

template<class T>
void ArvoreAVL<T>::printEmPreOrdem(NodoAVL<T> *nodoAvl) {
    if (nodoAvl != nullptr) {
        std::cout << nodoAvl->chave << std::endl;
        printEmPreOrdem(nodoAvl->esq);
        printEmPreOrdem(nodoAvl->dir);
    }
}


template<class T>
void ArvoreAVL<T>::printEmPreOrdem() {
    printEmPreOrdem(raiz);
}

template<class T>
void ArvoreAVL<T>::estatisticas(NodoAVL<T> *nodoAvl) {
    if (nodoAvl != nullptr) {
        std::cout << "Chave: " << nodoAvl->chave << " | Fator balanceamento: "
                  << getAltura(nodoAvl->esq) - getAltura(nodoAvl->dir)
                  << " | Altura: " << nodoAvl->altura << " | Altura real: " << alturaReal(nodoAvl) << std::endl;
        estatisticas(nodoAvl->esq);
        estatisticas(nodoAvl->dir);
    }
}

template<class T>
void ArvoreAVL<T>::estatisticas() {
    estatisticas(raiz);
}


template<class T>
NodoAVL<T> *ArvoreAVL<T>::insere(NodoAVL<T> *nodoAvl, T chave) {
    if (nodoAvl == nullptr) {
        size++;
        return new NodoAVL<T>(chave);
    } else if (chave < nodoAvl->chave) {
        nodoAvl->esq = insere(nodoAvl->esq, chave);
    } else if (chave > nodoAvl->chave) {
        nodoAvl->dir = insere(nodoAvl->dir, chave);
    }
    nodoAvl->altura = recalculaAltura(nodoAvl);
    nodoAvl = balanceia(nodoAvl);
    return nodoAvl;
}


template<class T>
bool ArvoreAVL<T>::insere(T chave) {
    unsigned int sizePreInsert = size;
    raiz = insere(raiz, chave);
    return size > sizePreInsert;
}

template<class T>
bool ArvoreAVL<T>::busca(NodoAVL<T> *nodoAvl, T chave, NodoAVL<T> **result, int &numChamadas) {
    NodoAVL<T> *temp = nodoAvl;

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
bool ArvoreAVL<T>::busca(T chave, NodoAVL<T> **result, int &numChamadas) {
    return busca(raiz, chave, result, numChamadas);
}

template<class T>
bool ArvoreAVL<T>::buscaAnterior(NodoAVL<T> *nodoAvl, T chave, NodoAVL<T> **result) {
    NodoAVL<T> *temp = nodoAvl;

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
bool ArvoreAVL<T>::buscaAnterior(T chave, NodoAVL<T> **result) {
    return buscaAnterior(raiz, chave, result);
}

template<class T>
bool ArvoreAVL<T>::remove(NodoAVL<T> **pNodoAvl, T chave) {
    if ((*pNodoAvl)->chave == chave) {
        delete (*pNodoAvl);
        *pNodoAvl = nullptr;
        return true;
    }

    NodoAVL<T> *toDeleteChildrens;

    if (!buscaAnterior((*pNodoAvl), chave, &toDeleteChildrens)) {
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
        size--;
        return true;
    }
}

template<class T>
bool ArvoreAVL<T>::remove(T chave) {
    return remove(&raiz, chave);
}

template<class T>
ArvoreAVL<T>::~ArvoreAVL() {
    if (raiz) delete (raiz);
    raiz = nullptr;
}

template<class T>
void ArvoreAVL<T>::printEmOrdem(NodoAVL<T> *nodoAvl) {
    if (nodoAvl != nullptr) {
        printEmOrdem(nodoAvl->esq);
        std::cout << nodoAvl->chave << std::endl;
        printEmOrdem(nodoAvl->dir);
    }
}

template<class T>
void ArvoreAVL<T>::printEmOrdem() {
    printEmOrdem(raiz);
}

template<class T>
void ArvoreAVL<T>::printEmPosOrdem(NodoAVL<T> *nodoAvl) {
    if (nodoAvl != nullptr) {
        printEmPosOrdem(nodoAvl->esq);
        printEmPosOrdem(nodoAvl->dir);
        std::cout << nodoAvl->chave << std::endl;
    }
}

template<class T>
void ArvoreAVL<T>::printEmPosOrdem() {
    printEmPosOrdem(raiz);
}

template<class T>
int ArvoreAVL<T>::getAltura() {
    return getAltura(raiz);
}


#endif //GERENCIADORARVORE_ARVOREAVL_H
