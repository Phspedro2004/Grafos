#ifndef FUNCOES_H
#define FUNCOES_H

#include <iostream>
#include <limits>
#include <vector>
#include "fila.h"
#include "grafo.h"
using namespace std;

// ---------------- DFS ----------------
void DFS_rec(int v, int** mat, int qntV, bool* visitado) {
    visitado[v] = true;
    cout << v + 1 << " ";
    for (int i = 0; i < qntV; i++) {
        if (mat[v][i] == 1 && !visitado[i]) DFS_rec(i, mat, qntV, visitado);
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

    bool* visitado = new bool[qntV];
    for (int i = 0; i < qntV; i++) visitado[i] = false;

    cout << "Percurso DFS a partir de " << inicio + 1 << ": ";
    DFS_rec(inicio, mat, qntV, visitado);

    // Se o grafo for desconexo, percorre os outros
    for (int i = 0; i < qntV; i++) {
        if (!visitado[i]) DFS_rec(i, mat, qntV, visitado);
    }
    cout << "\n";
    delete[] visitado;
}

// ---------------- BFS ----------------
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

    bool* visitado = new bool[qntV];
    for (int i = 0; i < qntV; i++) visitado[i] = false;

    cout << "Percurso BFS a partir de " << inicio + 1 << ": ";
    BFS(inicio, mat, qntV, visitado);

    for (int i = 0; i < qntV; i++) {
        if (!visitado[i]) BFS(i, mat, qntV, visitado);
    }
    cout << "\n";
    delete[] visitado;
}

// ---------------- Operações ----------------
void procurarVertice(int qntV) {
    int v;
    cout << "Digite o vértice a procurar: ";
    cin >> v;
    if (v >= 1 && v <= qntV) cout << "O vértice " << v << " existe no grafo.\n";
    else cout << "O vértice " << v << " NÃO existe no grafo.\n";
}

void adicionarAresta(int** mat, int qntV, bool dirigido) {
    int v1, v2;
    cout << "Insira a aresta (v1 v2): ";
    cin >> v1 >> v2;
    if (v1 < 1 || v1 > qntV || v2 < 1 || v2 > qntV) {
        cout << "Vértices inválidos!\n";
        return;
    }
    if (mat[v1-1][v2-1] == 1) {
        cout << "Aresta já existe!\n";
        return;
    }
    mat[v1-1][v2-1] = 1;
    if (!dirigido) mat[v2-1][v1-1] = 1;
    cout << "Aresta adicionada!\n";
}

void removerAresta(int** mat, int qntV, bool dirigido) {
    int v1, v2;
    cout << "Digite os vértices da aresta a remover (v1 v2): ";
    cin >> v1 >> v2;
    if (v1 < 1 || v1 > qntV || v2 < 1 || v2 > qntV) {
        cout << "Vértices inválidos!\n";
        return;
    }
    if (mat[v1-1][v2-1] == 0) {
        cout << "Aresta não existe!\n";
        return;
    }
    mat[v1-1][v2-1] = 0;
    if (!dirigido) mat[v2-1][v1-1] = 0;
    cout << "Aresta removida!\n";
}

int** adicionarVertice(int** mat, int& qntV) {
    int novoV = qntV + 1;
    int** nova = criarMatriz(novoV);
    for (int i = 0; i < qntV; i++)
        for (int j = 0; j < qntV; j++)
            nova[i][j] = mat[i][j];
    liberarMatriz(mat, qntV);
    qntV = novoV;
    cout << "Vértice adicionado! Agora são " << qntV << " vértices.\n";
    return nova;
}

int** removerVertice(int** mat, int& qntV) {
    if (qntV <= 1) {
        cout << "Não é possível remover mais vértices.\n";
        return mat;
    }
    int v;
    cout << "Digite o vértice a remover: ";
    cin >> v;
    if (v < 1 || v > qntV) {
        cout << "Vértice inválido!\n";
        return mat;
    }
    int novoV = qntV - 1;
    int** nova = criarMatriz(novoV);
    for (int i = 0, ni = 0; i < qntV; i++) {
        if (i == v-1) continue;
        for (int j = 0, nj = 0; j < qntV; j++) {
            if (j == v-1) continue;
            nova[ni][nj] = mat[i][j];
            nj++;
        }
        ni++;
    }
    liberarMatriz(mat, qntV);
    qntV = novoV;
    cout << "Vértice removido! Agora são " << qntV << " vértices.\n";
    return nova;
}

// ---------------- Fecho Transitivo Direto (BFS) ----------------
void fechoTransitivoDireto(int** mat, int qntV) {
    int v;
    cout << "Digite o vértice inicial: ";
    cin >> v;
    if (v < 1 || v > qntV) {
        cout << "Vértice inválido!\n";
        return;
    }
    int inicio = v - 1;
    bool* visitado = new bool[qntV];
    int* nivel = new int[qntV];
    for (int i = 0; i < qntV; i++) { visitado[i] = false; nivel[i] = -1; }

    Fila<int> f;
    inicializarFila(f);

    inserirFila(f, inicio);
    visitado[inicio] = true;
    nivel[inicio] = 0;

    cout << "\nFecho transitivo direto do vértice " << v << ":\n";
    cout << "Vértice (Nível)\n";
    cout << "----------------\n";

    while (!filaVazia(f)) {
        int u;
        retirarFila(f, u);
        cout << u + 1 << " (" << nivel[u] << ")\n";

        for (int i = 0; i < qntV; i++) {
            if (mat[u][i] == 1 && !visitado[i]) {
                inserirFila(f, i);
                visitado[i] = true;
                nivel[i] = nivel[u] + 1;
            }
        }
    }
    cout << "----------------\n";

    delete[] visitado;
    delete[] nivel;
}

