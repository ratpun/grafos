#include "Grafo_lista.h"

Grafo_lista::Grafo_lista(int n, bool dir, bool pondArestas, bool pondVertices)
{
    direcionado = dir;
    arestas_ponderadas = pondArestas;
    vertices_ponderados = pondVertices;
    numNos = n;

    vertices = new Vertice *[numNos];
    for (int i = 0; i < numNos; ++i)
    {
        vertices[i] = nullptr;
    }
}

Grafo_lista::~Grafo_lista()
{
    for (int i = 0; i < numNos; ++i)
    {
        delete vertices[i];
    }
    delete[] vertices;
}
