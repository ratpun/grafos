#ifndef NOARESTA_H
#define NOARESTA_H

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
