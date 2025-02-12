
#include "./include/Grafo.hpp"
#include "./include/GrafoLista.hpp"
#include "./include/GrafoMatriz.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Uso: " << argv[0] << " -d -m|-l nome_arquivo.txt\n";
    return 1;
  }

  string flagDirecao = argv[1];
  string flagEstrutura = argv[2]; // "-m" para matriz ou "-l" para lista
  string nomeArquivo = argv[3];

  Grafo *grafo = 0;
  if (flagEstrutura == "-m")
    grafo = new GrafoMatriz();
  else if (flagEstrutura == "-l")
    grafo = new GrafoLista();
  else {
    cout << "Estrutura invalida. Use -m para matriz ou -l para lista.\n";
    return 1;
  }

  grafo->carrega_grafo(nomeArquivo);

  cout << "Grau: " << grafo->get_grau() << "\n";
  cout << "Ordem: " << grafo->get_ordem() << "\n";
  cout << "Direcionado: " << (grafo->eh_direcionado() ? "Sim" : "Nao") << "\n";
  cout << "Vertices ponderados: "
       << (grafo->vertice_ponderado() ? "Sim" : "Nao") << "\n";
  cout << "Arestas ponderadas: " << (grafo->aresta_ponderada() ? "Sim" : "Nao")
       << "\n";
  cout << "Completo: " << (grafo->eh_completo() ? "Sim" : "Nao") << "\n";

  delete grafo;
  return 0;
}
