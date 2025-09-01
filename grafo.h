#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
using namespace std;

// Estrutura de grafo genérico
template <typename T>
struct Grafo {
    int qntV;                // quantidade de vértices
    bool dirigido;           // se é dirigido ou não
    int** mat;               // matriz de adjacência
    vector<T> rotulos;       // rótulos dos vértices
};

// Função para criar matriz dinâmica
inline int** criarMatriz(int qntV) {
    int** mat = new int*[qntV];
    for (int i = 0; i < qntV; i++) {
        mat[i] = new int[qntV]();
    }
    return mat;
}

// Função para liberar matriz
inline void liberarMatriz(int** mat, int qntV) {
    for (int i = 0; i < qntV; i++) delete[] mat[i];
    delete[] mat;
}

#endif // GRAFO_H
