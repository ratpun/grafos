
#include "./include/Grafo.hpp"
#include "./include/GrafoLista.hpp"
#include "./include/GrafoMatriz.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Uso: " << argv[0] << " -p [-m|-l] <arquivo_grafo>" << endl;
    return 1;
  }

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

  clock_t inicioLeitura = clock();
  grafo->carrega_grafo(nomeArquivo);
  clock_t fimLeitura = clock();
  double tempoLeitura = double(fimLeitura - inicioLeitura) / CLOCKS_PER_SEC;
  cout << "Tempo de leitura do arquivo: " << tempoLeitura << " segundos"
       << endl;

  // cout << "Grafo carregado: Ordem = " << grafo->get_ordem() << endl;

  // grafo->imprime_grafo();

  // Exclusão de nó 1 (se existir)
  // cout << "Excluindo nó 1..." << endl;

  // grafo->deleta_no(1);

  // Exclusão da primeira aresta do nó 2 (se existir)
  // cout << "Excluindo primeira aresta do nó 2..." << endl;
  // IntList vizinhos = grafo->get_vizinhos(2);
  // if (vizinhos.size() > 0) {
  //   int primeiroVizinho = vizinhos.get(0);
  //   grafo->deleta_aresta(2, primeiroVizinho);
  // }

  // grafo->imprime_grafo();

  // Impressão das propriedades do grafo
  // cout << "Grau: " << grafo->get_grau() << endl;
  // cout << "Ordem: " << grafo->get_ordem() << endl;
  // cout << "Direcionado: " << (grafo->eh_direcionado() ? "Sim" : "Nao") <<
  // endl; cout << "Vertices ponderados: "
  //      << (grafo->vertice_ponderado() ? "Sim" : "Nao") << endl;
  // cout << "Arestas ponderadas: " << (grafo->aresta_ponderada() ? "Sim" :
  // "Nao")
  //      << endl;
  // cout << "Completo: " << (grafo->eh_completo() ? "Sim" : "Nao") << endl;

  // Cálculo e impressão da maior menor distância (diâmetro do grafo)
  // Grafo::ResultadoDistancia res = grafo->calculaMaiorMenorDistancia();
  // cout << "Maior menor distância: (" << res.no1 << "-" << res.no2 << ") "
  //      << res.distancia << endl;

  cout << "Executando algoritmos de coloração..." << endl;
  grafo->coloracaoGulosa();
  grafo->coloracaoRandomizada(10);
  grafo->coloracaoReativa(10, 0.5);

  delete grafo;
  return 0;
}
