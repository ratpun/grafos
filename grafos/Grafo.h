#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief Classe base para o grafo
 * 
 */

class Grafo
{
protected:
  int numNos = 0;           /// Indica o número de nós do grafo
  bool direcionado = false; /// Indica se o grafo é direcionado
  bool arestas_ponderadas =
      false; /// Indica se as arestas do grafo são ponderadas
  bool vertices_ponderados =
      false; /// Indica se os vértices do grafo são ponderados

public:
  Grafo() = default;
  virtual ~Grafo() = default;
  ///   virtual void imprimir();
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
