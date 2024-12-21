#ifndef ARESTA_H
#define ARESTA_H

class Aresta {
public:
    int destino; // indica o vértice de destino
    int peso;    // indica o peso da aresta
    Aresta* prox; // indica o ponteiro para a próxima aresta

    Aresta(int d, int p) : destino(d), peso(p), prox(nullptr) {}
    ~Aresta() = default;
};

#endif
