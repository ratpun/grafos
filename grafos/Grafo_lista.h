#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "Grafo.h"
#include "no_Vertice.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

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
