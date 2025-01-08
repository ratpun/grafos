#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "Grafo.h"
#include "no_Vertice.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

/**
 * @class Grafo_lista
 * @brief Classe que representa um grafo utilizando listas de adjacência.
 * 
 * A classe Grafo_lista herda da classe base Grafo e implementa um grafo utilizando listas de adjacência.
 * Ela fornece métodos para carregar, manipular e analisar grafos.
 * 
 * @details
 * A classe contém uma estrutura interna NoLista que representa um nó na lista de adjacência.
 * Cada nó contém o ID do vértice e um ponteiro para o próximo nó na lista.
 * 
 * A classe também contém vários métodos para manipulação e análise do grafo, incluindo:
 * - Carregar um grafo a partir de um arquivo.
 * - Criar um novo grafo.
 * - Limpar o grafo.
 * - Verificar se o grafo é bipartido.
 * - Obter o grau do grafo.
 * - Verificar se o grafo é direcionado.
 * - Verificar se os vértices ou arestas são ponderados.
 * - Obter o número de componentes conexas.
 * - Obter a ordem do grafo.
 * - Verificar se o grafo é completo.
 * - Verificar se o grafo é uma árvore.
 * - Verificar se o grafo possui articulações ou pontes.
 * - Realizar buscas em profundidade (DFS) para várias finalidades, como marcar componentes, detectar ciclos, etc.
 * 
 * @note
 * A classe utiliza várias variáveis privadas para armazenar informações sobre o grafo, como o primeiro vértice,
 * número de nós, pesos dos nós, se o grafo é direcionado, se os vértices ou arestas são ponderados, número de arestas,
 * se os vértices foram visitados, componentes, número de componentes, etc.
 * 
 * @see Grafo
 * @see NoVertice
 */

class Grafo_lista : public Grafo
{
private:
    struct NoLista
    {
        int idVertice;
        NoLista *proximo;

        NoLista(int id) : idVertice(id), proximo(nullptr) {}
    };

    NoVertice *primeiroVertice;
    int numNos;
    float *pesoNos;
    bool direcionado;
    bool verticesPonderados;
    bool arestasPonderadas;
    int numArestas;
    bool *visitado;
    int *componentes;
    int numComponentes;
    bool existeAresta(int origem, int destino);
    void liberarLista(NoLista *lista);

public:
    Grafo_lista();
    ~Grafo_lista();
    void carrega_grafo(const std::string &arquivo);
    void novo_grafo(const std::string &descricao, const std::string &arquivoSaida);
    void limpaGrafo();
    bool eh_bipartido();
    int get_grau();
    bool eh_direcionado();
    bool vertice_ponderado();
    bool aresta_ponderada();
    int n_conexo();
    int get_ordem();
    bool eh_completo();
    bool eh_arvore();
    bool possui_articulacao();
    bool possui_ponte();
    void dfs_marcar_componente(int idVertice, bool visitado[]);
    void dfs_articulacao(int u, int &tempo, int disc[], int low[], bool visitado[], int pai[], bool articulacao[], int &filhosRaiz);
    bool dfs_ponte(int u, int &tempo, int disc[], int low[], bool visitado[], int *pai);
    bool tem_ciclo();
    NoLista *getVizinhosIgnorandoDirecao(int idVertice);
    NoVertice *encontraVertice(int id);
    void insereVertice(int id, double peso);
    void insereAresta(int origem, int destino, double peso);
    bool dfs_detecta_ciclo(int idVertice, bool visitado[], int pai);
};

#endif
