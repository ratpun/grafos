#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

#include "Grafo.h"

using namespace std;

void Grafo::leitorDeGrafo(const string& Path)
{
    ifstream GrafoFile(Path);

    if(!GrafoFile.is_open())
    {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    string linha;
    getline(GrafoFile, linha);
    istringstream ss(linha);
    string token;

    getline(ss, token, ' ');
    ordem = stoi(token);

    getline(ss, token, ' ');


}