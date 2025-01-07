#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "Grafo.h"
#include "Vertice.h"
#include "no_Vertice.h"
#include <fstream>
#include <iostream>
#include <string>

class Grafo_lista : public Grafo {
private:
  NoVertice *primeiroVertice; ///< Ponteiro para o primeiro vértice da lista
  int numVertices;            ///< Número de vértices (ordem do grafo)
  int numArestas;             ///< Número de arestas
  bool direcionado;           ///< Flag que indica se o grafo é direcionado
  bool verticesPonderados;    ///< Flag que indica se os vértices têm peso
  bool arestasPonderadas;     ///< Flag que indica se as arestas têm peso

public:
  Grafo_lista();
  ~Grafo_lista();
};

#endif
