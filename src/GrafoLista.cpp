#include "../include/GrafoLista.hpp"
#include "../include/IntList.hpp"
#include "../include/ListaEncadeada.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

GrafoLista::GrafoLista() { vertices = new ListaEncadeada<Vertice *>(); }

GrafoLista::~GrafoLista() {
  // Itera sobre a lista de vértices e deleta cada um
  No<Vertice *> *no = vertices->getHead();
  while (no) {
    delete no->dado;
    no = no->prox;
  }
  delete vertices;
}

void GrafoLista::inserir_vertice(int id, int peso) {
  Vertice *v = new Vertice(id, peso);
  vertices->append(v);
}

Vertice *GrafoLista::encontrar_vertice(int id) const {
  No<Vertice *> *no = vertices->getHead();
  while (no) {
    if (no->dado->id == id)
      return no->dado;
    no = no->prox;
  }
  return 0;
}

void GrafoLista::inserir_aresta(int origem, int destino, int peso) {
  // Validação: não permitir laços
  if (origem == destino) {
    cerr << "Erro: Laço não permitido (origem e destino iguais: " << origem
         << ")." << endl;
    return;
  }

  // Busca o vértice de origem
  Vertice *v = encontrar_vertice(origem);
  if (!v) {
    cerr << "Erro: Vértice " << origem << " não encontrado." << endl;
    return;
  }

  // Verifica se já existe uma aresta de 'origem' para 'destino'
  No<Aresta> *no = v->arestas->getHead();
  while (no) {
    if (no->dado.destino == destino) {
      cerr << "Erro: Aresta de " << origem << " para " << destino
           << " já existe." << endl;
      return;
    }
    no = no->prox;
  }

  // Se não houver conflito, insere a aresta na lista do vértice de origem
  v->arestas->inserir(Aresta(destino, peso));

  // Se o grafo não for direcionado, insere a aresta simetricamente
  if (!direcionado) {
    Vertice *v2 = encontrar_vertice(destino);
    if (!v2) {
      cerr << "Erro: Vértice " << destino << " não encontrado." << endl;
      return;
    }
    // Verifica se a aresta reversa já existe na lista do vértice de destino
    no = v2->arestas->getHead();
    while (no) {
      if (no->dado.destino == origem) {
        cerr << "Erro: Aresta de " << destino << " para " << origem
             << " já existe." << endl;
        return;
      }
      no = no->prox;
    }
    v2->arestas->inserir(Aresta(origem, peso));
  }
}

IntList GrafoLista::get_vizinhos(int id) const {
  IntList lista;
  Vertice *v = encontrar_vertice(id);
  if (!v)
    return lista;
  No<Aresta> *no = v->arestas->getHead();
  while (no) {
    lista.add(no->dado.destino);
    no = no->prox;
  }
  return lista;
}

void GrafoLista::novo_no(int peso) {
  // Cria um novo vértice com id = ordem + 1 e o insere na lista
  Vertice *novo = new Vertice(ordem + 1, peso);
  vertices->inserir(novo);
  ordem++;
}

void GrafoLista::nova_aresta(int origem, int destino, int peso) {
  if (origem == destino) {
    cerr << "Erro: Laço não permitido." << endl;
    return;
  }
  Vertice *v = encontrar_vertice(origem);
  if (!v) {
    cerr << "Erro: Vértice " << origem << " não encontrado." << endl;
    return;
  }
  // Verifica se já existe aresta para o destino
  No<Aresta> *no = v->arestas->getHead();
  while (no) {
    if (no->dado.destino == destino) {
      cerr << "Erro: Aresta de " << origem << " para " << destino
           << " já existe." << endl;
      return;
    }
    no = no->prox;
  }
  v->arestas->inserir(Aresta(destino, peso));
  if (!direcionado) {
    Vertice *v2 = encontrar_vertice(destino);
    if (!v2) {
      cerr << "Erro: Vértice " << destino << " não encontrado." << endl;
      return;
    }
    no = v2->arestas->getHead();
    while (no) {
      if (no->dado.destino == origem) {
        return;
      }
      no = no->prox;
    }
    v2->arestas->inserir(Aresta(origem, peso));
  }
}

