//
// Created by regis on 06/05/2020.
//

#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H


#include "Pagina.h"

template<typename T>
class ArvoreB {

private:

    Pagina<T> *raiz;
    unsigned int ordem;

public:

    explicit ArvoreB(unsigned int ordem);

    void insere(T chave);

    void print();

    Pagina<T> *busca(T chave);

};

template<typename T>
ArvoreB<T>::ArvoreB(unsigned int ordem):ordem(ordem) {
    this->ordem = ordem;
    this->raiz = new Pagina<T>(ordem, true);
}

template<typename T>
void ArvoreB<T>::insere(T chave) {
    Pagina<T> *pagina = nullptr;
    T *pChave = new T;
    this->raiz->inserePagina(chave, pChave, pagina);
    if (pagina != nullptr)
        this->raiz = this->raiz->trocaRaiz(pChave, pagina);
}

template<typename T>
void ArvoreB<T>::print() {
    this->raiz->print(0);
}

template<typename T>
Pagina<T> *ArvoreB<T>::busca(T chave) {
    return this->raiz->busca(chave);
}


#endif //ARVOREB_ARVOREB_H
