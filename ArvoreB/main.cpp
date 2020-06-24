#include <iostream>
#include <windows.h>

#include "ArvoreB.h"

enum menu {
    INSERIR = 1,
    BUSCA = 2,
    PRINT = 3,
    SAIR = 4
};

void menu();

int main() {

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    auto *arvoreB = new ArvoreB<int>(2);

    int opt = 0;
    int chave;

    while (opt != SAIR) {
        menu();
        cin >> opt;

        fflush(stdin);

        switch (opt) {

            case INSERIR:

                cout << "Entre com o elemento que deseja inserir: " << endl;
                cin >> chave;

                arvoreB->insere(chave);

                cout << "Operação realizada!" << endl;

                break;

            case BUSCA:

                cout << "Entre com o elemento que deseja buscar: " << endl;
                cin >> chave;

                if (arvoreB->busca(chave) != nullptr)
                    cout << "Elemento encontrado " << endl;
                else cout << "Não existe esse elemento" << endl;

                break;

            case PRINT:

                cout << "Mostrando elementos da árvore B" << endl;

                arvoreB->print();

                break;

            case SAIR:

                cout << "Bye" << endl;

                break;

            default:

                cout << "Essa não é uma opção válida" << endl;

                break;
        }

    }

    return 0;
}

void menu() {
    cout << "Escolha a opção que deseja: " << endl
         << "1 para inserir na árvore B" << endl
         << "2 para buscar um elemento" << endl
         << "3 para mostrar todos os elementos da árvore B" << endl
         << "4 para sair" << endl;
}