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

  return 0;
}
