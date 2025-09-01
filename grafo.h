#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
using namespace std;

int** criarMatriz(int qntV) {
    int** mat = new int*[qntV];
    for (int i = 0; i < qntV; i++) {
        mat[i] = new int[qntV]();
    }
    return mat;
}

void liberarMatriz(int** mat, int qntV) {
    for (int i = 0; i < qntV; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

bool verificarAresta(int** mat, int qntV, int v1, int v2) {
    if (v1 < 1 || v1 > qntV || v2 < 1 || v2 > qntV) return false;
    return mat[v1-1][v2-1] == 1;
}

void inserirConexoes(int** mat, int qntV, bool dirigido) {
    int v1, v2, insere = 1;
    while (insere != 0) {
        cout << "Insira a conexão (v1 -> v2):\n";
        cout << "v1: "; cin >> v1;
        cout << "v2: "; cin >> v2;

        if (v1 < 1 || v1 > qntV || v2 < 1 || v2 > qntV) {
            cout << "Vértices inválidos!\n";
        } else if (verificarAresta(mat, qntV, v1, v2)) {
            cout << "Essa aresta já existe!\n";
        } else {
            mat[v1-1][v2-1] = 1;
            if (!dirigido) mat[v2-1][v1-1] = 1;
            cout << "Aresta adicionada!\n";
        }

        cout << "Deseja inserir outra conexão? (1=Sim, 0=Não): ";
        cin >> insere;
    }
}

void imprimirMatriz(int** mat, int qntV) {
    cout << "\nMatriz de Adjacência:\n";
    cout << "====================\n";
    for (int i = 0; i < qntV; i++) {
        for (int j = 0; j < qntV; j++) {
            if (mat[i][j] == 1) cout << "\033[1;32m" << mat[i][j] << " "; // verde
            else cout << "\033[1;35m" << mat[i][j] << " ";               // magenta
        }
        cout << "\033[0m" << endl; // reset
    }
    cout << "====================\n";
}

#endif
