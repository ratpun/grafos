#include "../include/Grafo.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

// Carrega o grafo a partir do arquivo
void Grafo::carrega_grafo(const std::string &nomeArquivo) {
  std::ifstream arquivo(nomeArquivo.c_str());
  if (!arquivo) {
    std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << "\n";
    return;
  }
  arquivo >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;

  // Insere os vértices
  if (ponderadoVertices) {
    for (int i = 1; i <= ordem; i++) {
      int peso;
      arquivo >> peso;
      inserir_vertice(i, peso);
    }
  } else {
    for (int i = 1; i <= ordem; i++) {
      inserir_vertice(i, 0);
    }
  }

  // Lê as arestas
  int origem, destino, peso;
  while (arquivo >> origem >> destino) {
    if (ponderadoArestas) {
      arquivo >> peso;
      inserir_aresta(origem, destino, peso);
    } else {
      // Para grafos não ponderados, usar 1 para indicar a presença da aresta
      inserir_aresta(origem, destino, 1);
    }
  }
  arquivo.close();
}

// Retorna o grau (ou grau máximo) do grafo.
// Para grafos direcionados, considera a soma do outdegree e indegree.
int Grafo::get_grau() const {
  int max_grau = 0;
  for (int i = 1; i <= ordem; i++) {
    IntList vizinhos = get_vizinhos(i);
    int out_deg = vizinhos.size();
    int in_deg = 0;
    for (int j = 1; j <= ordem; j++) {
      if (j == i)
        continue;
      IntList viz = get_vizinhos(j);
      for (int k = 0; k < viz.size(); k++) {
        if (viz.get(k) == i) {
          in_deg++;
          break;
        }
      }
    }
    int total = (direcionado ? (out_deg + in_deg) : out_deg);
    if (total > max_grau)
      max_grau = total;
  }
  return max_grau;
}

// Função auxiliar DFS para marcar os vértices alcançados (desconsidera a
// direção)
void dfs_util(const Grafo *g, int v, bool *visitado) {
  visitado[v] = true;
  IntList viz = g->get_vizinhos(v);
  for (int i = 0; i < viz.size(); i++) {
    int w = viz.get(i);
    if (!visitado[w])
      dfs_util(g, w, visitado);
  }
  // Para garantir a conectividade em grafos direcionados, varre os vértices que
  // apontam para v
  for (int i = 1; i <= g->get_ordem(); i++) {
    if (!visitado[i]) {
      IntList viz_i = g->get_vizinhos(i);
      for (int j = 0; j < viz_i.size(); j++) {
        if (viz_i.get(j) == v) {
          dfs_util(g, i, visitado);
          break;
        }
      }
    }
  }
}

// Retorna o número de componentes conexas
int Grafo::n_conexo() const {
  bool *visitado = new bool[ordem + 1];
  for (int i = 0; i <= ordem; i++)
    visitado[i] = false;
  int count = 0;
  for (int i = 1; i <= ordem; i++) {
    if (!visitado[i]) {
      dfs_util(this, i, visitado);
      count++;
    }
  }
  delete[] visitado;
  return count;
}

// Verifica se o grafo é completo
bool Grafo::eh_completo() const {
  for (int i = 1; i <= ordem; i++) {
    IntList viz = get_vizinhos(i);
    if (!direcionado) {
      if (viz.size() != ordem - 1)
        return false;
    } else {
      if (viz.size() != ordem - 1)
        return false;
      int in_deg = 0;
      for (int j = 1; j <= ordem; j++) {
        if (j == i)
          continue;
        IntList viz_j = get_vizinhos(j);
        for (int k = 0; k < viz_j.size(); k++) {
          if (viz_j.get(k) == i) {
            in_deg++;
            break;
          }
        }
      }
      if (in_deg != ordem - 1)
        return false;
    }
  }
  return true;
}
