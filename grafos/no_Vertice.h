#ifndef NOVERTICE_H
#define NOVERTICE_H

#include "no_Aresta.h"

/**
 * @brief Nó que representa um vértice e sua lista de adjacência.
 */
class NoVertice {
private:
  int idVertice;      ///< Identificador único do vértice
  double pesoVertice; ///< Peso do vértice (caso o grafo seja ponderado nos
                      ///< vértices)
  NoAresta *primeiraAresta;  ///< Ponteiro para a primeira aresta da lista de
                             ///< adjacência
  NoVertice *proximoVertice; ///< Ponteiro para o próximo vértice (lista
                             ///< encadeada de vértices)

public:
  /**
   * @brief Construtor do nó de vértice.
   * @param idVertice ID do vértice
   * @param pesoVertice Peso do vértice (padrão = 1.0)
   */
  NoVertice(int idVertice, double pesoVertice = 1.0)
      : idVertice(idVertice), pesoVertice(pesoVertice), primeiraAresta(nullptr),
        proximoVertice(nullptr) {}

  int getIdVertice() const { return idVertice; }
  double getPesoVertice() const { return pesoVertice; }
  NoAresta *getPrimeiraAresta() const { return primeiraAresta; }
  NoVertice *getProximoVertice() const { return proximoVertice; }

  void setProximoVertice(NoVertice *prox) { proximoVertice = prox; }

  /**
   * @brief Insere uma nova aresta na lista de adjacência deste vértice.
   * @param idDestino ID do vértice de destino da aresta
   * @param peso Peso da aresta
   */
  void insereAresta(int idDestino, double peso) {
    NoAresta *novaAresta = new NoAresta(idDestino, peso);
    novaAresta->setProxima(primeiraAresta);
    primeiraAresta = novaAresta;
  }
};

#endif
