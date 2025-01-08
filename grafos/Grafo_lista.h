#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "Grafo.h"
#include "no_Vertice.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

// Definição da classe Grafo_lista que herda de Grafo
class Grafo_lista : public Grafo {
private:
    // Estrutura que representa um nó da lista de adjacências
    struct NoLista {
        int idVertice; // ID do vértice
        NoLista* proximo; // Ponteiro para o próximo nó

        NoLista(int id) : idVertice(id), proximo(nullptr) {} // Construtor do nó
    };

    NoVertice* primeiroVertice; // Ponteiro para o primeiro vértice da lista de vértices
    int numNos; // Número de vértices no grafo
    float* pesoNos; // Vetor de peso para os vértices
    bool direcionado; // Indica se o grafo é direcionado
    bool verticesPonderados; // Indica se os vértices têm peso
    bool arestasPonderadas; // Indica se as arestas têm peso
    int numArestas; // Número de arestas no grafo
    bool* visitado; // Vetor que indica se um vértice foi visitado durante a busca
    int* componentes; // Vetor que armazena os componentes conexos do grafo
    int numComponentes; // Número de componentes conexos

    // Função para verificar a existência de uma aresta entre dois vértices
    bool existeAresta(int origem, int destino);

    // Função para liberar a memória da lista de vizinhos de um vértice
    void liberarLista(NoLista* lista);

public:
    // Construtor do grafo
    Grafo_lista();

    // Destrutor do grafo
    ~Grafo_lista();

    // Carrega o grafo a partir de um arquivo
    void carrega_grafo(const std::string& arquivo);

    // Cria um novo grafo a partir de uma descrição e um arquivo de saída
    void novo_grafo(const std::string& descricao, const std::string& arquivoSaida);

    // Limpa o grafo, liberando a memória
    void limpaGrafo();

    // Verifica se o grafo é bipartido
    bool eh_bipartido();

    // Obtém o grau do grafo
    int get_grau();

    // Verifica se o grafo é direcionado
    bool eh_direcionado();

    // Verifica se os vértices são ponderados
    bool vertice_ponderado();

    // Verifica se as arestas são ponderadas
    bool aresta_ponderada();

    // Retorna o número de componentes conexos no grafo
    int n_conexo();

    // Retorna a ordem do grafo (número de vértices)
    int get_ordem();

    // Verifica se o grafo é completo
    bool eh_completo();

    // Verifica se o grafo é uma árvore
    bool eh_arvore();

    // Verifica se o grafo possui articulações (pontos de separação)
    bool possui_articulacao();

    // Verifica se o grafo possui pontes (arestas de corte)
    bool possui_ponte();

    // Função de busca em profundidade para marcar componentes conectados
    void dfs_marcar_componente(int idVertice, bool visitado[]);

    // Função para identificar articulações
    void dfs_articulacao(int u, int& tempo, int disc[], int low[], bool visitado[], int pai[], bool articulacao[], int& filhosRaiz);

    // Função DFS para identificar pontes (arestas de corte)
    bool dfs_ponte(int u, int& tempo, int disc[], int low[], bool visitado[], int* pai);

    // Verifica se o grafo tem ciclos
    bool tem_ciclo();

    // Obtém os vizinhos de um vértice ignorando a direção das arestas
    NoLista* getVizinhosIgnorandoDirecao(int idVertice);

    // Encontra um vértice dado o seu ID
    NoVertice* encontraVertice(int id);

    // Insere um novo vértice no grafo com um peso especificado
    void insereVertice(int id, double peso);

    // Insere uma aresta entre dois vértices com um peso especificado
    void insereAresta(int origem, int destino, double peso);

    // Função DFS para detectar ciclos no grafo
    bool dfs_detecta_ciclo(int idVertice, bool visitado[], int pai);
};

#endif // GRAFO_LISTA_H
