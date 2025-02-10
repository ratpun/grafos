#ifndef GRAFOMATRIZ_HPP
#define GRAFOMATRIZ_HPP

#include "Grafo.hpp"
#include "IntList.hpp"

class GrafoMatriz : public Grafo {
private:
  int *pesosVertices; // Vetor de pesos dos nós
  int **matriz;       // Matriz de adjacência (capacidade x capacidade)
  int capacidade;     // Capacidade atual (inicialmente 10)
  int nNos;           // Número atual de nós inseridos
  void realocarMatriz(int novaCapacidade);

public:
  GrafoMatriz();
  virtual ~GrafoMatriz();

  virtual void inserir_vertice(int id, int peso = 0) override;
  virtual void inserir_aresta(int origem, int destino, int peso = 0) override;
  virtual IntList get_vizinhos(int vertice) const override;
  virtual double getPesoAresta(int origem, int destino) const override;

  // Funções dinâmicas:
  void novo_no(int peso = 0);
  void nova_aresta(int origem, int destino, int peso);
  void deleta_no(int id) override;
  void deleta_aresta(int origem, int destino) override;
};

#endif
