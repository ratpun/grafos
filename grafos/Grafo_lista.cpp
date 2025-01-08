#include "Grafo.h"

#include "Grafo_lista.h"
#include "no_Aresta.h"
#include "no_Vertice.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Constrói um novo objeto Grafo_lista.
 *
 * Este construtor inicializa um novo objeto Grafo_lista com valores padrão:
 * - primeiroVertice é definido como nullptr.
 * - numNos é definido como 0.
 * - pesoNos é definido como nullptr.
 * - direcionado é definido como false.
 * - verticesPonderados é definido como false.
 * - arestasPonderadas é definido como false.
 * - numArestas é definido como 0.
 * - visitado é definido como nullptr.
 * - componentes é definido como nullptr.
 * - numComponentes é definido como 0.
 */
Grafo_lista::Grafo_lista()
    : primeiroVertice(nullptr), numNos(0), pesoNos(nullptr), direcionado(false),
      verticesPonderados(false), arestasPonderadas(false), numArestas(0),
      visitado(nullptr), componentes(nullptr), numComponentes(0) {}

/**
 * @brief Destrutor da classe Grafo_lista.
 *
 * Este destrutor desaloca toda a memória usada pelo grafo. Ele itera por todos
 * os vértices e suas respectivas arestas, deletando cada uma para liberar a
 * memória.
 *
 * O processo é o seguinte:
 * 1. Itera por cada vértice no grafo.
 * 2. Para cada vértice, itera por suas arestas e deleta cada aresta.
 * 3. Deleta o próprio vértice.
 *
 * Isso garante que toda a memória alocada dinamicamente para vértices e arestas
 * seja devidamente liberada quando um objeto Grafo_lista é destruído.
 */
Grafo_lista::~Grafo_lista() {

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
}

/**
 * @brief Carrega um grafo a partir de um arquivo.
 *
 * Esta função lê um grafo de um arquivo especificado e inicializa a estrutura
 * de dados do grafo com os vértices e arestas lidos. O arquivo deve seguir um
 * formato específico:
 * - A primeira linha contém quatro inteiros: o número de nós, um indicador se o
 *   grafo é direcionado (1 para sim, 0 para não), um indicador se os vértices
 *   são ponderados (1 para sim, 0 para não), e um indicador se as arestas são
 *   ponderadas (1 para sim, 0 para não).
 * - Se os vértices são ponderados, as próximas linhas contêm os pesos dos
 * vértices.
 * - As linhas seguintes contêm as arestas, cada uma representada por dois
 * inteiros (origem e destino) e, se as arestas são ponderadas, um valor de
 * peso.
 *
 * @param arquivo O caminho para o arquivo que contém a descrição do grafo.
 */
void Grafo_lista::carrega_grafo(const string &arquivo) {
  ifstream fin(arquivo.c_str());
  if (!fin.is_open()) {
    cerr << "Erro ao abrir arquivo " << arquivo << endl;
    return;
  }

  int dir, vPond, aPond;
  fin >> numNos >> dir >> vPond >> aPond;
  if (!fin.good()) {
    cerr << "Erro ao ler a primeira linha de " << arquivo << endl;
    return;
  }

  direcionado = (dir == 1);
  verticesPonderados = (vPond == 1);
  arestasPonderadas = (aPond == 1);

  if (verticesPonderados) {
    for (int i = 0; i < numNos; i++) {
      double pesoVert;
      fin >> pesoVert;
      if (!fin.good()) {
        cerr << "Erro ao ler peso do vertice " << i << endl;
        return;
      }
      insereVertice(i + 1, pesoVert);
    }
  } else {

    for (int i = 0; i < numNos; i++) {
      insereVertice(i + 1, 1.0);
    }
  }

  numArestas = 0;
  while (true) {
    int origem, destino;
    double peso = 1.0;
    fin >> origem >> destino;
    if (!fin.good()) {
      break;
    }
    if (arestasPonderadas) {
      fin >> peso;
      if (!fin.good()) {
        break;
      }
    }

    insereAresta(origem, destino, peso);
    numArestas++;
  }

  fin.close();
}

