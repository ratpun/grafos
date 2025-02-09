#ifndef GRAFOLISTA_HPP
#define GRAFOLISTA_HPP

#include "Grafo.hpp"
#include "IntList.hpp"
#include "ListaEncadeada.hpp"

// Estrutura para representar uma aresta
struct Aresta {
  int destino;
  int peso;
  Aresta(int d, int p) : destino(d), peso(p) {}
};

// Estrutura para representar um vértice (contém uma lista de arestas)
struct Vertice {
  int id;
  int peso;
  ListaEncadeada<Aresta> *arestas;
  Vertice(int id, int peso) : id(id), peso(peso) {
    arestas = new ListaEncadeada<Aresta>();
  }
  ~Vertice() { delete arestas; }
};

class GrafoLista : public Grafo {
private:
  ListaEncadeada<Vertice *> *vertices; // lista encadeada de vértices
public:
  GrafoLista();
  virtual ~GrafoLista();
  virtual void inserir_vertice(int id, int peso = 0);
  virtual void inserir_aresta(int origem, int destino, int peso = 0);
  virtual IntList get_vizinhos(int vertice) const;
  // Função auxiliar para buscar um vértice pelo id
  Vertice *encontrar_vertice(int id) const;
};

#endif
