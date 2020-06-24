//
// Created by regis on 11/04/2020.
//

#ifndef GERENCIADORARVORE_GERENCIADORARVORE_H
#define GERENCIADORARVORE_GERENCIADORARVORE_H

#include "ArvoreDeBusca.h"
#include "ArvoreAVL.h"
#include <iostream>
#include <ctime>

using namespace std;

template<typename T>
class GerenciadorArvore {

public:
    bool ready{false};
    int tamanho;
    ArvoreDeBusca<T> *arvoreDeBusca;
    ArvoreAVL<T> *arvoreAvl;

public:

    explicit GerenciadorArvore(int tamanho) : tamanho(tamanho) {}

    int criaBST();

    void criaAVL();

    bool insere(T chave);

    bool remove(T chave);

public:

    void geraArvores();

};


template<typename T>
void GerenciadorArvore<T>::geraArvores() {
    criaBST();
    criaAVL();

    if (arvoreAvl->getSize() == arvoreDeBusca->getSize()) {
        ready = true;
    } else {
        delete (arvoreDeBusca);
        delete (arvoreAvl);
    }
}

template<typename T>
int GerenciadorArvore<T>::criaBST() {
    srand(time(nullptr));
    arvoreDeBusca = new ArvoreDeBusca<T>();
    int naoInseridos = 0;

    for (int i = 0; i < tamanho; i++) {
        T chave = rand();
        if (!arvoreDeBusca->insere(chave)) naoInseridos++;
    }
    tamanho -= naoInseridos;

    return naoInseridos;
}

template<typename T>
void GerenciadorArvore<T>::criaAVL() {
    if (arvoreDeBusca == nullptr) return;
    arvoreAvl = arvoreDeBusca->toAVL();
}

template<typename T>
bool GerenciadorArvore<T>::insere(T chave) {
    if (!arvoreDeBusca->insere(chave)) {
        return false;
    } else {
        if (!arvoreAvl->insere(chave)) {
            arvoreDeBusca->remove(chave);
            return false;
        } else {
            return true;
        }
    }
}

template<typename T>
bool GerenciadorArvore<T>::remove(T chave) {
    if (!arvoreDeBusca->remove(chave)) {
        return false;
    } else {
        if (!arvoreAvl->remove(chave)) {
            arvoreDeBusca->insere(chave);
            return false;
        } else {
            return true;
        }
    }
}


#endif //GERENCIADORARVORE_GERENCIADORARVORE_H
