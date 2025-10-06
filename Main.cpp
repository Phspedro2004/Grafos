#include <iostream>
#include <locale.h>
#include <limits>
#include <vector>
#include <string>
#include "grafo.h"
#include "funcoes.h"
using namespace std;

// Função para limpar tela
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para pausar tela
void pausar() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Função para ler opção com validação
int lerOpcao(int min, int max) {
    int opcao;
    while (!(cin >> opcao) || opcao < min || opcao > max) {
        cout << "Opção inválida! Digite um número entre " << min << " e " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return opcao;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Grafo<string> g;

    // -------------------- Configuração inicial --------------------
    cout << "Insira a quantidade de vértices: ";
    while (!(cin >> g.qntV) || g.qntV <= 0) {
        cout << "Entrada inválida! Digite apenas números maiores que 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "O grafo é dirigido? (1 = Sim, 0 = Não): ";
    cin >> g.dirigido;
    g.dirigido = (g.dirigido == 1);

    g.mat = criarMatriz(g.qntV);
    g.rotulos.resize(g.qntV);

    cout << "Digite os rótulos dos vértices:\n";
    for (int i = 0; i < g.qntV; i++) {
        cout << "Vértice " << i + 1 << ": ";
        cin >> g.rotulos[i];
    }

    // -------------------- Menu principal --------------------
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
        cout << "9. Apagar grafo e redefinir\n";
        cout << "10. Fecho transitivo direto\n";
        cout << "11. Fecho transitivo inverso\n";
        cout << "12. Verificar conexidade / componentes fortemente conexos\n";
        cout << "13. Colorir grafo (heurística gulosa)\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";

        opcao = lerOpcao(0, 13);

        switch (opcao) {
            case 1:
                g.mat = adicionarVertice(g.mat, g.qntV);
                g.rotulos.push_back(""); 
                cout << "Digite o rótulo do novo vértice: ";
                cin >> g.rotulos.back();
                break;
            case 2:
                adicionarAresta(g.mat, g.qntV, g.dirigido, g.rotulos);
                break;
            case 3:
                imprimirMatriz(g.mat, g.qntV);
                break;
            case 4:
                executarDFS(g.mat, g.qntV, g.rotulos);
                break;
            case 5:
                executarBFS(g.mat, g.qntV, g.rotulos);
                break;
            case 6:
                procurarVertice(g.rotulos);
                break;
            case 7:
                removerAresta(g.mat, g.qntV, g.dirigido, g.rotulos);
                break;
            case 8:
                g.mat = removerVertice(g.mat, g.qntV, g.rotulos);
                g.rotulos.pop_back(); 
                break;
            case 9:
                liberarMatriz(g.mat, g.qntV);
                cout << "Digite a nova quantidade de vértices: ";
                cin >> g.qntV;
                cout << "O grafo é dirigido? (1 = Sim, 0 = Não): ";
                cin >> g.dirigido;
                g.dirigido = (g.dirigido == 1);
                g.mat = criarMatriz(g.qntV);
                g.rotulos.resize(g.qntV);
                cout << "Digite os rótulos dos vértices:\n";
                for (int i = 0; i < g.qntV; i++) cin >> g.rotulos[i];
                break;
            case 10:
                fechoTransitivoDireto(g.mat, g.qntV, g.rotulos);
                break;
            case 11:
                fechoTransitivoInverso(g.mat, g.qntV, g.rotulos);
                break;
            case 12:
                if (!g.dirigido) {
                    if (ehConexoNaoDirigido(g.mat, g.qntV))
                        cout << "O grafo é conexo.\n";
                    else
                        cout << "O grafo NÃO é conexo.\n";
                } else {
                    encontrarComponentesFortementeConexos(g.mat, g.qntV, g.rotulos);
                }
                break;
            case 13:
                colorirGrafo(g.mat, g.qntV, g.rotulos);
                break;
            case 0:
                cout << "Saindo...\n";
                break;
        }

        pausar();
        limparTela();

    } while (opcao != 0);

    liberarMatriz(g.mat, g.qntV);
    return 0;
}
