#include <iostream>
#include <afxres.h>

#include "GerenciadorArvore.h"

using namespace std;


enum menu {
    INSERIR = 1,
    REMOVER = 2,
    PREORDEM = 3,
    POSORDEM = 4,
    ORDEM = 5,
    BUSCA = 6,
    ALTURA = 7,
    SAIR = 8,
};

void menu();

int main() {

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    int opt = 0;
    int tamanho = 0;
    int chave;
    int numChamadasBusca = 0;
    int numChamadasAVL = 0;

    cout << "Olá! Bem vindo ao comparador de Árvores" << endl;

    cout << "Entre com um número de elementos inicial para que eu preencha as árvores com elementos aleatórios" << endl;

    cin >> tamanho;

    while (tamanho <= 0) {
        cout << "Entre com um número válido, maior que zero << endl";
        cin >> tamanho;
    }

    fflush(stdin);
    auto *gerenciadorArvore = new GerenciadorArvore<int>(tamanho);

    NodoBusca<int> *nodoBusca;
    NodoAVL<int> *nodoAvl;

    gerenciadorArvore->geraArvores();

    while (opt != SAIR) {

        menu();
        cin >> opt;
        std::fflush(stdin);

        switch (opt) {
            case INSERIR:
                cout << "Entre com o a chave do elemento que deseja inserir: " << endl;
                cin >> chave;

                if (gerenciadorArvore->insere(chave))
                    cout << "Elemento inserido em ambas as árvores com sucesso! " << endl;
                else cout << "Não foi possível inserir";

                std::fflush(stdin);

                break;

            case REMOVER:

                cout << "Entre com a chave do elemento que deseja remover: " << endl;
                cin >> chave;

                if (gerenciadorArvore->remove(chave))
                    cout << "Elemento removido com sucesso!" << endl;
                else cout << "Não foi possível remover" << endl;

            case PREORDEM:
                cout << "Mostrando os elementos da Árvore de Busca em pré-ordem" << endl;
                gerenciadorArvore->arvoreDeBusca->printEmPreOrdem();
                cout << "Mostrando os elementos da Árvore AVL em pré-ordem" << endl;
                gerenciadorArvore->arvoreAvl->printEmPreOrdem();

                break;

            case ORDEM:
                cout << "Mostrando os elementos da Árvore de Busca em ordem" << endl;
                gerenciadorArvore->arvoreDeBusca->printEmOrdem();
                cout << "Mostrando os elementos da Árvore AVL em ordem" << endl;
                gerenciadorArvore->arvoreAvl->printEmOrdem();
                break;

            case POSORDEM:
                cout << "Mostrando os elementos da Árvore de Busca em pós-ordem" << endl;
                gerenciadorArvore->arvoreDeBusca->printEmPosOrdem();
                cout << "Mostrando os elementos da Árvore AVL em pós-ordem" << endl;
                gerenciadorArvore->arvoreAvl->printEmPosOrdem();

                break;

            case BUSCA:

                cout << "Entre com o número da chave que deseja buscar: " << endl;
                int busca;
                cin >> busca;
                if (gerenciadorArvore->arvoreDeBusca->busca(busca, &nodoBusca, numChamadasBusca)
                    && gerenciadorArvore->arvoreAvl->busca(busca, &nodoAvl, numChamadasAVL)) {
                    cout << "Elemento de valor " << busca << " encontrado! " << endl;
                    cout << "Foram necessárias " << numChamadasBusca
                         << " para a busca desse elemento na Árvore de Busca" << endl;
                    cout << "Foram necessárias " << numChamadasAVL << " para a busca desse elemento na Árvore AVL"
                         << endl;
                } else {
                    cout << "Não foi possível encontrar o elemento " << busca << endl;
                }
                numChamadasBusca = 0;
                numChamadasAVL = 0;
                break;

            case ALTURA:

                cout << "Altura da sua Árvore de Busca: " << gerenciadorArvore->arvoreDeBusca->getAltura()
                     << endl;
                cout << "Altura da sua Árvore AVL: " << gerenciadorArvore->arvoreAvl->getAltura() << endl;

                break;

            case SAIR:
                cout << "Saindo" << endl;
                break;
            default:
                cout << "Essa não é uma opção válida" << endl;
                break;

        }

        delete (gerenciadorArvore);
    }
}

void menu() {
    cout <<
         "1: Inserir um elemento nas árvores" << endl <<
         "2: Remover um elemento das árvores" << endl <<
         "3: Mostrar o valor dos elementos das árvores em pré-ordem" << endl <<
         "4: Mostrar o valor dos elementos das árvores em pós-ordem" << endl <<
         "5: Mostrar o valor dos elementos das árvores em ordem" << endl <<
         "6: Buscar um elemento em ambas as árvores e mostrar a quantidade de iterações" << endl <<
         "7: Mostrar a altura de ambas as árvores" << endl <<
         "8: Sair do programa" << endl <<
         "Escolha uma das opções acima" << endl;
}
