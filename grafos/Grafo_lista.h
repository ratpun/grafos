#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "Grafo.h"
#include "Vertice.h"
#include <iostream>
#include <string>
#include <fstream>

class Grafo_lista : public Grafo
{
private:
    Vertice **vertices; // indica um array de ponteiros para vértices
public:
    Grafo_lista(int n, bool dir, bool pondArestas, bool pondVertices);
    ~Grafo_lista();
};

#endif
