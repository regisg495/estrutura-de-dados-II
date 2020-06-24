#include <iostream>
#include <windows.h>

#include "Lista.h"
#include "ArvoreDeBusca.h"

using namespace std;

enum menu {
    INSERIR = 1,
    REMOVER = 2,
    PREORDEM = 3,
    POSORDEM = 4,
    ORDEM = 5,
    REPETIDOS = 6,
    SAIR = 7,
};

void menu();

Lista *lerListaDoTerminal();

int main() {

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    auto *arvore = new ArvoreDeBusca();
    int opt = 0;
    unsigned int chaveCount = 0;
    string chaveCountVal;
    Lista *lista;

    cout << "Olá, seja bem-vindo(a) à criação de árvores binárias" << endl;
    cout << "Por enquanto, sua árvore não possui nenhum elemento" << endl << endl;

    while (opt != SAIR) {

        menu();
        cin >> opt;
        std::fflush(stdin);

        switch (opt) {

            case INSERIR:
                lista = lerListaDoTerminal();

                if (!arvore->insere(lista))
                    cout << "Não foi possível inserir o valor. Talvez já exista uma lista com esse"
                            " número de elementos " << endl;

                else cout << "Lista adicionada!" << endl;

                std::fflush(stdin);

                break;

            case REMOVER:

                cout << "Entre com a chave do nó que deseja remover: " << endl;

                cin >> chaveCountVal;

                while (!regex_match(chaveCountVal.c_str(), regex("[0-9]+"))) {
                    cout << "Formato de chave inválida. Entre com um formato válido: " << endl;
                    cin >> chaveCountVal;
                }

                chaveCount = static_cast<unsigned int>(stoul(chaveCountVal));

                if (arvore->remove(chaveCount)) cout << "Nó de chave " << chaveCount << " Removido" << endl;
                else cout << "Não foi possivel remover =(" << endl;

                std::fflush(stdin);

                break;

            case PREORDEM:
                cout << "Imprimindo em pré-ordem:" << endl;
                arvore->printEmPreOrdem();
                break;

            case POSORDEM:
                cout << "Imprimindo em pós-ordem:" << endl;
                arvore->printEmPosOrdem();
                break;

            case ORDEM:
                cout << "Imprimindo em ordem:" << endl;
                arvore->printEmOrdem();
                break;

            case REPETIDOS:

                if (arvore->vazia()) cout << "Sua árvore ainda está vazia" << endl;
                else cout << "Quantidade de elementos repetidos dentro das listas: " << arvore->repetidos() << endl;
                break;

            case SAIR:
                cout << "Até mais!";
                break;

            default:
                cout << "Esta não é uma opção válida =(" << endl;
                break;
        }
    }

    delete (arvore);

    return 0;
}

void menu() {
    cout <<
         "1: Inserir uma lista na árvore" << endl <<
         "2: Remover um elemento da árvore" << endl <<
         "3: Mostrar o valor dos elementos da árvore em pré-ordem" << endl <<
         "4: Mostrar o valor dos elementos da árvore em pós-ordem" << endl <<
         "5: Mostrar o valor dos elementos da árvore em ordem" << endl <<
         "6: Mostrar a quantidade de elementos repetidos existentes" << endl <<
         "7: Sair do programa" << endl <<
         "Escolha uma das opções acima" << endl;
}

Lista *lerListaDoTerminal() {

    string str;

    auto *lista = new Lista();

    cout << "Ok! Agora entre com os valores que quer adicionar, separado pelo caractere vírgula \",\": " << endl;
    cin >> str;
    string delimitador = ",";

    auto strInicio = 0U;
    auto strFim = str.find(delimitador);

    regex regexPattern("-?[0-9]+");

    if (!str.substr(0, str.find(delimitador)).empty() &&
        regex_match(str.substr(0, str.find(delimitador)), regexPattern)) {
        lista->insereNoFim(stoi(str.substr(0, str.find(delimitador))));
    }

    while (strFim != string::npos) {
        strInicio = strFim + delimitador.length();
        strFim = str.find(delimitador, strInicio);
        if (regex_match(str.substr(strInicio, strFim - strInicio), regexPattern))
            lista->insereNoFim(stoi(str.substr(strInicio, strFim - strInicio)));
    }

    return lista;
}