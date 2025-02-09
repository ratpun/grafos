#include "../include/GrafoMatriz.hpp"
#include "../include/IntList.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

GrafoMatriz::GrafoMatriz() : pesosVertices(0), matriz(0), currentIndex(0) {}

GrafoMatriz::~GrafoMatriz() {
  if (pesosVertices)
    delete[] pesosVertices;
  if (matriz) {
    for (int i = 0; i < ordem; i++) {
      delete[] matriz[i];
    }
    delete[] matriz;
  }
}

void GrafoMatriz::inserir_vertice(int id, int peso) {
  // Na primeira inserção, aloca os arrays de tamanho "ordem"
  if (currentIndex == 0) {
    pesosVertices = new int[ordem];
    matriz = new int *[ordem];
    for (int i = 0; i < ordem; i++) {
      matriz[i] = new int[ordem];
      for (int j = 0; j < ordem; j++) {
        matriz[i][j] = 0;
      }
    }
  }
  pesosVertices[currentIndex] = peso;
  currentIndex++;
}

void GrafoMatriz::inserir_aresta(int origem, int destino, int peso) {
  int o = origem - 1;
  int d = destino - 1;

  if (origem == destino) {
    cerr << "Erro: laço não permitido (origem == destino).\n";
    return;
  }
  if (matriz[o][d] != 0) {
    cerr << "Erro: aresta já existe (aresta múltipla não permitida).\n";
    return;
  }

  if (o < 0 || o >= ordem || d < 0 || d >= ordem) {
    cerr << "Indices de aresta invalidos.\n";
    return;
  }
  matriz[o][d] = peso;
  if (!direcionado)
    matriz[d][o] = peso;
}

IntList GrafoMatriz::get_vizinhos(int vertice) const {
  IntList lista;
  int idx = vertice - 1;
  if (idx < 0 || idx >= ordem)
    return lista;
  for (int j = 0; j < ordem; j++) {
    if (matriz[idx][j] != 0)
      lista.add(j + 1);
  }
  return lista;
}
