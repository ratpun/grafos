#ifndef VERTICE_H
#define VERTICE_H

#include "Aresta.h"

class Vertice {
public:
    int id;          // indica o ID único do vértice
    Aresta* arestas; // indica o ponteiro para a cabeça da lista de arestas

    Vertice(int i) : id(i), arestas(nullptr) {}
    ~Vertice() {
        Aresta* atual = arestas;
        while (atual != nullptr) {
            Aresta* temp = atual;
            atual = atual->prox;
            delete temp;
        }
    }
};

#endif 
