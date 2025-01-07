#ifndef NOARESTA_H
#define NOARESTA_H

/**
 * @brief Classe que representa uma aresta de um grafo
 * 
 */

class NoAresta {
private:
  int idVertice;     /// ID do vértice de destino
  double pesoAresta; /// Peso da aresta (caso seja ponderada)
  NoAresta *proxima; /// Ponteiro para a próxima aresta

public:
  NoAresta(int idVertice, double pesoAresta = 1.0)
      : idVertice(idVertice), pesoAresta(pesoAresta), proxima(nullptr) {}

  int getIdVertice() const { return idVertice; }
  double getPesoAresta() const { return pesoAresta; }
  NoAresta *getProxima() const { return proxima; }

  void setProxima(NoAresta *prox) { proxima = prox; }
};

#endif
