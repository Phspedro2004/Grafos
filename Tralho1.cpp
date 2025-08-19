#include <iostream>
#include <windows.h>
#include <locale.h>
using namespace std;

#ifndef TAM
#define TAM 50
#endif // TAM

// ====== ESTRUTURA DE FILA ======
template <typename T>
struct Fila {
    T info[TAM];
    int comeco, fim;
};

template <typename T>
void inicializarFila(Fila<T>& f) {
    f.comeco = 0;
    f.fim = -1;
}

template <typename T>
bool filaVazia(Fila<T> f) {
    return f.fim < f.comeco;
}

template <typename T>
bool filaCheia(Fila<T> f) {
    return f.fim == TAM - 1;
}

template <typename T>
bool inserirFila(Fila<T>& f, T valor) {
    if (filaCheia(f)) return false;
    f.fim++;
    f.info[f.fim] = valor;
    return true;
}

template <typename T>
bool retirarFila(Fila<T>& f, T& valor) {
    if (filaVazia(f)) return false;
    valor = f.info[f.comeco];
    f.comeco++;
    return true;
}

// ====== FUNÇÕES DO GRAFO ======
int** criarMatriz(int qntV) {
    int** mat = new int* [qntV];
    for (int i = 0; i < qntV; ++i) {
        mat[i] = new int[qntV]();
    }
    return mat;
}

void liberarMatriz(int** mat, int qntV) {
    for (int i = 0; i < qntV; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

void inserirConexoes(int** mat, int qntV, bool dirigido) {
    int v1, v2;
    int insere = 1;

    while (insere != 0) {
        cout << "Insira a conexão (v1 -> v2):\n";
        cout << "v1: "; cin >> v1;
        cout << "v2: "; cin >> v2;

        if (v1 < 1 || v1 > qntV || v2 < 1 || v2 > qntV) {
            cout << "Vértices inválidos!\n";
        } else {
            mat[v1 - 1][v2 - 1] = 1;
            if (!dirigido) mat[v2 - 1][v1 - 1] = 1;
        }

        cout << "Deseja fazer mais conexões? (1 = Sim, 0 = Não): ";
        cin >> insere;
    }
}

void imprimirMatriz(int** mat, int qntV, HANDLE hConsole) {
    cout << "\nMatriz de Adjacência:\n";
    cout << "====================\n";
    for (int i = 0; i < qntV; i++) {
        for (int j = 0; j < qntV; j++) {
            if (mat[i][j] == 1) {
                SetConsoleTextAttribute(hConsole, 10); // Verde
            } else {
                SetConsoleTextAttribute(hConsole, 13); // Rosa
            }
            cout << mat[i][j] << " ";
        }
        SetConsoleTextAttribute(hConsole, 7);
        cout << "\n";
    }
    cout << "====================\n";
}

// ====== DFS ======
void DFS(int v, int** mat, int qntV, bool* visitado) {
    cout << v + 1 << " ";
    visitado[v] = true;

    for (int i = 0; i < qntV; i++) {
        if (mat[v][i] == 1 && !visitado[i]) {
            DFS(i, mat, qntV, visitado);
        }
    }
}

void executarDFS(int** mat, int qntV) {
    int inicio;
    cout << "Digite o vértice inicial para DFS: ";
    cin >> inicio;
    inicio--;

    if (inicio < 0 || inicio >= qntV) {
        cout << "Vértice inválido!\n";
        return;
    }

    bool visitado[TAM] = { false };
    cout << "Percurso DFS: ";
    DFS(inicio, mat, qntV, visitado);

    // Se o grafo for desconexo, percorre os outros
    for (int i = 0; i < qntV; i++) {
        if (!visitado[i]) {
            DFS(i, mat, qntV, visitado);
        }
    }
    cout << "\n";
}

// ====== BFS ======
void BFS(int inicio, int** mat, int qntV, bool* visitado) {
    Fila<int> f;
    inicializarFila(f);

    inserirFila(f, inicio);
    visitado[inicio] = true;

    while (!filaVazia(f)) {
        int v;
        retirarFila(f, v);
        cout << v + 1 << " ";

        for (int i = 0; i < qntV; i++) {
            if (mat[v][i] == 1 && !visitado[i]) {
                inserirFila(f, i);
                visitado[i] = true;
            }
        }
    }
}

void executarBFS(int** mat, int qntV) {
    int inicio;
    cout << "Digite o vértice inicial para BFS: ";
    cin >> inicio;
    inicio--;

    if (inicio < 0 || inicio >= qntV) {
        cout << "Vértice inválido!\n";
        return;
    }

    bool visitado[TAM] = { false };
    cout << "Percurso BFS: ";
    BFS(inicio, mat, qntV, visitado);

    for (int i = 0; i < qntV; i++) {
        if (!visitado[i]) {
            BFS(i, mat, qntV, visitado);
        }
    }
    cout << "\n";
}

// ====== Verificar existência de vértice ======
void procurarVertice(int qntV) {
    int v;
    cout << "Digite o vértice a procurar: ";
    cin >> v;
    if (v >= 1 && v <= qntV) {
        cout << "O vértice " << v << " existe no grafo.\n";
    } else {
        cout << "O vértice " << v << " NÃO existe no grafo.\n";
    }
}

// ====== MAIN ======
int main() {
    setlocale(LC_ALL, "Portuguese");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int qntV, dirigido;
    cout << "Insira a quantidade de vértices: ";
    cin >> qntV;

    cout << "O grafo é dirigido? (1 = Sim, 0 = Não): ";
    cin >> dirigido;

    int** matriz = criarMatriz(qntV);
    inserirConexoes(matriz, qntV, dirigido);

    int opcao;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Mostrar matriz de adjacência\n";
        cout << "2. Executar DFS\n";
        cout << "3. Executar BFS\n";
        cout << "4. Procurar vértice\n";
        cout << "0. Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
        case 1: imprimirMatriz(matriz, qntV, hConsole); break;
        case 2: executarDFS(matriz, qntV); break;
        case 3: executarBFS(matriz, qntV); break;
        case 4: procurarVertice(qntV); break;
        case 0: cout << "Saindo...\n"; break;
        default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);

    liberarMatriz(matriz, qntV);
    return 0;
}



