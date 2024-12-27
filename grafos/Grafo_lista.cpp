#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "no_Vertice.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Grafo_lista : public Grafo {
private:
  NoVertice *primeiroVertice; ///< Ponteiro para o primeiro vértice da lista
  int numVertices;            ///< Número de vértices (ordem do grafo)
  int numArestas;             ///< Número de arestas
  bool direcionado;           ///< Flag que indica se o grafo é direcionado
  bool verticesPonderados;    ///< Flag que indica se os vértices têm peso
  bool arestasPonderadas;     ///< Flag que indica se as arestas têm peso

public:
  Grafo_lista()
      : primeiroVertice(nullptr), numVertices(0), numArestas(0),
        direcionado(false), verticesPonderados(false),
        arestasPonderadas(false) {}

  ~Grafo_lista() {
    // Destruir toda a lista de vértices e as respectivas listas de arestas
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      // Desalocar arestas do vértice
      NoAresta *aAtual = vAtual->getPrimeiraAresta();
      while (aAtual != nullptr) {
        NoAresta *aDel = aAtual;
        aAtual = aAtual->getProxima();
        delete aDel;
      }
      // Desalocar vértice
      NoVertice *vDel = vAtual;
      vAtual = vAtual->getProximoVertice();
      delete vDel;
    }
  }

  void carrega_grafo(const string &arquivo) override {
    ifstream fin(arquivo.c_str());
    if (!fin.is_open()) {
      cerr << "Erro ao abrir arquivo " << arquivo << endl;
      return;
    }

    // 1) Lê a primeira linha (4 valores):
    //    [numVertices] [dir=0/1] [vPond=0/1] [aPond=0/1]
    int dir, vPond, aPond;
    fin >> numVertices >> dir >> vPond >> aPond;
    if (!fin.good()) {
      cerr << "Erro ao ler a primeira linha de " << arquivo << endl;
      return;
    }

    // Ajusta flags internas
    direcionado = (dir == 1);
    verticesPonderados = (vPond == 1);
    arestasPonderadas = (aPond == 1);

    // 2) Se os vértices são ponderados, lê uma linha com 'numVertices' pesos
    //    Caso não sejam ponderados, podemos usar peso 1.0 para todos
    if (verticesPonderados) {
      for (int i = 0; i < numVertices; i++) {
        double pesoVert;
        fin >> pesoVert;
        if (!fin.good()) {
          cerr << "Erro ao ler peso do vertice " << i << endl;
          return;
        }
        insereVertice(i + 1, pesoVert);
        // Se seus vértices são indexados de 1..N, use (i+1).
        // Se for 0..(N-1), use (i).
      }
    } else {
      // Se não for ponderado em vértices, ainda precisamos criar vértices,
      // mas com peso default (1.0) ou algo do tipo
      for (int i = 0; i < numVertices; i++) {
        insereVertice(i + 1, 1.0);
      }
    }

    // 3) Agora lemos as arestas até o fim do arquivo:
    //    Se arestasPonderadas == 1, formato: <origem> <destino> <peso>
    //    Se arestasPonderadas == 0, formato: <origem> <destino>
    numArestas = 0;
    while (true) {
      int origem, destino;
      double peso = 1.0; // Peso default se não for ponderada
      fin >> origem >> destino;
      if (!fin.good()) {
        break; // chegou no fim ou deu erro de leitura
      }
      if (arestasPonderadas) {
        fin >> peso;
        if (!fin.good()) {
          break; // leitura de peso falhou
        }
      }
      // Insere a aresta no grafo
      insereAresta(origem, destino, peso);
      numArestas++;
    }

    fin.close();
  }

  void novo_grafo(const string &descricao,
                  const string &arquivoSaida) override {

    ifstream fin(descricao.c_str());
    if (!fin.is_open()) {
      cerr << "Erro ao abrir arquivo de descrição " << descricao << endl;
      return;
    }

    fin >> numVertices >> numArestas;
    int dir, compConexas, vPond, aPond, completo, bipartido, arvore, aPonte,
        vArti;
    fin >> dir >> compConexas >> vPond >> aPond >> completo >> bipartido >>
        arvore >> aPonte >> vArti;

    //  AINDA É NECESSARIO TRATAR OS OUTROS
    //  PARAMETROS DE ENTRADA!!
    direcionado = (dir == 1);
    verticesPonderados = (vPond == 1);
    arestasPonderadas = (aPond == 1);

    fin.close();

    // Limpar qualquer dado antigo
    limpaGrafo();

    // Gerar vértices aleatórios (por exemplo, pesos aleatórios)
    srand((unsigned)time(nullptr));
    for (int i = 0; i < numVertices; i++) {
      double peso = (verticesPonderados) ? (double)(rand() % 10 + 1) : 1.0;
      insereVertice(i + 1, peso);
    }

    // Gerar arestas aleatórias
    int contadorArestas = 0;
    while (contadorArestas < numArestas) {
      int origem = rand() % numVertices;
      int destino = rand() % numVertices;
      if (origem == destino)
        continue; // evita laço
      // Checar se aresta já existe (evitar múltiplas arestas)
      if (!existeAresta(origem, destino)) {
        double pesoA = (arestasPonderadas) ? (double)(rand() % 10 + 1) : 1.0;
        insereAresta(origem, destino, pesoA);
        contadorArestas++;
      }
    }

    // Salvar grafo no arquivo de saída
    ofstream fout(arquivoSaida.c_str());
    if (!fout.is_open()) {
      cerr << "Erro ao criar arquivo de saída " << arquivoSaida << endl;
      return;
    }
    // Formato de saída (deve ser igual ao usado em carrega_grafo acima):

    fout << numVertices << " " << (direcionado ? 1 : 0) << " "
         << (verticesPonderados ? 1 : 0) << " " << (arestasPonderadas ? 1 : 0)
         << endl;

    // Escreve pesos dos vértices (se houver)
    if (verticesPonderados) {
      NoVertice *vAtual = primeiroVertice;
      while (vAtual != nullptr) {
        fout << vAtual->getPesoVertice() << " ";
        vAtual = vAtual->getProximoVertice();
      }
      fout << endl;
    }

    // Escreve as arestas
    // Para cada vértice, varremos sua lista de adjacência
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      NoAresta *aAtual = vAtual->getPrimeiraAresta();
      while (aAtual != nullptr) {
        fout << vAtual->getIdVertice() << " " << aAtual->getIdVertice();
        if (arestasPonderadas) {
          fout << " " << aAtual->getPesoAresta();
        }
        fout << endl;
        aAtual = aAtual->getProxima();
      }
      vAtual = vAtual->getProximoVertice();
    }

    fout.close();
  }

  bool eh_bipartido() override {
    // Implementar a "força bruta" mencionada nas especificações.
    return false;
  }

  int n_conexo() override {
    // Implementar função que indica a quantidade de componentes conexas
    return 0;
  }

  int get_grau() override {
    int grauMaximo = 0;
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      // Conta quantas arestas existem no vértice
      int contador = 0;
      NoAresta *aAtual = vAtual->getPrimeiraAresta();
      while (aAtual != nullptr) {
        contador++;
        aAtual = aAtual->getProxima();
      }
      if (contador > grauMaximo) {
        grauMaximo = contador;
      }
      vAtual = vAtual->getProximoVertice();
    }
    return grauMaximo;
  }

  int get_ordem() override { return numVertices; }
  bool eh_direcionado() override { return direcionado; }
  bool vertice_ponderado() override { return verticesPonderados; }
  bool aresta_ponderada() override { return arestasPonderadas; }
  bool eh_completo() override {
    // Implementar função que diz se um grafo é completo ou não
    return false;
  }

  bool eh_arvore() override {
    // Implementar função que diz se o grafo é uma árvore
    // Uma maneira simples: verificar se é conexo e se (número de arestas =
    // número de vértices - 1)
    return false;
  }

  bool possui_articulacao() override {
    // Implementar função que diz se existe ao menos um vertice de articulação
    return false;
  }

  bool possui_ponte() override {
    // Implementar função que diz se existe ao menos uma aresta ponte
    return false;
  }

  //-------------------------------------------------------------
  //            MÉTODOS AUXILIARES ESPECÍFICOS
  //-------------------------------------------------------------

  void insereVertice(int id, double pesoVertice = 1.0) {
    // Verifica se já existe esse vértice
    if (encontraVertice(id) != nullptr)
      return;

    NoVertice *novoV = new NoVertice(id, pesoVertice);
    novoV->setProximoVertice(primeiroVertice);
    primeiroVertice = novoV;
  }

  void insereAresta(int origem, int destino, double peso = 1.0) {
    // Evita laços
    if (origem == destino)
      return;
    // Verifica se já existe a aresta
    if (existeAresta(origem, destino))
      return;

    NoVertice *vOrigem = encontraVertice(origem);
    if (!vOrigem)
      return; // Vértice de origem não existe

    // Insere aresta em origem -> destino
    vOrigem->insereAresta(destino, peso);

    // Se o grafo não for direcionado, insere a aresta destino -> origem também
    if (!direcionado) {
      NoVertice *vDestino = encontraVertice(destino);
      if (!vDestino)
        return; // Vértice de destino não existe
      vDestino->insereAresta(origem, peso);
    }
  }

private:
  NoVertice *encontraVertice(int id) {
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      if (vAtual->getIdVertice() == id) {
        return vAtual;
      }
      vAtual = vAtual->getProximoVertice();
    }
    return nullptr;
  }

  bool existeAresta(int origem, int destino) {
    NoVertice *vOrigem = encontraVertice(origem);
    if (!vOrigem)
      return false;
    NoAresta *aAtual = vOrigem->getPrimeiraAresta();
    while (aAtual != nullptr) {
      if (aAtual->getIdVertice() == destino) {
        return true;
      }
      aAtual = aAtual->getProxima();
    }
    return false;
  }

  void limpaGrafo() {
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      NoAresta *aAtual = vAtual->getPrimeiraAresta();
      while (aAtual != nullptr) {
        NoAresta *aDel = aAtual;
        aAtual = aAtual->getProxima();
        delete aDel;
      }
      NoVertice *vDel = vAtual;
      vAtual = vAtual->getProximoVertice();
      delete vDel;
    }
    primeiroVertice = nullptr;
  }
};

#endif
