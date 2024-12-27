#ifndef NOVERTICE_H
#define NOVERTICE_H

#include "no_Aresta.h"

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
  NoVertice(int idVertice, double pesoVertice = 1.0)
      : idVertice(idVertice), pesoVertice(pesoVertice), primeiraAresta(nullptr),
        proximoVertice(nullptr) {}

  int getIdVertice() const { return idVertice; }
  double getPesoVertice() const { return pesoVertice; }
  NoAresta *getPrimeiraAresta() const { return primeiraAresta; }
  NoVertice *getProximoVertice() const { return proximoVertice; }

  void setProximoVertice(NoVertice *prox) { proximoVertice = prox; }

  void insereAresta(int idDestino, double peso) {
    NoAresta *novaAresta = new NoAresta(idDestino, peso);
    novaAresta->setProxima(primeiraAresta);
    primeiraAresta = novaAresta;
  }
};

#endif
