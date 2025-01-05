#ifndef GRAFO_H
#define GRAFO_H


#include <string>
#include <cstring>

using namespace std;

class Grafo
{       
    public:

        int grau;
        int ordem;
        int comp_conexas;
        bool direcionado,V_ponderados,
             A_ponderadas,completo,
             bipartido,arvore,
             A_ponte,V_articulacao;


        void leitorDeGrafo(const string& Path);
};
#endif