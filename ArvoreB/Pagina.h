//
// Created by regis on 02/05/2020.
//

#ifndef ARVOREB_PAGINA_H
#define ARVOREB_PAGINA_H

#include <vector>

using namespace std;

template<typename T>
class ArvoreB;

template<typename T>
class Pagina;

template<typename T>
class Pagina {

    friend class ArvoreB<T>;

public:

    vector<T> chaves;
    vector<Pagina<T> *> childs;
    unsigned int ordem;
    bool folha;

    explicit Pagina(unsigned int ordem, bool folha);

    void inserePagina(T chave, T *pChave, Pagina<T> *&pagina);

    void splitPagina(T *pChave, Pagina<T> *&pagina);

    Pagina<T> *trocaRaiz(T *pChave, Pagina<T> *pagina);

    void print(unsigned int numPagina);

    Pagina<T> *busca(T chave);

};

template<typename T>
Pagina<T>::Pagina(unsigned int ordem, bool folha):ordem(ordem), folha(folha) {
    this->ordem = ordem;
    this->folha = folha;
}

template<typename T>
void Pagina<T>::inserePagina(T chave, T *pChave, Pagina<T> *&pagina) {
    if (!this->folha) {
        int i = 0;

        while (i < this->chaves.size() && chave > this->chaves.at(i)) i++;

        this->childs.at(i)->inserePagina(chave, pChave, pagina);

        if (pagina == nullptr)
            return;

        this->chaves.insert(this->chaves.begin() + i, *pChave);
        this->childs.insert(this->childs.begin() + i + 1, pagina);

        if (this->chaves.size() < 2 * this->ordem)
            pagina = nullptr;
        else this->splitPagina(pChave, pagina);

    } else {

        typename vector<T>::iterator itr = lower_bound(this->chaves.begin(), this->chaves.end(), chave);
        this->chaves.insert(itr, chave);

        if (this->chaves.size() == 2 * this->ordem) {
            pagina = new Pagina<T>(this->ordem, true);
            *pChave = this->chaves.at(this->ordem);

            for (int i = this->ordem + 1; i < 2 * this->ordem; i++)
                pagina->chaves.push_back(this->chaves.at(i));

            this->chaves.resize(this->ordem);
        }
    }

}

template<typename T>
void Pagina<T>::splitPagina(T *pChave, Pagina<T> *&pagina) {
    pagina = new Pagina<T>(this->ordem, false);
    *pChave = this->chaves.at(this->ordem);

    for (int i = this->ordem + 1; i < 2 * this->ordem; i++)
        pagina->chaves.push_back(this->chaves.at(i));

    this->chaves.resize(this->ordem);

    for (int i = this->ordem + 1; i <= 2 * this->ordem; i++)
        pagina->childs.push_back(this->childs.at(i));

    this->childs.resize(this->ordem + 1);
}

template<typename T>
Pagina<T> *Pagina<T>::trocaRaiz(T *pChave, Pagina<T> *pagina) {
    auto *raiz = new Pagina<T>(this->ordem, false);
    raiz->chaves.push_back(*pChave);
    raiz->childs.push_back(this);
    raiz->childs.push_back(pagina);

    return raiz;
}

template<typename T>
void Pagina<T>::print(unsigned int numPagina) {
    int i;
    cout << "Pagina: " << numPagina << endl;
    for (i = 0; i < this->chaves.size(); i++) {
        if (!this->folha) {
            numPagina++;

            this->childs.at(i)->print(numPagina);
        }
        cout << "Chave: " << this->chaves.at(i) << endl;
    }

    if (!this->folha)
        this->childs.at(i)->print(numPagina);

}

template<typename T>
Pagina<T> *Pagina<T>::busca(T chave) {
    int i = 0;

    while (i < this->chaves.size() && chave > this->chaves.at(i))
        i++;

    if (this->chaves.at(i) == chave)
        return this;

    if (this->folha)
        return nullptr;

    return this->childs.at(i)->busca(chave);

}

#endif //ARVOREB_PAGINA_H
