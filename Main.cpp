#include <iostream>
#include <locale.h>
#include <limits>
#include "grafo.h"
#include "funcoes.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese");

    int qntV, dirigido;
    cout << "Insira a quantidade de vértices: ";
    while (!(cin >> qntV) || qntV <= 0) {
        cout << "Entrada inválida! Digite apenas números maiores que 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "O grafo é dirigido? (1 = Sim, 0 = Não): ";
    cin >> dirigido;
    dirigido = (dirigido == 1) ? 1 : 0;

    int** matriz = criarMatriz(qntV);
    inserirConexoes(matriz, qntV, dirigido);

    int opcao;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Adicionar vértice\n";
        cout << "2. Adicionar aresta/arco\n";
        cout << "3. Mostrar matriz de adjacência\n";
        cout << "4. Executar DFS\n";
        cout << "5. Executar BFS\n";
        cout << "6. Procurar vértice\n";
        cout << "7. Remover aresta/arco\n";
        cout << "8. Remover vértice\n";
        cout << "9. Apagar grafo\n";
        cout << "10. Fecho transitivo direto\n";
        cout << "11. Fecho transitivo inverso\n";
        cout << "12. Verificar se o grafo é conexo / Mostrar componentes\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
        case 1: matriz = adicionarVertice(matriz, qntV); break;
        case 2: adicionarAresta(matriz, qntV, dirigido); break;
        case 3: imprimirMatriz(matriz, qntV); break;
        case 4: executarDFS(matriz, qntV); break;
        case 5: executarBFS(matriz, qntV); break;
        case 6: procurarVertice(qntV); break;
        case 7: removerAresta(matriz, qntV, dirigido); break;
        case 8: matriz = removerVertice(matriz, qntV); break;
        case 9:
            liberarMatriz(matriz, qntV);
            cout << "Digite a nova quantidade de vértices: ";
            cin >> qntV;
            cout << "O grafo é dirigido? (1 = Sim, 0 = Não): ";
            cin >> dirigido;
            dirigido = (dirigido == 1) ? 1 : 0;
            matriz = criarMatriz(qntV);
            inserirConexoes(matriz, qntV, dirigido);
            cout << "Grafo redefinido com sucesso!\n";
            break;
        case 10: fechoTransitivoDireto(matriz, qntV); break;
        case 11: fechoTransitivoInverso(matriz, qntV); break;
        case 12:
            if (!dirigido) {
                if (ehConexoNaoDirigido(matriz, qntV))
                    cout << "O grafo é conexo.\n";
                else
                    cout << "O grafo NÃO é conexo.\n";
            } else {
            encontrarComponentesFortementeConexos(matriz, qntV);
            }
        break;
        case 0: cout << "Saindo...\n"; break;
        default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);

    liberarMatriz(matriz, qntV);
    return 0;
}