void GrafoLista::deleta_no(int id) {
  // 1. Remover o vértice da lista de vértices
  No<Vertice *> *atual = vertices->getHead();
  No<Vertice *> *anterior = nullptr;
  bool removido = false;
  while (atual != nullptr) {
    if (atual->dado->id == id) {
      if (anterior == nullptr) {
        // Atualize o head da lista
        vertices->setHead(atual->prox);
      } else {
        anterior->prox = atual->prox;
      }
      // Libere as arestas e o vértice
      delete atual->dado;
      delete atual;
      removido = true;
      ordem--; // Atualize a ordem
      break;
    }
    anterior = atual;
    atual = atual->prox;
  }
  if (!removido) {
    cerr << "Erro: Vértice " << id << " não existe." << endl;
    return;
  }

  // 2. Remover de todas as listas de arestas quaisquer referências ao nó
  // removido
  atual = vertices->getHead();
  while (atual != nullptr) {
    No<Aresta> *atAresta = atual->dado->arestas->getHead();
    No<Aresta> *antAresta = nullptr;
    while (atAresta != nullptr) {
      if (atAresta->dado.destino == id) {
        if (antAresta == nullptr) {
          atual->dado->arestas->setHead(atAresta->prox);
        } else {
          antAresta->prox = atAresta->prox;
        }
        No<Aresta> *temp = atAresta;
        atAresta = atAresta->prox;
        delete temp;
      } else {
        antAresta = atAresta;
        atAresta = atAresta->prox;
      }
    }
    atual = atual->prox;
  }

  // 3. Reindexar os nós restantes (supondo que os nós na lista devem ser
  // numerados de 1 a ordem)
  int novoId = 1;
  atual = vertices->getHead();
  while (atual != nullptr) {
    atual->dado->id = novoId;
    novoId++;
    atual = atual->prox;
  }

  // 4. Atualizar as referências das arestas: se o destino > id removido,
  // subtrair 1.
  atual = vertices->getHead();
  while (atual != nullptr) {
    No<Aresta> *atAresta = atual->dado->arestas->getHead();
    while (atAresta != nullptr) {
      if (atAresta->dado.destino > id) {
        atAresta->dado.destino -= 1;
      }
      atAresta = atAresta->prox;
    }
    atual = atual->prox;
  }
}

void GrafoLista::deleta_aresta(int origem, int destino) {
  Vertice *v = encontrar_vertice(origem);
  if (!v) {
    cerr << "Erro: Vértice " << origem << " não encontrado." << endl;
    return;
  }
  No<Aresta> *atual = v->arestas->getHead();
  No<Aresta> *anterior = nullptr;
  while (atual != nullptr) {
    if (atual->dado.destino == destino) {
      if (anterior == nullptr) {
        v->arestas->setHead(atual->prox);
      } else {
        anterior->prox = atual->prox;
      }
      delete atual;
      break;
    }
    anterior = atual;
    atual = atual->prox;
  }
  if (!direcionado) {
    Vertice *v2 = encontrar_vertice(destino);
    if (v2) {
      atual = v2->arestas->getHead();
      anterior = nullptr;
      while (atual != nullptr) {
        if (atual->dado.destino == origem) {
          if (anterior == nullptr) {
            v2->arestas->setHead(atual->prox);
          } else {
            anterior->prox = atual->prox;
          }
          delete atual;
          break;
        }
        anterior = atual;
        atual = atual->prox;
      }
    }
  }
}

double GrafoLista::getPesoAresta(int origem, int destino) const {
  Vertice *v = encontrar_vertice(origem);
  if (!v)
    return 1e9;
  No<Aresta> *no = v->arestas->getHead();
  while (no) {
    if (no->dado.destino == destino)
      return no->dado.peso;
    no = no->prox;
  }
  return 1e9;
}
void GrafoLista::imprime_grafo() const {
  std::cout << "Grafo (Lista de Adjacência):" << std::endl;
  std::cout << "Ordem: " << ordem << std::endl;
  // Percorre a lista de vértices (assumindo que vertices->getHead() retorna um
  // ponteiro para o primeiro nó)
  No<Vertice *> *atual = vertices->getHead();
  while (atual != nullptr) {
    std::cout << "Vértice " << atual->dado->id;
    if (ponderadoVertices)
      std::cout << " (peso: " << atual->dado->peso << ")";
    std::cout << " -> ";
    // Obtém e imprime os vizinhos usando get_vizinhos
    IntList vizinhos = get_vizinhos(atual->dado->id);
    if (vizinhos.size() == 0) {
      std::cout << "Sem vizinhos";
    } else {
      for (int i = 0; i < vizinhos.size(); i++) {
        std::cout << vizinhos.get(i) << " ";
      }
    }
    std::cout << std::endl;
    atual = atual->prox;
  }
}