/**
 * @brief Cria um novo grafo a partir de uma descrição fornecida em um arquivo.
 *
 * Esta função lê a descrição de um grafo a partir de um arquivo de entrada,
 * inicializa o grafo com base nas informações lidas e salva o grafo gerado
 * em um arquivo de saída.
 *
 * @param descricao Caminho para o arquivo de descrição do grafo.
 * @param arquivoSaida Caminho para o arquivo onde o grafo gerado será salvo.
 *
 * O arquivo de descrição deve conter as seguintes informações na primeira
 * linha:
 * - grau: Grau do grafo.
 * - ordem: Número de vértices do grafo.
 * - dir: Indica se o grafo é direcionado (1) ou não (0).
 * - compConexas: Número de componentes conexas.
 * - vPond: Indica se os vértices são ponderados (1) ou não (0).
 * - aPond: Indica se as arestas são ponderadas (1) ou não (0).
 * - completo: Indica se o grafo é completo (1) ou não (0).
 * - bipartido: Indica se o grafo é bipartido (1) ou não (0).
 * - arvore: Indica se o grafo é uma árvore (1) ou não (0).
 * - aPonte: Indica se o grafo possui uma aresta ponte (1) ou não (0).
 * - vArti: Indica se o grafo possui um vértice de articulação (1) ou não (0).
 *
 * A função cria o grafo de acordo com as especificações lidas e o salva no
 * arquivo de saída no seguinte formato:
 * - Primeira linha: ordem, dir, vPond, aPond.
 * - Se os vértices são ponderados, uma linha com os pesos dos vértices.
 * - Para cada aresta, uma linha com os vértices de origem e destino e, se
 *   as arestas são ponderadas, o peso da aresta.
 */
