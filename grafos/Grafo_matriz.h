#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

class Grafo_matriz : public Grafo {
private:
    int** matriz; // indica a matriz de adjacência
public:
    Grafo_matriz(int n, bool dir, bool pondArestas, bool pondVertices);
    ~Grafo_matriz();
    void adicionarAresta(Vertice* vertice);
    void imprimirMatriz();
    bool verificarAresta (int origem, int destino);
    void removerAresta (int origem, int destino);   
    void limparGrafo();
    void verificarLigacoes(int x);
    bool verificarLigacao(int x, int y);
};

#endif
