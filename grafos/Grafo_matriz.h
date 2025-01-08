#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "Grafo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

/**
 * @class Grafo_matriz
 * @brief Uma classe que representa um grafo usando uma matriz de adjacência.
 * 
 * Esta classe herda da classe Grafo e fornece funcionalidades para gerenciar
 * e manipular um grafo representado por uma matriz de adjacência. Suporta grafos
 * direcionados e não direcionados, bem como vértices e arestas ponderados.
 * 
 * @details
 * A classe Grafo_matriz inclui métodos para inserir vértices, adicionar arestas,
 * verificar a existência de arestas, carregar um grafo a partir de um arquivo,
 * criar um novo grafo, limpar o grafo e várias outras operações relacionadas ao
 * grafo, como verificar se o grafo é bipartido, uma árvore ou completo, e encontrar
 * o número de componentes conectados.
 * 
 * @note
 * - O grafo pode ser direcionado ou não direcionado.
 * - Os vértices e arestas podem ser ponderados ou não ponderados.
 * 
 * @see Grafo
 */

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