void Grafo_lista::novo_grafo(const string &descricao,
                             const string &arquivoSaida) {
  ifstream fin(descricao.c_str());
  if (!fin.is_open()) {
    cerr << "Erro ao abrir arquivo de descrição " << descricao << endl;
    return;
  }

  int grau, ordem, dir, compConexas, vPond, aPond, completo, bipartido, arvore,
      aPonte, vArti;
  fin >> grau >> ordem >> dir >> compConexas >> vPond >> aPond >> completo >>
      bipartido >> arvore >> aPonte >> vArti;

  direcionado = (dir == 1);
  verticesPonderados = (vPond == 1);
  arestasPonderadas = (aPond == 1);

  fin.close();

  limpaGrafo();

  srand((unsigned)time(nullptr));
  for (int i = 0; i < ordem; i++) {
    double peso = (verticesPonderados) ? (double)(rand() % 10 + 1) : 1.0;
    insereVertice(i + 1, peso);
  }

  int *conjuntoA = nullptr;
  int *conjuntoB = nullptr;
  if (bipartido) {
    conjuntoA = new int[(ordem + 1) / 2];
    conjuntoB = new int[ordem / 2];
  }

  if (completo) {

    for (int i = 1; i <= ordem; i++) {
      for (int j = i + 1; j <= ordem; j++) {
        if (!direcionado) {
          insereAresta(i, j,
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        } else {
          insereAresta(i, j,
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
          insereAresta(j, i,
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        }
      }
    }
  } else if (arvore) {

    int *vertices = new int[ordem];
    for (int i = 0; i < ordem; i++) {
      vertices[i] = i + 1;
    }

    for (int i = ordem - 1; i > 0; i--) {
      int j = rand() % (i + 1);
      swap(vertices[i], vertices[j]);
    }

    for (int i = 1; i < ordem; i++) {
      int origem = vertices[i - 1];
      int destino = vertices[i];
      insereAresta(origem, destino,
                   arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
    }

    delete[] vertices;
  } else if (bipartido) {

    int tamanhoA = 0, tamanhoB = 0;

    for (int i = 1; i <= ordem; i++) {
      if (i % 2 == 0) {
        conjuntoA[tamanhoA++] = i;
      } else {
        conjuntoB[tamanhoB++] = i;
      }
    }

    for (int i = 0; i < tamanhoA; i++) {
      for (int j = 0; j < tamanhoB; j++) {
        if (rand() % 2 == 0) {
          insereAresta(conjuntoA[i], conjuntoB[j],
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        }
      }
    }

    delete[] conjuntoA;
    delete[] conjuntoB;
  } else {

    int tamanhoComp = ordem / compConexas;
    int **componentes = new int *[compConexas];
    for (int i = 0; i < compConexas; i++) {
      componentes[i] = new int[tamanhoComp];
      for (int j = 0; j < tamanhoComp; j++) {
        componentes[i][j] = j + 1 + (i * tamanhoComp);
      }
    }

    for (int i = 0; i < compConexas; i++) {
      for (int u = 0; u < tamanhoComp; u++) {
        for (int k = 0; k < grau; k++) {
          int v = componentes[i][rand() % tamanhoComp];
          if (componentes[i][u] != v && !existeAresta(componentes[i][u], v)) {
            insereAresta(componentes[i][u], v,
                         arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
          }
        }
      }
      delete[] componentes[i];
    }

    delete[] componentes;
  }

  if (aPonte) {
    int u = 1, v = 2;
    if (!existeAresta(u, v)) {
      insereAresta(u, v, arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
    }
  }

  ofstream fout(arquivoSaida.c_str());
  if (!fout.is_open()) {
    cerr << "Erro ao criar arquivo de saída " << arquivoSaida << endl;
    return;
  }

  fout << ordem << " " << (direcionado ? 1 : 0) << " "
       << (verticesPonderados ? 1 : 0) << " " << (arestasPonderadas ? 1 : 0)
       << endl;

  if (verticesPonderados) {
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      fout << vAtual->getPesoVertice() << " ";
      vAtual = vAtual->getProximoVertice();
    }
    fout << endl;
  }

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

/**
 * @brief Verifica se o grafo é bipartido.
 *
 * Esta função verifica se o grafo representado pela lista de adjacência é
 * bipartido. Um grafo é bipartido se seus vértices podem ser divididos em dois
 * conjuntos disjuntos de forma que nenhum vértice do mesmo conjunto seja
 * adjacente.
 *
 * @return true se o grafo é bipartido, false caso contrário.
 */
bool Grafo_lista::eh_bipartido() {

  for (unsigned long mascara = 0; mascara < (1UL << numNos); mascara++) {

    bool ok = true;

    NoVertice *uV = primeiroVertice;
    while (uV != nullptr && ok) {
      int u = uV->getIdVertice();
      NoAresta *a = uV->getPrimeiraAresta();
      while (a != nullptr) {
        int v = a->getIdVertice();

        int corU = ((mascara >> (u - 1)) & 1);
        int corV = ((mascara >> (v - 1)) & 1);
        if (corU == corV) {

          ok = false;
          break;
        }
        a = a->getProxima();
      }
      uV = uV->getProximoVertice();
    }

    if (ok) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Calcula o número de componentes conexas no grafo.
 *
 * Esta função percorre o grafo para determinar o número de componentes conexas.
 * Ela utiliza uma abordagem de busca em profundidade (DFS) para marcar todos os
 * vértices em cada componente.
 *
 * @return int O número de componentes conexas no grafo.
 */
int Grafo_lista::n_conexo() {

  bool *visitado = new bool[numNos + 1];
  for (int i = 1; i <= numNos; i++) {
    visitado[i] = false;
  }

  int componentesConexas = 0;

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {
    int idVertice = vAtual->getIdVertice();

    if (!visitado[idVertice]) {
      componentesConexas++;

      dfs_marcar_componente(idVertice, visitado);
    }

    vAtual = vAtual->getProximoVertice();
  }

  delete[] visitado;

  return componentesConexas;
}

/**
 * @brief Calcula o grau máximo do grafo.
 *
 * Esta função itera por todos os vértices do grafo e determina o vértice
 * com o maior número de arestas (grau). O grau de um vértice é o número de
 * arestas conectadas a ele.
 *
 * @return O grau máximo de qualquer vértice no grafo.
 */
int Grafo_lista::get_grau() {
  int grauMaximo = 0;
  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {

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

/**
 * @brief Obtém a ordem do grafo.
 *
 * Esta função retorna o número de nós (vértices) no grafo.
 *
 * @return int O número de nós no grafo.
 */
int Grafo_lista::get_ordem() { return numNos; }

/**
 * @brief Verifica se o grafo é direcionado.
 *
 * Esta função retorna um valor booleano indicando se o grafo é direcionado.
 *
 * @return true se o grafo for direcionado, false caso contrário.
 */
bool Grafo_lista::eh_direcionado() { return direcionado; }

/**
 * @brief Verifica se os vértices no grafo são ponderados.
 *
 * Esta função retorna um valor booleano indicando se os vértices
 * no grafo possuem pesos associados.
 *
 * @return true se os vértices são ponderados, false caso contrário.
 */
bool Grafo_lista::vertice_ponderado() { return verticesPonderados; }

/**
 * @brief Verifica se as arestas no grafo são ponderadas.
 *
 * Esta função retorna um valor booleano indicando se as arestas
 * no grafo possuem pesos associados.
 *
 * @return true se as arestas são ponderadas, false caso contrário.
 */
bool Grafo_lista::aresta_ponderada() { return arestasPonderadas; }

/**
 * @brief Verifica se o grafo é completo.
 *
 * Um grafo é considerado completo se há uma aresta entre cada par de vértices.
 * Para grafos direcionados, ambas as direções devem ter arestas entre cada par
 * de vértices.
 *
 * @return true se o grafo é completo, false caso contrário.
 */
bool Grafo_lista::eh_completo() {

  if (numNos <= 1) {
    return true;
  }

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {
    int idOrigem = vAtual->getIdVertice();

    NoVertice *vAux = primeiroVertice;
    while (vAux != nullptr) {
      int idDestino = vAux->getIdVertice();

      if (idOrigem != idDestino) {

        bool existeOD = existeAresta(idOrigem, idDestino);
        if (!existeOD) {
          return false;
        }

        if (this->direcionado) {
          bool existeDO = existeAresta(idDestino, idOrigem);
          if (!existeDO) {
            return false;
          }
        }
      }

      vAux = vAux->getProximoVertice();
    }

    vAtual = vAtual->getProximoVertice();
  }

  return true;
}

/**
 * @brief Verifica se o grafo é uma árvore.
 *
 * Esta função verifica se o grafo representado pelo objeto Grafo_lista é uma
 * árvore. Um grafo é considerado uma árvore se for conexo e acíclico.
 *
 * @return true se o grafo é uma árvore, false caso contrário.
 */
bool Grafo_lista::eh_arvore() {

  if (n_conexo() != 1) {
    return false;
  }

  if (tem_ciclo()) {
    return false;
  }

  return true;
}

/**
 * @brief Verifica se o grafo possui algum ponto de articulação.
 *
 * Um ponto de articulação é um vértice que, se removido, aumenta o número de
 * componentes conectados do grafo.
 *
 * @return true se o grafo possui pelo menos um ponto de articulação, false caso
 * contrário.
 */
bool Grafo_lista::possui_articulacao() {

  if (direcionado) {
    return false;
  }

  int *disc = new int[numNos + 1];
  int *low = new int[numNos + 1];
  bool *visitado = new bool[numNos + 1];
  int *pai = new int[numNos + 1];
  bool *articulacao = new bool[numNos + 1];

  for (int i = 1; i <= numNos; i++) {
    disc[i] = -1;
    low[i] = -1;
    visitado[i] = false;
    pai[i] = -1;
    articulacao[i] = false;
  }

  int tempo = 0;

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {
    int idVertice = vAtual->getIdVertice();
    if (!visitado[idVertice]) {
      int filhosRaiz = 0;
      dfs_articulacao(idVertice, tempo, disc, low, visitado, pai, articulacao,
                      filhosRaiz);

      if (filhosRaiz > 1) {
        articulacao[idVertice] = true;
      }
    }
    vAtual = vAtual->getProximoVertice();
  }

  bool existeArticulacao = false;
  for (int i = 1; i <= numNos; i++) {
    if (articulacao[i]) {
      existeArticulacao = true;
      break;
    }
  }

  delete[] disc;
  delete[] low;
  delete[] visitado;
  delete[] pai;
  delete[] articulacao;

  return existeArticulacao;
}

/**
 * @brief Realiza a busca em profundidade (DFS) para encontrar pontos de
 * articulação em um grafo.
 *
 * Esta função utiliza a busca em profundidade (DFS) para identificar pontos de
 * articulação em um grafo. Um ponto de articulação é um vértice que, se
 * removido, aumenta o número de componentes conectados do grafo.
 *
 * @param u O vértice atual sendo visitado.
 * @param tempo Referência para o contador de tempo usado para definir a ordem
 * de descoberta dos vértices.
 * @param disc Array que armazena o tempo de descoberta de cada vértice.
 * @param low Array que armazena o menor tempo de descoberta alcançável a partir
 * de cada vértice.
 * @param visitado Array que indica se um vértice foi visitado ou não.
 * @param pai Array que armazena o pai de cada vértice na árvore DFS.
 * @param articulacao Array que indica se um vértice é um ponto de articulação.
 * @param filhosRaiz Referência para o contador de filhos da raiz na árvore DFS.
 */
void Grafo_lista::dfs_articulacao(int u, int &tempo, int disc[], int low[],
                                  bool visitado[], int pai[],
                                  bool articulacao[], int &filhosRaiz) {

  visitado[u] = true;

  disc[u] = low[u] = ++tempo;

  bool isRoot = (pai[u] == -1);
  if (isRoot) {
    filhosRaiz = 0;
  }

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(u);
  NoLista *atual = vizinhos;
  while (atual != nullptr) {
    int v = atual->idVertice;

    if (!visitado[v]) {
      if (isRoot) {
        filhosRaiz++;
      }
      pai[v] = u;

      dfs_articulacao(v, tempo, disc, low, visitado, pai, articulacao,
                      filhosRaiz);

      low[u] = std::min(low[u], low[v]);

      if (!isRoot && low[v] >= disc[u]) {
        articulacao[u] = true;
      }
    } else if (v != pai[u]) {

      low[u] = std::min(low[u], disc[v]);
    }

    atual = atual->proximo;
  }

  liberarLista(vizinhos);
}

/**
 * @brief Verifica se o grafo possui uma ponte.
 *
 * Uma ponte é uma aresta que, se removida, aumenta o número de componentes
 * conectados do grafo. Esta função utiliza uma busca em profundidade (DFS) para
 * encontrar pontes no grafo.
 *
 * @return true Se o grafo possui pelo menos uma ponte.
 * @return false Se o grafo não possui nenhuma ponte.
 */
bool Grafo_lista::possui_ponte() {

  int *disc = new int[numNos + 1];
  int *low = new int[numNos + 1];
  bool *visitado = new bool[numNos + 1];
  int *pai = new int[numNos + 1];

  for (int i = 1; i <= numNos; i++) {
    disc[i] = -1;
    low[i] = -1;
    visitado[i] = false;
    pai[i] = -1;
  }

  int tempo = 0;

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {
    int idVertice = vAtual->getIdVertice();
    if (!visitado[idVertice]) {
      if (dfs_ponte(idVertice, tempo, disc, low, visitado, pai)) {

        delete[] disc;
        delete[] low;
        delete[] visitado;
        delete[] pai;
        return true;
      }
    }
    vAtual = vAtual->getProximoVertice();
  }

  delete[] disc;
  delete[] low;
  delete[] visitado;
  delete[] pai;
  return false;
}

/**
 * @brief Insere um novo vértice no grafo.
 *
 * Esta função insere um novo vértice no grafo com um identificador e um peso
 * especificado. Se um vértice com o mesmo identificador já existir, a função
 * não faz nada.
 *
 * @param id Identificador do vértice a ser inserido.
 * @param pesoVertice Peso do vértice a ser inserido. O valor padrão é 1.0.
 */
void Grafo_lista::insereVertice(int id, double pesoVertice = 1.0) {

  if (encontraVertice(id) != nullptr)
    return;

  NoVertice *novoV = new NoVertice(id, pesoVertice);
  novoV->setProximoVertice(primeiroVertice);
  primeiroVertice = novoV;
}

/**
 * @brief Insere uma aresta no grafo.
 *
 * Esta função insere uma aresta entre dois vértices no grafo. Se o grafo não
 * for direcionado, a aresta será inserida em ambas as direções (origem ->
 * destino e destino -> origem).
 *
 * @param origem O vértice de origem da aresta.
 * @param destino O vértice de destino da aresta.
 * @param peso O peso da aresta (valor padrão é 1.0).
 *
 * @note Se a aresta já existir ou se a origem for igual ao destino, a função
 * não fará nada.
 * @note Se o vértice de origem ou destino não existir, a função não fará nada.
 */
void Grafo_lista::insereAresta(int origem, int destino, double peso = 1.0) {

  if (origem == destino)
    return;

  if (existeAresta(origem, destino))
    return;

  NoVertice *vOrigem = encontraVertice(origem);
  if (!vOrigem)
    return;

  vOrigem->insereAresta(destino, peso);

  if (!direcionado) {
    NoVertice *vDestino = encontraVertice(destino);
    if (!vDestino)
      return;
    vDestino->insereAresta(origem, peso);
  }
}

/**
 * @brief Encontra um vértice no grafo pelo seu ID.
 *
 * Esta função percorre a lista de vértices do grafo e retorna o vértice
 * cujo ID corresponde ao valor fornecido. Se nenhum vértice com o ID
 * especificado for encontrado, a função retorna nullptr.
 *
 * @param id O ID do vértice a ser encontrado.
 * @return Um ponteiro para o vértice encontrado, ou nullptr se não for
 * encontrado.
 */
NoVertice *Grafo_lista::encontraVertice(int id) {
  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {
    if (vAtual->getIdVertice() == id) {
      return vAtual;
    }
    vAtual = vAtual->getProximoVertice();
  }
  return nullptr;
}

/**
 * @brief Verifica se existe uma aresta entre dois vértices no grafo.
 *
 * Esta função verifica se existe uma aresta que conecta o vértice de origem ao
 * vértice de destino.
 *
 * @param origem O identificador do vértice de origem.
 * @param destino O identificador do vértice de destino.
 * @return true Se existe uma aresta entre os vértices de origem e destino.
 * @return false Se não existe uma aresta entre os vértices de origem e destino.
 */
bool Grafo_lista::existeAresta(int origem, int destino) {
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

/**
 * @brief Limpa o grafo, removendo todos os vértices e arestas.
 *
 * Esta função percorre todos os vértices do grafo e, para cada vértice,
 * percorre todas as suas arestas, deletando-as. Após deletar todas as arestas
 * de um vértice, o próprio vértice é deletado. No final, o ponteiro para o
 * primeiro vértice é definido como nullptr, indicando que o grafo está vazio.
 */
void Grafo_lista::limpaGrafo() {
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

/**
 * @brief Retorna a lista de vizinhos de um vértice, ignorando a direção das
 * arestas.
 *
 * Esta função retorna uma lista de vizinhos de um vértice especificado pelo seu
 * ID, ignorando a direção das arestas. Se o grafo for direcionado, a função
 * também considera as arestas que chegam ao vértice.
 *
 * @param idVert O ID do vértice cujos vizinhos serão retornados.
 * @return Um ponteiro para a lista de vizinhos do vértice especificado.
 */
Grafo_lista::NoLista *Grafo_lista::getVizinhosIgnorandoDirecao(int idVert) {
  Grafo_lista::NoLista *vizinhos = nullptr;

  NoVertice *vOrigem = encontraVertice(idVert);
  if (vOrigem != nullptr) {

    NoAresta *aAtual = vOrigem->getPrimeiraAresta();
    while (aAtual != nullptr) {

      Grafo_lista::NoLista *novoVizinho =
          new Grafo_lista::NoLista(aAtual->getIdVertice());
      novoVizinho->proximo = vizinhos;
      vizinhos = novoVizinho;
      aAtual = aAtual->getProxima();
    }
  }

  if (this->direcionado) {
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr) {
      NoAresta *aAtual = vAtual->getPrimeiraAresta();
      while (aAtual != nullptr) {
        if (aAtual->getIdVertice() == idVert) {
          Grafo_lista::NoLista *novoVizinho =
              new Grafo_lista::NoLista(vAtual->getIdVertice());
          novoVizinho->proximo = vizinhos;
          vizinhos = novoVizinho;
        }
        aAtual = aAtual->getProxima();
      }
      vAtual = vAtual->getProximoVertice();
    }
  }

  return vizinhos;
}

/**
 * @brief Libera a memória alocada para uma lista encadeada.
 *
 * Esta função percorre uma lista encadeada de nós do tipo NoLista e libera a
 * memória alocada para cada nó, evitando vazamentos de memória.
 *
 * @param lista Ponteiro para o primeiro nó da lista encadeada a ser liberada.
 */
void Grafo_lista::liberarLista(NoLista *lista) {
  while (lista != nullptr) {
    NoLista *temp = lista;
    lista = lista->proximo;
    delete temp;
  }
}

/**
 * @brief Realiza uma busca em profundidade (DFS) para marcar os vértices de uma
 * componente conexa.
 *
 * Esta função marca todos os vértices que pertencem à mesma componente conexa
 * que o vértice dado.
 *
 * @param idVertice O identificador do vértice inicial.
 * @param visitado Array booleano que indica se um vértice foi visitado ou não.
 */
void Grafo_lista::dfs_marcar_componente(int idVertice, bool visitado[]) {

  visitado[idVertice] = true;

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(idVertice);

  NoLista *atual = vizinhos;
  while (atual != nullptr) {
    if (!visitado[atual->idVertice]) {
      dfs_marcar_componente(atual->idVertice, visitado);
    }
    atual = atual->proximo;
  }

  liberarLista(vizinhos);
}

/**
 * @brief Verifica se o grafo contém um ciclo.
 *
 * Esta função percorre todos os vértices do grafo e utiliza uma busca em
 * profundidade (DFS) para detectar ciclos. Se um ciclo for encontrado, a função
 * retorna true. Caso contrário, retorna false.
 *
 * @return true se o grafo contém um ciclo, false caso contrário.
 */
bool Grafo_lista::tem_ciclo() {

  bool *visitado = new bool[numNos + 1];
  for (int i = 1; i <= numNos; i++) {
    visitado[i] = false;
  }

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr) {
    int idVertice = vAtual->getIdVertice();

    if (!visitado[idVertice]) {
      if (dfs_detecta_ciclo(idVertice, visitado, -1)) {
        delete[] visitado;
        return true;
      }
    }

    vAtual = vAtual->getProximoVertice();
  }

  delete[] visitado;

  return false;
}

/**
 * @brief Realiza uma busca em profundidade (DFS) para detectar ciclos em um
 * grafo.
 *
 * Esta função utiliza a técnica de DFS para verificar se há ciclos no grafo.
 * Ela marca os vértices visitados e verifica se há uma aresta de retorno que
 * indica a presença de um ciclo.
 *
 * @param idVertice O identificador do vértice atual sendo visitado.
 * @param visitado Um array booleano que indica se um vértice foi visitado.
 * @param pai O identificador do vértice pai do vértice atual.
 * @return true Se um ciclo for detectado no grafo.
 * @return false Se nenhum ciclo for detectado no grafo.
 */
bool Grafo_lista::dfs_detecta_ciclo(int idVertice, bool visitado[], int pai) {

  visitado[idVertice] = true;

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(idVertice);

  NoLista *atual = vizinhos;
  while (atual != nullptr) {
    int vizinho = atual->idVertice;

    if (!visitado[vizinho]) {
      if (dfs_detecta_ciclo(vizinho, visitado, idVertice)) {
        liberarLista(vizinhos);
        return true;
      }
    }

    else if (vizinho != pai) {
      liberarLista(vizinhos);
      return true;
    }

    atual = atual->proximo;
  }

  liberarLista(vizinhos);

  return false;
}

/**
 * @brief Realiza uma busca em profundidade (DFS) para encontrar pontes em um
 * grafo.
 *
 * Esta função utiliza a técnica de DFS para identificar pontes em um grafo. Uma
 * ponte é uma aresta que, se removida, aumenta o número de componentes
 * conectados do grafo.
 *
 * @param u O vértice atual sendo visitado.
 * @param tempo Referência para o tempo de descoberta dos vértices.
 * @param disc Array que armazena o tempo de descoberta de cada vértice.
 * @param low Array que armazena o menor tempo de descoberta acessível a partir
 * do vértice.
 * @param visitado Array que indica se um vértice já foi visitado.
 * @param pai Ponteiro para o vértice pai no DFS.
 * @return true se uma ponte foi encontrada, false caso contrário.
 */
bool Grafo_lista::dfs_ponte(int u, int &tempo, int disc[], int low[],
                            bool visitado[], int pai[]) {

  // Marca o vértice como visitado
  visitado[u] = true;

  // Inicializa discovery time e low-link value
  disc[u] = low[u] = ++tempo;

  // Obtém a lista de vizinhos
  NoLista *vizinhos = getVizinhosIgnorandoDirecao(u);
  NoLista *atual = vizinhos;

  while (atual != nullptr) {
    int v = atual->idVertice;

    // Se o vizinho não foi visitado, processa recursivamente
    if (!visitado[v]) {
      pai[v] = u;

      if (dfs_ponte(v, tempo, disc, low, visitado, pai)) {
        liberarLista(vizinhos);
        return true;
      }

      // Atualiza o low-link value do vértice atual
      low[u] = std::min(low[u], low[v]);

      // Condição para identificar uma ponte
      if (low[v] > disc[u]) {
        liberarLista(vizinhos);
        return true; // Encontramos uma ponte
      }
    }
    // Se já foi visitado, atualiza o low-link value para arestas de retorno
    else if (v != pai[u]) {
      low[u] = std::min(low[u], disc[v]);
    }

    atual = atual->proximo;
  }

  liberarLista(vizinhos);
  return false;
}