void GrafoLista::colore_arestas() {
    std::cout << "Iniciando coloração de arestas..." << std::endl;

    int *arestaCor = new int[ordem * ordem];
    std::fill(arestaCor, arestaCor + (ordem * ordem), -1); // Inicializa todas as arestas sem cor

    // Itera sobre cada vértice (lista de vértices)
    No<Vertice *> *atual = vertices->getHead();
    while (atual != nullptr) {
        // Para cada vértice, percorre suas arestas de saída
        No<Aresta> *atAresta = atual->dado->arestas->getHead();
        while (atAresta != nullptr) {
            int origem = atual->dado->id;
            int destino = atAresta->dado.destino;

            int arestaIndex = (origem - 1) * ordem + (destino - 1);
            int arestaIndexInvertida = (destino - 1) * ordem + (origem - 1);

            // Se a aresta já foi colorida, pula para a próxima
            if (arestaCor[arestaIndex] != -1) {
                atAresta = atAresta->prox;
                continue;
            }

            // Cria array para armazenar as cores usadas pelas arestas incidentes
            bool *coresUsadas = new bool[ordem];
            std::fill(coresUsadas, coresUsadas + ordem, false);

            // Verifica cores das arestas que partem do mesmo vértice origem
            No<Aresta> *vizinho = atual->dado->arestas->getHead();
            while (vizinho != nullptr) {
                int vizinhoIndex = (origem - 1) * ordem + (vizinho->dado.destino - 1);
                if (vizinhoIndex >= 0 && vizinhoIndex < (ordem * ordem) && arestaCor[vizinhoIndex] != -1) {
                    coresUsadas[arestaCor[vizinhoIndex]] = true;
                }
                vizinho = vizinho->prox;
            }

            // Verifica cores das arestas que chegam ao vértice origem (arestas de outros vértices que chegam em 'origem')
            No<Vertice *> *atualOrigem = vertices->getHead();
            while (atualOrigem != nullptr) {
                No<Aresta> *entrada = atualOrigem->dado->arestas->getHead();
                while (entrada != nullptr) {
                    if (entrada->dado.destino == origem) {
                        // Aqui o índice correto utiliza o id do vértice de onde sai a aresta (atualOrigem)
                        int entradaIndex = (atualOrigem->dado->id - 1) * ordem + (origem - 1);
                        if (entradaIndex >= 0 && entradaIndex < (ordem * ordem) && arestaCor[entradaIndex] != -1) {
                            coresUsadas[arestaCor[entradaIndex]] = true;
                        }
                    }
                    entrada = entrada->prox;
                }
                atualOrigem = atualOrigem->prox;
            }

            // Verifica cores das arestas que chegam ao vértice destino (arestas de outros vértices que chegam em 'destino')
            No<Vertice *> *atualDestino = vertices->getHead();
            while (atualDestino != nullptr) {
                No<Aresta> *entrada = atualDestino->dado->arestas->getHead();
                while (entrada != nullptr) {
                    if (entrada->dado.destino == destino) {
                        // O índice utiliza o id do vértice de origem da aresta (atualDestino)
                        int entradaIndex = (atualDestino->dado->id - 1) * ordem + (destino - 1);
                        if (entradaIndex >= 0 && entradaIndex < (ordem * ordem) && arestaCor[entradaIndex] != -1) {
                            coresUsadas[arestaCor[entradaIndex]] = true;
                        }
                    }
                    entrada = entrada->prox;
                }
                atualDestino = atualDestino->prox;
            }

            // Encontra a menor cor disponível
            int cor = 0;
            while (cor < ordem && coresUsadas[cor]) {
                cor++;
            }

            // Atribui a cor à aresta
            arestaCor[arestaIndex] = cor;
            std::cout << "Aresta (" << origem << " -> " << destino << ") colorida com cor: " << cor << std::endl;

            // Se o grafo for não direcionado, também colorimos a aresta reversa
            if (!direcionado) {
                arestaCor[arestaIndexInvertida] = cor;
            }

            // Libera a memória do array auxiliar
            delete[] coresUsadas;

            atAresta = atAresta->prox;
        }
        atual = atual->prox;
    }

    // Calcula o número total de cores utilizadas
    int coresUtilizadas = 0;
    for (int i = 0; i < ordem * ordem; i++) {
        if (arestaCor[i] != -1) {
            coresUtilizadas = std::max(coresUtilizadas, arestaCor[i] + 1);
        }
    }
    std::cout << "Número total de cores usadas: " << coresUtilizadas << std::endl;

    // Libera a memória alocada para as cores das arestas
    delete[] arestaCor;
}