// ---------------- Fecho Transitivo Inverso (BFS invertido) ----------------
void fechoTransitivoInverso(int** mat, int qntV) {
    int v;
    cout << "Digite o vértice inicial: ";
    cin >> v;
    if (v < 1 || v > qntV) {
        cout << "Vértice inválido!\n";
        return;
    }
    int inicio = v - 1;
    bool* visitado = new bool[qntV];
    int* nivel = new int[qntV];
    for (int i = 0; i < qntV; i++) { visitado[i] = false; nivel[i] = -1; }

    Fila<int> f;
    inicializarFila(f);

    inserirFila(f, inicio);
    visitado[inicio] = true;
    nivel[inicio] = 0;

    cout << "\nFecho transitivo inverso do vértice " << v << ":\n";
    cout << "Vértice (Nível)\n";
    cout << "----------------\n";

    while (!filaVazia(f)) {
        int u;
        retirarFila(f, u);
        cout << u + 1 << " (" << nivel[u] << ")\n";

        for (int i = 0; i < qntV; i++) {
            if (mat[i][u] == 1 && !visitado[i]) { // invertido!
                inserirFila(f, i);
                visitado[i] = true;
                nivel[i] = nivel[u] + 1;
            }
        }
    }
    cout << "----------------\n";

    delete[] visitado;
    delete[] nivel;
}

// ---------------- Verificar se o grafo é conexo ----------------
bool ehConexoNaoDirigido(int** mat, int qntV) {
    bool* visitado = new bool[qntV];
    for (int i = 0; i < qntV; i++) visitado[i] = false;

    // Faz DFS a partir do vértice 0
    DFS_rec(0, mat, qntV, visitado);

    // Se algum vértice não foi visitado, não é conexo
    for (int i = 0; i < qntV; i++) {
        if (!visitado[i]) {
            delete[] visitado;
            return false;
        }
    }
    delete[] visitado;
    return true;
}

// ---------------- Transposição da matriz (necessária para Kosaraju) ----------------
int** transporGrafo(int** mat, int qntV) {
    int** trans = criarMatriz(qntV);
    for (int i = 0; i < qntV; i++) {
        for (int j = 0; j < qntV; j++) {
            if (mat[i][j] == 1) trans[j][i] = 1;
        }
    }
    return trans;
}

// ---------------- Kosaraju para componentes fortemente conexos ----------------
void preencherOrdem(int v, bool* visitado, int** mat, int qntV, Fila<int>& ordem) {
    visitado[v] = true;
    for (int i = 0; i < qntV; i++) {
        if (mat[v][i] == 1 && !visitado[i])
            preencherOrdem(i, visitado, mat, qntV, ordem);
    }
    inserirFila(ordem, v);
}

void DFS_componentes(int v, bool* visitado, int** mat, int qntV) {
    visitado[v] = true;
    cout << v + 1 << " ";
    for (int i = 0; i < qntV; i++) {
        if (mat[v][i] == 1 && !visitado[i])
            DFS_componentes(i, visitado, mat, qntV);
    }
}

void DFS_componentes_scc(int v, bool* visitado, int** mat, int qntV, vector<int>& scc) {
    visitado[v] = true;
    scc.push_back(v); // adiciona o vértice atual à SCC
    for (int i = 0; i < qntV; i++) {
        if (mat[v][i] == 1 && !visitado[i])
            DFS_componentes_scc(i, visitado, mat, qntV, scc);
    }
}

void encontrarComponentesFortementeConexos(int** mat, int qntV) {
    bool* visitado = new bool[qntV];
    for (int i = 0; i < qntV; i++) visitado[i] = false;

    // 1ª DFS para preencher ordem
    Fila<int> ordem;
    inicializarFila(ordem);
    for (int i = 0; i < qntV; i++) {
        if (!visitado[i]) preencherOrdem(i, visitado, mat, qntV, ordem);
    }

    // Transpõe grafo
    int** transposto = transporGrafo(mat, qntV);

    for (int i = 0; i < qntV; i++) visitado[i] = false;

    cout << "\nComponentes Fortemente Conexos Máximos:\n";
    cout << "=======================================\n";

    while (!filaVazia(ordem)) {
        int v;
        retirarFila(ordem, v);
        if (!visitado[v]) {
            vector<int> scc; // vetor para armazenar os vértices da SCC
            // Chamada DFS modificada
            DFS_componentes_scc(v, visitado, transposto, qntV, scc);

            // Imprime o SCC encontrado
            cout << "SCC: ";
            for (int u : scc) cout << u + 1 << " ";
            cout << endl;
        }
    }

    liberarMatriz(transposto, qntV);
    delete[] visitado;
}


#endif // FUNCOES_H
