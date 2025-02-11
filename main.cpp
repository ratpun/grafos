
#include "./include/Grafo.hpp"
#include "./include/GrafoLista.hpp"
#include "./include/GrafoMatriz.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Uso: " << argv[0] << " -d|-n -m|-l grafo.txt" << endl;
    return 1;
  }

  string flagDirecao = argv[1];   // -d ou -n
  string flagEstrutura = argv[2]; // -m ou -l
  string nomeArquivo = argv[3];

  Grafo *grafo = nullptr;
  if (flagEstrutura == "-m")
    grafo = new GrafoMatriz();
  else if (flagEstrutura == "-l")
    grafo = new GrafoLista();
  else {
    cout << "Estrutura inválida. Use -m para matriz ou -l para lista." << endl;
    return 1;
  }

  grafo->carrega_grafo(nomeArquivo);

  cout << "Grafo carregado: Ordem = " << grafo->get_ordem() << endl;

  grafo->imprime_grafo();

  // Exclusão de nó 1 (se existir)
  cout << "Excluindo nó 1..." << endl;

  grafo->deleta_no(1);

  // Exclusão da primeira aresta do nó 2 (se existir)
  cout << "Excluindo primeira aresta do nó 2..." << endl;
  IntList vizinhos = grafo->get_vizinhos(2);
  if (vizinhos.size() > 0) {
    int primeiroVizinho = vizinhos.get(0);
    grafo->deleta_aresta(2, primeiroVizinho);
  }

  grafo->imprime_grafo();

  // Impressão das propriedades do grafo
  cout << "Grau: " << grafo->get_grau() << endl;
  cout << "Ordem: " << grafo->get_ordem() << endl;
  cout << "Direcionado: " << (grafo->eh_direcionado() ? "Sim" : "Nao") << endl;
  cout << "Vertices ponderados: "
       << (grafo->vertice_ponderado() ? "Sim" : "Nao") << endl;
  cout << "Arestas ponderadas: " << (grafo->aresta_ponderada() ? "Sim" : "Nao")
       << endl;
  cout << "Completo: " << (grafo->eh_completo() ? "Sim" : "Nao") << endl;

  // Cálculo e impressão da maior menor distância (diâmetro do grafo)
  Grafo::ResultadoDistancia res = grafo->calculaMaiorMenorDistancia();
  cout << "Maior menor distância: (" << res.no1 << "-" << res.no2 << ") "
       << res.distancia << endl;

  delete grafo;
  return 0;
}
