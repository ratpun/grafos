#ifndef NOVERTICE_H
#define NOVERTICE_H

#include "no_Aresta.h"

class NoVertice
{
private:
  int idVertice;
  double pesoVertice;

  NoAresta *primeiraAresta;

  NoVertice *proximoVertice;

public:
  NoVertice(int idVertice, double pesoVertice = 1.0)
      : idVertice(idVertice), pesoVertice(pesoVertice), primeiraAresta(nullptr),
        proximoVertice(nullptr) {}

  int getIdVertice() const { return idVertice; }
  double getPesoVertice() const { return pesoVertice; }
  NoAresta *getPrimeiraAresta() const { return primeiraAresta; }
  NoVertice *getProximoVertice() const { return proximoVertice; }

  void setProximoVertice(NoVertice *prox) { proximoVertice = prox; }

  void insereAresta(int idDestino, double peso)
  {
    NoAresta *novaAresta = new NoAresta(idDestino, peso);
    novaAresta->setProxima(primeiraAresta);
    primeiraAresta = novaAresta;
  }
};

#endif
