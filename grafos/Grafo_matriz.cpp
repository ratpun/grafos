#include "Grafo_matriz.h"

Grafo_matriz::Grafo_matriz(int n, bool dir, bool pondArestas, bool pondVertices) {
    numNos = n;
    direcionado = dir;
    arestas_ponderadas = pondArestas;
    vertices_ponderados = pondVertices;

    matriz = new int*[numNos];
    for (int i = 0; i < numNos; ++i) {
        matriz[i] = new int[numNos];
        for (int j = 0; j < numNos; ++j) {
            matriz[i][j] = 0;
        }
    }
}

Grafo_matriz::~Grafo_matriz() {
    for (int i = 0; i < numNos; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
