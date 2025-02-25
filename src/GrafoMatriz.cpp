#include "../include/GrafoMatriz.hpp"
#include "../include/IntList.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

const double INF = 1e9;

GrafoMatriz::GrafoMatriz()
    : pesosVertices(nullptr), matriz(nullptr), capacidade(10), nNos(0) {
  // Aloca o vetor de pesos e o array de ponteiros para as linhas da matriz
  pesosVertices = new int[capacidade];
  matriz = new int *[capacidade];
  // Inicializa todas as linhas como nullptr (para evitar acessos indevidos)
  for (int i = 0; i < capacidade; i++) {
    matriz[i] = nullptr;
  }
}

GrafoMatriz::~GrafoMatriz() {
  // Libera todas as linhas alocadas
  for (int i = 0; i < nNos; i++) {
    if (matriz[i] != nullptr) {
      delete[] matriz[i];
    }
  }
  delete[] matriz;
  delete[] pesosVertices;
}

void GrafoMatriz::inserir_vertice(int id, int peso) {
  (void)id;
  novo_no(peso);
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

  if (o < 0 || o >= nNos || d < 0 || d >= nNos) {
    cerr << "Indices de aresta invalidos." << endl;
    return;
  }
  matriz[o][d] = peso;
  if (!direcionado)
    matriz[d][o] = peso;
}

IntList GrafoMatriz::get_vizinhos(int vertice) const {
  IntList lista;
  int idx = vertice - 1;
  if (idx < 0 || idx >= nNos)
    return lista;
  for (int j = 0; j < nNos; j++) {
    if (matriz[idx][j] != 0)
      lista.add(j + 1);
  }
  return lista;
}

void GrafoMatriz::realocarMatriz(int novaCapacidade) {
  // Cria novo vetor de pesos e nova matriz
  int *novoPesos = new int[novaCapacidade];
  int **novaMatriz = new int *[novaCapacidade];
  for (int i = 0; i < novaCapacidade; i++) {
    novaMatriz[i] = nullptr;
  }
  // Copia os dados dos nós já inseridos
  for (int i = 0; i < nNos; i++) {
    novoPesos[i] = pesosVertices[i];
    // Aloca uma nova linha com novaCapacidade colunas
    novaMatriz[i] = new int[novaCapacidade];
    // Copia os valores existentes para as colunas de 0 a nNos-1
    for (int j = 0; j < nNos; j++) {
      novaMatriz[i][j] = matriz[i][j];
    }
    // Inicializa as colunas restantes com 0
    for (int j = nNos; j < novaCapacidade; j++) {
      novaMatriz[i][j] = 0;
    }
  }
  // Libera a matriz e o vetor de pesos antigos
  for (int i = 0; i < nNos; i++) {
    if (matriz[i] != nullptr) {
      delete[] matriz[i];
    }
  }
  delete[] matriz;
  delete[] pesosVertices;
  // Atualiza os ponteiros e a capacidade
  matriz = novaMatriz;
  pesosVertices = novoPesos;
  capacidade = novaCapacidade;
}

void GrafoMatriz::novo_no(int peso) {
  if (nNos >= capacidade) {
    realocarMatriz(capacidade * 2);
  }
  // Aloca a linha para o novo nó se ainda não foi alocada
  if (matriz[nNos] == nullptr) {
    matriz[nNos] = new int[capacidade];
    for (int j = 0; j < capacidade; j++) {
      matriz[nNos][j] = 0;
    }
  }
  pesosVertices[nNos] = peso;
  // Inicializa, para cada nó já inserido, a coluna do novo nó com 0
  for (int i = 0; i < nNos; i++) {
    matriz[i][nNos] = 0;
  }
  nNos++;
  // Observe: NÃO atualizamos a variável "ordem" aqui,
  // pois a ordem já foi definida no carregamento do grafo.
}

