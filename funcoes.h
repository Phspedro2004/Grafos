#ifndef FUNCOES_H
#define FUNCOES_H

#include <iostream>
#include <vector>
#include "fila.h"
using namespace std;

// ---------------- Auxiliar: buscar índice do rótulo ----------------
template <typename T>
int buscarIndice(const vector<T>& rotulos, T valor) {
    for (int i = 0; i < (int)rotulos.size(); i++)
        if (rotulos[i] == valor) return i;
    return -1;
}

// ---------------- DFS ----------------
template <typename T>
void DFS_rec(int v, int** mat, int qntV, bool* visitado, const vector<T>& rotulos) {
    visitado[v] = true;
    cout << rotulos[v] << " ";
    for (int i = 0; i < qntV; i++)
        if (mat[v][i] == 1 && !visitado[i]) DFS_rec(i, mat, qntV, visitado, rotulos);
}

template <typename T>
void executarDFS(int** mat, int qntV, const vector<T>& rotulos) {
    T inicioValor;
    cout << "Digite o vértice inicial para DFS: ";
    cin >> inicioValor;

    int inicio = buscarIndice(rotulos, inicioValor);
    if (inicio == -1) {
        cout << "Vértice inválido!\n";
        return;
    }

    bool* visitado = new bool[qntV]();
    cout << "Percurso DFS a partir de " << rotulos[inicio] << ": ";
    DFS_rec(inicio, mat, qntV, visitado, rotulos);

    for (int i = 0; i < qntV; i++)
        if (!visitado[i]) DFS_rec(i, mat, qntV, visitado, rotulos);

    cout << "\n";
    delete[] visitado;
}

// ---------------- BFS ----------------
template <typename T>
void BFS(int inicio, int** mat, int qntV, bool* visitado, const vector<T>& rotulos) {
    Fila<int> f;
    inicializarFila(f);
    inserirFila(f, inicio);
    visitado[inicio] = true;

    while (!filaVazia(f)) {
        int v; retirarFila(f, v);
        cout << rotulos[v] << " ";
        for (int i = 0; i < qntV; i++)
            if (mat[v][i] == 1 && !visitado[i]) {
                inserirFila(f, i);
                visitado[i] = true;
            }
    }
}

template <typename T>
void executarBFS(int** mat, int qntV, const vector<T>& rotulos) {
    T inicioValor;
    cout << "Digite o vértice inicial para BFS: ";
    cin >> inicioValor;

    int inicio = buscarIndice(rotulos, inicioValor);
    if (inicio == -1) {
        cout << "Vértice inválido!\n";
        return;
    }

    bool* visitado = new bool[qntV]();
    cout << "Percurso BFS a partir de " << rotulos[inicio] << ": ";
    BFS(inicio, mat, qntV, visitado, rotulos);

    for (int i = 0; i < qntV; i++)
        if (!visitado[i]) BFS(i, mat, qntV, visitado, rotulos);

    cout << "\n";
    delete[] visitado;
}

// ---------------- Operações ----------------
template <typename T>
void procurarVertice(const vector<T>& rotulos) {
    T v;
    cout << "Digite o vértice a procurar: ";
    cin >> v;
    if (buscarIndice(rotulos, v) != -1) cout << "O vértice existe no grafo.\n";
    else cout << "O vértice NÃO existe no grafo.\n";
}

template <typename T>
void adicionarAresta(int** mat, int qntV, bool dirigido, const vector<T>& rotulos) {
    T v1Val, v2Val;
    cout << "Insira a aresta (v1 v2): ";
    cin >> v1Val >> v2Val;

    int v1 = buscarIndice(rotulos, v1Val);
    int v2 = buscarIndice(rotulos, v2Val);
    if (v1 == -1 || v2 == -1) { cout << "Vértices inválidos!\n"; return; }
    if (mat[v1][v2] == 1) { cout << "Aresta já existe!\n"; return; }

    mat[v1][v2] = 1;
    if (!dirigido) mat[v2][v1] = 1;
    cout << "Aresta adicionada!\n";
}

template <typename T>
void removerAresta(int** mat, int qntV, bool dirigido, const vector<T>& rotulos) {
    T v1Val, v2Val;
    cout << "Digite os vértices da aresta a remover (v1 v2): ";
    cin >> v1Val >> v2Val;

    int v1 = buscarIndice(rotulos, v1Val);
    int v2 = buscarIndice(rotulos, v2Val);
    if (v1 == -1 || v2 == -1) { cout << "Vértices inválidos!\n"; return; }
    if (mat[v1][v2] == 0) { cout << "Aresta não existe!\n"; return; }

    mat[v1][v2] = 0;
    if (!dirigido) mat[v2][v1] = 0;
    cout << "Aresta removida!\n";
}

// ---------------- Imprimir matriz ----------------
inline void imprimirMatriz(int** mat, int qntV) {
    cout << "\033[1;34m\nMatriz de Adjacência:\033[0m\n";  // título azul e em negrito
    cout << "\033[1;33m====================\033[0m\n";     // linha amarela

    // cabeçalho
    cout << "    ";
    for (int j = 0; j < qntV; j++)
        cout << "\033[1;36m" << j+1 << "\033[0m ";  // índice em ciano
    cout << "\n";

    for (int i = 0; i < qntV; i++) {
        cout << "\033[1;36m" << i+1 << "\033[0m | ";  // índice linha
        for (int j = 0; j < qntV; j++) {
            if (mat[i][j] == 1) cout << "\033[1;32m1\033[0m "; // verde para aresta
            else cout << "\033[1;31m0\033[0m ";                // vermelho para ausência
        }
        cout << "\n";
    }
    cout << "\033[1;33m====================\033[0m\n"; // linha final
}

