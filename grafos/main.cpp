#include "Grafo.h"
#include "Grafo_lista.h"
#include "Grafo_matriz.h"

using namespace std;

int main(int argc, char *argv[]) {

  if (argc < 4) {
    cerr << "Uso incorreto. Exemplos:\n"
         << "  " << argv[0] << " -d -m grafo.txt\n"
         << "  " << argv[0] << " -d -l grafo.txt\n"
         << "  " << argv[0] << " -c -m descricao.txt grafo.txt\n"
         << "  " << argv[0] << " -c -l descricao.txt grafo.txt\n";
    return 1;
  }

  // Lê primeiro argumento: -d ou -c
  string modo = argv[1]; // "-d" ou "-c"

  // Lê segundo argumento: -m ou -l
  string estrutura = argv[2]; // "-m" ou "-l"

  // Ponteiro para a classe base (grafo)
  Grafo *g = nullptr;

  // == MODO DESCRICAO: -d ==
  if (modo == "-d") {
    // Verifica se tem ao menos 3 argumentos: -d -m/-l nome_arquivo
    // argv[3] deve ser o arquivo de grafo
    if (argc < 4) {
      cerr << "Faltam argumentos para o modo -d.\n";
      return 1;
    }

    string arquivoGrafo = argv[3];

    // Escolhe a implementação
    if (estrutura == "-m") {
      g = new Grafo_matriz(0, false, false, false);
      // Apontar corretamente com os parâmetros certos! Talvez seja interessante
      // não passar os parametros na criação
    } else if (estrutura == "-l") {
      g = new Grafo_lista(0, false, false, false);
      // Apontar corretamente com os parâmetros certos! Talvez seja interessante
      // não passar os parâmetros na criação
    } else {
      cerr << "Estrutura inválida (use -m ou -l).\n";
      return 1;
    }

    // Carrega o grafo a partir do arquivo
    g->carrega_grafo(arquivoGrafo);

    // Exibe as propriedades do grafo
    cout << arquivoGrafo << "\n";
    cout << "Grau: " << g->get_grau() << "\n";
    cout << "Ordem: " << g->get_ordem() << "\n";
    cout << "Direcionado: " << (g->eh_direcionado() ? "Sim" : "Não") << "\n";
    cout << "Componentes conexas: " << g->n_conexo() << "\n";
    cout << "Vertices ponderados: " << (g->vertice_ponderado() ? "Sim" : "Não")
         << "\n";
    cout << "Arestas ponderadas: " << (g->aresta_ponderada() ? "Sim" : "Não")
         << "\n";
    cout << "Completo: " << (g->eh_completo() ? "Sim" : "Não") << "\n";
    cout << "Bipartido: " << (g->eh_bipartido() ? "Sim" : "Não") << "\n";
    cout << "Arvore: " << (g->eh_arvore() ? "Sim" : "Não") << "\n";
    cout << "Aresta Ponte: " << (g->possui_ponte() ? "Sim" : "Não") << "\n";
    cout << "Vertice de Articulacao: "
         << (g->possui_articulacao() ? "Sim" : "Não") << "\n";
  }
  // == MODO CRIACAO: -c ==
  else if (modo == "-c") {
    // Verifica se tem ao menos 5 argumentos: -c -m/-l descricao.txt grafo.txt
    if (argc < 5) {
      cerr << "Faltam argumentos para o modo -c.\n";
      return 1;
    }

    string arquivoDesc = argv[3];  // descricao.txt
    string arquivoGrafo = argv[4]; // grafo.txt

    // Escolhe a implementação
    if (estrutura == "-m") {
      // g = new grafo_matriz(); // Apontar corretamente com os parâmetros!
    } else if (estrutura == "-l") {
      // g = new grafo_lista(); // Apontar corretamente com os parâmetros!
    } else {
      cerr << "Estrutura inválida (use -m ou -l).\n";
      return 1;
    }

    // Gera um novo grafo aleatório (com base no arquivo de descrição) e salva
    // em arquivoGrafo
    g->novo_grafo(arquivoDesc, arquivoGrafo);

    cout << "Grafo criado e salvo em " << arquivoGrafo << endl;
  } else {
    cerr << "Modo inválido (use -d ou -c).\n";
    return 1;
  }

  // Desaloca o grafo, caso tenha sido criado
  delete g;

  cout << "Finalizado" << endl;

  return 0;
}
