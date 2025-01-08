#ifndef NOARESTA_H
#define NOARESTA_H

/**
 * @file no_Aresta.h
 * @brief Definição da classe NoAresta.
 */

/**
 * @class NoAresta
 * @brief Representa um nó de aresta em um grafo.
 *
 * Esta classe encapsula as propriedades e comportamentos de um nó de aresta,
 * incluindo o ID do vértice ao qual se conecta, o peso da aresta e um ponteiro
 * para o próximo nó de aresta na lista de adjacência.
 */

class NoAresta
{
private:
  int idVertice;
  double pesoAresta;
  NoAresta *proxima;

public:
  NoAresta(int idVertice, double pesoAresta = 1.0)
      : idVertice(idVertice), pesoAresta(pesoAresta), proxima(nullptr) {}

  int getIdVertice() const { return idVertice; }
  double getPesoAresta() const { return pesoAresta; }
  NoAresta *getProxima() const { return proxima; }

  void setProxima(NoAresta *prox) { proxima = prox; }
};

#endif
