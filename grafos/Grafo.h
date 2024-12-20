#include <iostream>
#include <string>
#include <fstream>


class Grafo
{
protected:
    int numNos = 0; // Indica o número de nós do grafo
    bool direcionado = false; // Indica se o grafo é direcionado
    bool arestas_ponderadas = false; // Indica se as arestas do grafo são ponderadas
    bool vertices_ponderados = false; // Indica se os vértices do grafo são ponderados

public:
    Grafo() = default;
    virtual ~Grafo() = default;
    virtual void imprimir();
    virtual bool eh_bipartido();
    virtual int n_conexo();
    virtual int get_grau(int no);
    virtual int get_ordem();
    virtual bool eh_direcionado();
    virtual bool vertice_ponderado();
    virtual bool aresta_ponderada();
    virtual bool eh_completo();
    virtual bool eh_arvore();
    virtual bool possui_articulacao();
    virtual bool possui_ponte();
    virtual Grafo* carrega_grafo(std::string &filename); // Não tenho certeza se o retorno esta correto
    virtual Grafo* novo_grafo(std::string &filename); // Não tenho certeza se o retorno esta correto
};