void GrafoMatriz::nova_aresta(int origem, int destino, int peso) {
  // Validação para impedir laço e aresta múltipla
  if (origem == destino) {
    cerr << "Erro: Laço não permitido." << endl;
    return;
  }
  int o = origem - 1;
  int d = destino - 1;
  if (o < 0 || o >= nNos || d < 0 || d >= nNos) {
    cerr << "Erro: Vértice inexistente." << endl;
    return;
  }
  if (matriz[o][d] != 0) {
    cerr << "Erro: Aresta já existe." << endl;
    return;
  }
  matriz[o][d] = peso;
  if (!direcionado)
    matriz[d][o] = peso;
}

void GrafoMatriz::deleta_no(int id) {
  int index = id - 1; // Convertendo para índice 0-based
  if (index < 0 || index >= nNos) {
    cerr << "Erro: Vértice " << id << " não existe." << endl;
    return;
  }

  int newSize = nNos - 1; // Novo número de nós

  // Aloca nova matriz para os nós remanescentes
  int **novaMatriz = new int *[capacidade]; // mantemos a mesma capacidade
  for (int i = 0; i < newSize; i++) {
    novaMatriz[i] = new int[capacidade];
    // Inicializa as colunas (usaremos apenas 0 até newSize-1; o restante pode
    // ser 0 também)
    for (int j = 0; j < capacidade; j++) {
      novaMatriz[i][j] = 0;
    }
  }

  // Aloca novo vetor de pesos
  int *novoPesos = new int[capacidade];

  // Copia os dados da matriz antiga, pulando a linha e coluna do nó removido
  int newRow = 0;
  for (int i = 0; i < nNos; i++) {
    if (i == index)
      continue; // Pula a linha que será removida
    int newCol = 0;
    for (int j = 0; j < nNos; j++) {
      if (j == index)
        continue; // Pula a coluna que será removida
      novaMatriz[newRow][newCol] = matriz[i][j];
      newCol++;
    }
    novoPesos[newRow] = pesosVertices[i];
    newRow++;
  }

  // Libera a memória da matriz antiga e do vetor de pesos antigo
  for (int i = 0; i < nNos; i++) {
    if (matriz[i] != nullptr) {
      delete[] matriz[i];
    }
  }
  delete[] matriz;
  delete[] pesosVertices;

  // Atualiza os ponteiros e o contador de nós
  matriz = novaMatriz;
  pesosVertices = novoPesos;
  nNos = newSize;
  ordem = newSize; // A ordem passa a ser o novo número de nós
}

void GrafoMatriz::deleta_aresta(int origem, int destino) {
  int o = origem - 1;
  int d = destino - 1;
  if (o < 0 || o >= nNos || d < 0 || d >= nNos) {
    cerr << "Indices de aresta invalidos." << endl;
    return;
  }
  matriz[o][d] = 0;
  if (!direcionado)
    matriz[d][o] = 0;
}

double GrafoMatriz::getPesoAresta(int origem, int destino) const {
  int o = origem - 1;
  int d = destino - 1;
  if (o < 0 || o >= nNos || d < 0 || d >= nNos)
    return INF;
  if (matriz[o][d] == 0)
    return INF;
  return (double)matriz[o][d];
}

void GrafoMatriz::imprime_grafo() const {
  std::cout << "Grafo (Matriz de Adjacência):" << std::endl;
  std::cout << "Ordem: " << ordem << std::endl;
  // Itera pelos nós (usando nNos como o número atual de nós inseridos)
  for (int i = 0; i < nNos; i++) {
    std::cout << "Vértice " << (i + 1);
    // Se o grafo for ponderado, mostre o peso do vértice
    if (ponderadoVertices)
      std::cout << " (peso: " << pesosVertices[i] << ")";
    std::cout << " -> ";
    // Lista os vizinhos e o peso da aresta (se ponderada)
    bool temVizinhos = false;
    for (int j = 0; j < nNos; j++) {
      if (matriz[i][j] != 0) {
        std::cout << (j + 1);
        if (ponderadoArestas)
          std::cout << " (peso: " << matriz[i][j] << ")";
        std::cout << " ";
        temVizinhos = true;
      }
    }
    if (!temVizinhos)
      std::cout << "Sem vizinhos";
    std::cout << std::endl;
  }
}
