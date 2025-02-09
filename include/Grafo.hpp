#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "IntList.hpp"
#include <string>
using namespace std;

class Grafo {
protected:
  int ordem;              // número de vértices
  bool direcionado;       // true se direcionado, false caso contrário
  bool ponderadoVertices; // se os vértices têm peso
  bool ponderadoArestas;  // se as arestas têm peso
public:
  Grafo()
      : ordem(0), direcionado(false), ponderadoVertices(false),
        ponderadoArestas(false) {}
  virtual ~Grafo() {}

  // Funções de acesso
  int get_ordem() const { return ordem; }
  bool eh_direcionado() const { return direcionado; }
  bool vertice_ponderado() const { return ponderadoVertices; }
  bool aresta_ponderada() const { return ponderadoArestas; }

  // Carrega o grafo a partir de um arquivo de texto
  void carrega_grafo(const string &nomeArquivo);
  // Retorna o grau (ou grau máximo) do grafo
  int get_grau() const;
  // Retorna a quantidade de componentes conexas (desconsiderando a direção)
  int n_conexo() const;
  // Informa se o grafo é completo
  bool eh_completo() const;

  // Método virtual que retorna os vizinhos de um vértice (os vértices
  // adjacentes)
  virtual IntList get_vizinhos(int vertice) const = 0;
  // Métodos virtuais para inserir vértices e arestas
  virtual void inserir_vertice(int id, int peso = 0) = 0;
  virtual void inserir_aresta(int origem, int destino, int peso = 0) = 0;
};

#endif
