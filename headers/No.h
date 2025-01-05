#ifndef NO_H
#define NO_H

#include <vector>

#include "Aresta.h"

using namespace std;

class No
{
    public:
       int            id;
       int            peso;
       vector<Aresta*> Arestas;
};
#endif