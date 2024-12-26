#ifndef NOARESTA_H
#define NOARESTA_H

/**
 * @brief Nó que representa uma aresta em uma lista de adjacência.
 */
class NoAresta {
private:
  int idVertice;     ///< ID do vértice de destino
  double pesoAresta; ///< Peso da aresta (caso seja ponderada)
  NoAresta *proxima; ///< Ponteiro para a próxima aresta

public:
  /**
   * @brief Construtor do nó de aresta.
   * @param idVertice ID do vértice destino desta aresta
   * @param pesoAresta Peso da aresta (padrão = 1.0)
   */
  NoAresta(int idVertice, double pesoAresta = 1.0)
      : idVertice(idVertice), pesoAresta(pesoAresta), proxima(nullptr) {}

  int getIdVertice() const { return idVertice; }
  double getPesoAresta() const { return pesoAresta; }
  NoAresta *getProxima() const { return proxima; }

  void setProxima(NoAresta *prox) { proxima = prox; }
};

#endif
