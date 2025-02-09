#ifndef GRAFOMATRIZ_HPP
#define GRAFOMATRIZ_HPP

#include "Grafo.hpp"

class GrafoMatriz : public Grafo {
private:
  int *pesosVertices; // vetor de pesos dos vértices
  int **matriz; // matriz de adjacência (valores 0 indicam ausência de aresta)
  int currentIndex; // conta quantos vértices foram inseridos
public:
  GrafoMatriz();
  virtual ~GrafoMatriz();
  virtual void inserir_vertice(int id, int peso = 0);
  virtual void inserir_aresta(int origem, int destino, int peso = 0);
  virtual IntList get_vizinhos(int vertice) const;
};

#endif
