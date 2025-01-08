#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

class Grafo_matriz : public Grafo
{
private:
    int numNos;
    float *pesoNos;
    bool direcionado;
    bool verticesPonderados;
    bool arestasPonderadas;
    double **matriz;
    int numArestas;
    bool *visitado;
    int *componentes;
    int numComponentes;

public:
    Grafo_matriz(int n, bool dir, bool pondArestas, bool pondVertices);
    ~Grafo_matriz();
    void insereVertice(int id, double peso);
    void adicionaAresta(int origem, int destino, double peso);
    bool existeAresta(int origem, int destino);
    void carrega_grafo(const std::string &arquivo);
    void novo_grafo(const std::string &descricao, const std::string &arquivoSaida);
    void limpaGrafo();
    bool eh_bipartido();
    bool eh_arvore();
    int n_conexo();
    void dfs(int vertice, bool *visitado);
    bool eh_completo();
    bool possui_ponte();
    bool aresta_ponderada();
    bool vertice_ponderado();
    bool eh_direcionado();
    int get_grau();
    int get_ordem();
};

#endif