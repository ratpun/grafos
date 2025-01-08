#include "Grafo.h"
#include "Grafo_lista.cpp"
#include "Grafo_matriz.h"

using namespace std;

int main(int argc, char *argv[])
{

  /**
   * Formas de execução:
   *
   * Caso 1: ./main.out -d -m grafo.txt
   *   - Imprime descrição do grafo após carregar com matriz de adjacência.
   * Caso 2: ./main.out -d -l grafo.txt
   *   - Imprime descrição do grafo após carregar com lista encadeada.
   * Caso 3: ./main.out -c -m descricao.txt grafo.txt
   *   - Lê config (descricao.txt), cria grafo aleatório (matriz) e salva em
   * grafo.txt. Caso 4: ./main.out -c -l descricao.txt grafo.txt
   *   - Lê config (descricao.txt), cria grafo aleatório (lista) e salva em
   * grafo.txt.
   */

  if (argc < 4)
  {
    cerr << "Uso incorreto. Exemplos:\n"
         << "  " << argv[0] << " -d -m grafo.txt\n"
         << "  " << argv[0] << " -d -l grafo.txt\n"
         << "  " << argv[0] << " -c -m descricao.txt grafo.txt\n"
         << "  " << argv[0] << " -c -l descricao.txt grafo.txt\n";
    return 1;
  }

  string modo = argv[1];

  string estrutura = argv[2];

  Grafo *g = nullptr;

  if (modo == "-d")
  {

    if (argc < 4)
    {
      cerr << "Faltam argumentos para o modo -d.\n";
      return 1;
    }

    string arquivoGrafo = argv[3];

    if (estrutura == "-m")
    {
    }
    else if (estrutura == "-l")
    {
      g = new Grafo_lista();
    }
    else
    {
      cerr << "Estrutura inválida (use -m ou -l).\n";
      return 1;
    }

    g->carrega_grafo(arquivoGrafo);

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

  else if (modo == "-c")
  {

    if (argc < 5)
    {
      cerr << "Faltam argumentos para o modo -c.\n";
      return 1;
    }

    string arquivoDesc = argv[3];
    string arquivoGrafo = argv[4];

    if (estrutura == "-m")
    {
    }
    else if (estrutura == "-l")
    {
      g = new Grafo_lista();
    }
    else
    {
      cerr << "Estrutura inválida (use -m ou -l).\n";
      return 1;
    }

    g->novo_grafo(arquivoDesc, arquivoGrafo);

    cout << "Grafo criado e salvo em " << arquivoGrafo << endl;
  }
  else
  {
    cerr << "Modo inválido (use -d ou -c).\n";
    return 1;
  }

  delete g;

  cout << "Finalizado" << endl;

  return 0;
}
