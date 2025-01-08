/**
 * @file no_Vertice.h
 * @brief Definição da classe NoVertice.
 */

#ifndef NOVERTICE_H
#define NOVERTICE_H

#include "no_Aresta.h"

/**
 * @class NoVertice
 * @brief Representa um vértice em um grafo.
 */
class NoVertice {
private:
  int idVertice;
  double pesoVertice;

  NoAresta *primeiraAresta;

  NoVertice *proximoVertice;

public:
  /**
   * @brief Constrói um novo vértice.
   * @param idVertice O ID do vértice.
   * @param pesoVertice O peso do vértice (padrão é 1.0).
   */
  NoVertice(int idVertice, double pesoVertice = 1.0)
      : idVertice(idVertice), pesoVertice(pesoVertice), primeiraAresta(nullptr),
        proximoVertice(nullptr) {}

  /**
   * @brief Obtém o ID do vértice.
   * @return O ID do vértice.
   */
  int getIdVertice() const { return idVertice; };

  /**
   * @brief Obtém o peso do vértice.
   * @return O peso do vértice.
   */
  double getPesoVertice() const { return pesoVertice; };

  /**
   * @brief Obtém a primeira aresta conectada a este vértice.
   * @return Ponteiro para a primeira aresta.
   */
  NoAresta *getPrimeiraAresta() const { return primeiraAresta; };

  /**
   * @brief Obtém o próximo vértice na lista.
   * @return Ponteiro para o próximo vértice.
   */
  NoVertice *getProximoVertice() const { return proximoVertice; };

  /**
   * @brief Define o próximo vértice na lista.
   * @param prox Ponteiro para o próximo vértice.
   */
  void setProximoVertice(NoVertice *prox) { proximoVertice = prox; };

  /**
   * @brief Insere uma nova aresta conectada a este vértice.
   * @param idDestino O ID do vértice de destino.
   * @param peso O peso da aresta.
   */
  void insereAresta(int idDestino, double peso) {
    NoAresta *novaAresta = new NoAresta(idDestino, peso);
    novaAresta->setProxima(primeiraAresta);
    primeiraAresta = novaAresta;
  };
};

#endif
