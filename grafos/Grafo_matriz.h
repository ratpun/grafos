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
    int numNos;              // Número de vértices no grafo
    bool direcionado;        // Flag para indicar se o grafo é direcionado
    bool verticesPonderados; // Flag para indicar se os vértices têm peso
    bool arestasPonderadas;  // Flag para indicar se as arestas têm peso
    double **matriz;         // Matriz de adjacência para representar as arestas e pesos
    int numArestas;          // Número de arestas no grafo
    bool *visitado;          // Vetor de visitados para busca em profundidade
    int *componentes;        // Vetor de componentes conexos
    int numComponentes;      // Número de componentes conexos
    int numVertices;         // Número de vértices no grafo

public:
    // Construtor
    Grafo_matriz(int n, bool dir, bool pondArestas, bool pondVertices);

    // Destruidor
    ~Grafo_matriz();

    // Insere um vértice com um peso específico
    void insereVertice(int id, double peso);

    // Adiciona uma aresta entre dois vértices com um peso
    void adicionaAresta(int origem, int destino, double peso);

    // Verifica se existe uma aresta entre dois vértices
    bool existeAresta(int origem, int destino);

    // Carrega o grafo a partir de um arquivo
    void carrega_grafo(const std::string &arquivo);

    // Cria um novo grafo a partir de uma descrição
    void novo_grafo(const std::string &descricao, const std::string &arquivoSaida);

    // Limpa qualquer dado antigo
    void limpaGrafo();

    // Verifica se o grafo é bipartido
    bool eh_bipartido();

    // Verifica se o grafo é árvore ou não
    bool eh_arvore();

    // Verifica o número de componentes conexos
    int n_conexo();

    // Realiza a marcação de componentes visitados
    void dfs(int vertice, bool *visitado);

    // Verifica se o grafo é completo ou não
    bool eh_completo();

    // Verifica se o grafo possui ponte
    bool possui_ponte();

    // Verifica se as arestas do grafo são ponderadas
    bool aresta_ponderada();

    // Verifica se os vértices do grafo são ponderados
    bool vertice_ponderado();
};

#endif // GRAFO_MATRIZ_H