// ---------------- Adicionar / remover vértices ----------------
inline int** adicionarVertice(int** mat, int& qntV) {
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

inline int** removerVertice(int** mat, int& qntV) {
    if (qntV <= 1) { cout << "Não é possível remover mais vértices.\n"; return mat; }

    int v;
    cout << "Digite o vértice a remover (posição 1 a " << qntV << "): ";
    cin >> v;
    if (v < 1 || v > qntV) { cout << "Vértice inválido!\n"; return mat; }

    int novoV = qntV - 1;
    int** nova = criarMatriz(novoV);
    for (int i = 0, ni = 0; i < qntV; i++) {
        if (i == v-1) continue;
        for (int j = 0, nj = 0; j < qntV; j++) {
            if (j == v-1) continue;
            nova[ni][nj++] = mat[i][j];
        }
        ni++;
    }
    liberarMatriz(mat, qntV);
    qntV = novoV;
    cout << "Vértice removido! Agora são " << qntV << " vértices.\n";
    return nova;
}

// ---------------- Fecho Transitivo ----------------
inline void fechoTransitivoDireto(int** mat, int qntV) {
    int v;
    cout << "Digite o vértice inicial: ";
    cin >> v;
    if (v < 1 || v > qntV) { cout << "Vértice inválido!\n"; return; }
    int inicio = v - 1;
    bool* visitado = new bool[qntV]();
    int* nivel = new int[qntV];
    for (int i = 0; i < qntV; i++) nivel[i] = -1;

    Fila<int> f; inicializarFila(f);
    inserirFila(f, inicio); visitado[inicio] = true; nivel[inicio] = 0;

    cout << "\nFecho transitivo direto do vértice " << v << ":\nVértice (Nível)\n----------------\n";
    while (!filaVazia(f)) {
        int u; retirarFila(f, u);
        cout << u+1 << " (" << nivel[u] << ")\n";
        for (int i = 0; i < qntV; i++)
            if (mat[u][i] == 1 && !visitado[i]) { inserirFila(f,i); visitado[i]=true; nivel[i]=nivel[u]+1; }
    }
    cout << "----------------\n";
    delete[] visitado; delete[] nivel;
}

inline void fechoTransitivoInverso(int** mat, int qntV) {
    int v;
    cout << "Digite o vértice inicial: ";
    cin >> v;
    if (v < 1 || v > qntV) { cout << "Vértice inválido!\n"; return; }
    int inicio = v - 1;
    bool* visitado = new bool[qntV]();
    int* nivel = new int[qntV];
    for (int i = 0; i < qntV; i++) nivel[i] = -1;

    Fila<int> f; inicializarFila(f);
    inserirFila(f, inicio); visitado[inicio]=true; nivel[inicio]=0;

    cout << "\nFecho transitivo inverso do vértice " << v << ":\nVértice (Nível)\n----------------\n";
    while(!filaVazia(f)) {
        int u; retirarFila(f,u);
        cout << u+1 << " (" << nivel[u] << ")\n";
        for(int i=0;i<qntV;i++)
            if(mat[i][u]==1 && !visitado[i]) { inserirFila(f,i); visitado[i]=true; nivel[i]=nivel[u]+1; }
    }
    cout << "----------------\n";
    delete[] visitado; delete[] nivel;
}

// ---------------- Conexidade ----------------
inline bool ehConexoNaoDirigido(int** mat, int qntV) {
    bool* visitado = new bool[qntV]();
    DFS_rec(0, mat, qntV, visitado, vector<string>(qntV,"")); // rótulos irrelevantes
    for(int i=0;i<qntV;i++) if(!visitado[i]) { delete[] visitado; return false; }
    delete[] visitado;
    return true;
}

// ---------------- Componentes Fortemente Conexos (Kosaraju) ----------------
inline int** transporGrafo(int** mat, int qntV) {
    int** trans = criarMatriz(qntV);
    for(int i=0;i<qntV;i++)
        for(int j=0;j<qntV;j++)
            if(mat[i][j]==1) trans[j][i]=1;
    return trans;
}

inline void preencherOrdem(int v, int** mat, int qntV, bool* visitado, vector<int>& pilha) {
    visitado[v]=true;
    for(int i=0;i<qntV;i++)
        if(mat[v][i]==1 && !visitado[i]) preencherOrdem(i, mat, qntV, visitado, pilha);
    pilha.push_back(v);
}

inline void DFS_scc(int v, int** mat, int qntV, bool* visitado, vector<int>& componente) {
    visitado[v]=true;
    componente.push_back(v);
    for(int i=0;i<qntV;i++)
        if(mat[v][i]==1 && !visitado[i]) DFS_scc(i, mat, qntV, visitado, componente);
}

inline void encontrarComponentesFortementeConexos(int** mat, int qntV) {
    bool* visitado = new bool[qntV]();
    vector<int> pilha;
    for(int i=0;i<qntV;i++) if(!visitado[i]) preencherOrdem(i, mat, qntV, visitado, pilha);

    int** trans = transporGrafo(mat,qntV);
    for(int i=0;i<qntV;i++) visitado[i]=false;

    cout << "\nComponentes fortemente conexos:\n";
    while(!pilha.empty()) {
        int v = pilha.back(); pilha.pop_back();
        if(!visitado[v]) {
            vector<int> comp;
            DFS_scc(v, trans, qntV, visitado, comp);
            for(int x: comp) cout << x+1 << " ";
            cout << "\n";
        }
    }
    liberarMatriz(trans,qntV);
    delete[] visitado;
}

#endif // FUNCOES_H
