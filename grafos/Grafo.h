#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <iostream>
#include <string>

class Grafo
{
protected:
  int numNos = 0;
  bool direcionado = false;
  bool arestas_ponderadas =
      false;
  bool vertices_ponderados =
      false;

public:
  Grafo() = default;
  virtual ~Grafo() = default;

  virtual bool eh_bipartido() = 0;
  virtual int n_conexo() = 0;
  virtual int get_grau() = 0;
  virtual int get_ordem() = 0;
  virtual bool eh_direcionado() = 0;
  virtual bool vertice_ponderado() = 0;
  virtual bool aresta_ponderada() = 0;
  virtual bool eh_completo() = 0;
  virtual bool eh_arvore() = 0;
  virtual bool possui_articulacao() = 0;
  virtual bool possui_ponte() = 0;
  virtual void carrega_grafo(const std::string &arquivo) = 0;
  virtual void novo_grafo(const std::string &descricao,
                          const std::string &arquivoSaida) = 0;
};

#endif
