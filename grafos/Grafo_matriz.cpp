#include "Grafo_matriz.h"
#include "Grafo.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Construtor do objeto Grafo_matriz
 *
 * Este construtor inicializa um grafo representado por uma matriz de
 * adjacência.
 *
 * @param n O número de vértices no grafo. Deve ser maior que 0.
 * @param dir Um booleano indicando se o grafo é direcionado (true) ou não
 * (false).
 * @param pondArestas Um booleano indicando se as arestas são ponderadas (true)
 * ou não (false).
 * @param pondVertices Um booleano indicando se os vértices são ponderados
 * (true) ou não (false).
 *
 * @note Se o número de vértices (n) for menor ou igual a 0, uma mensagem de
 * erro é impressa e o construtor retorna sem inicializar o grafo.
 */
Grafo_matriz::Grafo_matriz(int n, bool dir, bool pondArestas,
                           bool pondVertices) {
  if (n <= 0) {
    cerr << "Número de vértices inválido" << endl;
    return;
  }

  numNos = n;
  direcionado = dir;
  arestas_ponderadas = pondArestas;
  vertices_ponderados = pondVertices;

  pesoNos = new float[numNos];

  matriz = new int *[numNos];
  for (int i = 0; i < numNos; i++) {
    matriz[i] = new int[numNos];

    for (int j = 0; j < numNos; j++) {
      matriz[i][j] = 0.0;
    }
  }
}

/**
 * @brief Destrutor da classe Grafo_matriz.
 *
 * Este destrutor é responsável por desalocar a memória alocada dinamicamente
 * usada pela matriz de adjacência e pelo array de pesos dos nós. Ele itera
 * por cada linha da matriz de adjacência e a deleta, depois deleta o array de
 * ponteiros de linha, e finalmente deleta o array de pesos dos nós.
 */
Grafo_matriz::~Grafo_matriz() {

  for (int i = 0; i < numNos; i++) {
    delete[] matriz[i];
  }
  delete[] matriz;

  delete[] pesoNos;
}

/**
 * @brief Insere um vértice no grafo com um peso associado.
 *
 * @param id Identificador do vértice a ser inserido.
 * @param peso Peso associado ao vértice.
 *
 * @details Esta função insere um vértice no grafo, atribuindo um peso ao
 * vértice se o grafo for ponderado. Se o identificador do vértice for inválido
 * (menor que 0 ou maior ou igual ao número de nós), uma mensagem de erro será
 * exibida.
 */
void Grafo_matriz::insereVertice(int id, int peso) {
  if (id < 0 || id >= numNos) {
    cerr << "ID do vértice inválido." << std::endl;
    return;
  }
  if (verticesPonderados) {
    pesoNos[id] = peso;
  }
}

/**
 * @brief Adiciona uma aresta ao grafo.
 *
 * Esta função adiciona uma aresta entre dois nós no grafo, com um peso
 * especificado. Se o grafo não for direcionado, a aresta é adicionada em ambas
 * as direções.
 *
 * @param origem O índice do nó de origem.
 * @param destino O índice do nó de destino.
 * @param peso O peso da aresta.
 *
 * @note Se a origem ou o destino forem inválidos (fora dos limites do grafo),
 *       uma mensagem de erro será exibida e a função retornará sem adicionar a
 * aresta.
 */
void Grafo_matriz::adicionaAresta(int origem, int destino, int peso) {
  if (origem < 0 || origem >= numNos || destino < 0 || destino >= numNos) {
    std::cerr << "Origem ou destino inválido." << std::endl;
    return;
  }

  matriz[origem][destino] = peso;

  if (!direcionado) {
    matriz[destino][origem] = peso;
  }
}

/**
 * @brief Verifica se existe uma aresta entre dois nós no grafo.
 *
 * Esta função verifica se existe uma aresta entre o nó na posição de origem
 * especificada e o nó na posição de destino especificada na representação
 * da matriz de adjacência do grafo.
 *
 * @param origem O índice do nó de origem.
 * @param destino O índice do nó de destino.
 * @return true se existir uma aresta entre os nós de origem e destino, false
 * caso contrário.
 */
bool Grafo_matriz::existeAresta(int origem, int destino) {
  if (origem < 0 || origem >= numNos || destino < 0 || destino >= numNos) {
    return false;
  }

  return matriz[origem][destino] != 0;
}

/**
 * @brief Carrega um grafo a partir de um arquivo.
 *
 * Esta função lê um grafo de um arquivo especificado e inicializa a matriz de
 * adjacência do grafo. O arquivo deve conter a seguinte estrutura:
 * - Primeira linha: número de nós, indicador de direcionamento (1 para
 * direcionado, 0 para não direcionado), indicador de vértices ponderados (1
 * para ponderado, 0 para não ponderado), indicador de arestas ponderadas (1
 * para ponderado, 0 para não ponderado).
 * - Se os vértices forem ponderados, as próximas linhas conterão os pesos dos
 * vértices.
 * - As linhas seguintes conterão as arestas no formato: origem destino [peso]
 * (o peso é opcional e só é lido se as arestas forem ponderadas).
 *
 * @param arquivo O caminho para o arquivo que contém a descrição do grafo.
 */
void Grafo_matriz::carrega_grafo(const string &arquivo) {
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

  matriz = new int *[numNos];
  for (int i = 0; i < numNos; i++) {
    matriz[i] = new int[numNos];
    fill_n(matriz[i], numNos, 0);
  }

  if (verticesPonderados) {
    for (int i = 0; i < numNos; i++) {
      int pesoVert;
      fin >> pesoVert;
      if (!fin.good()) {
        cerr << "Erro ao ler peso do vertice " << i << endl;
        return;
      }
    }
  }

  numArestas = 0;
  while (true) {
    int origem, destino;
    int peso = 1.0;
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

    adicionaAresta(origem - 1, destino - 1, peso);
    numArestas++;
  }

  fin.close();
}

bool Grafo_matriz::possui_articulacao() { return false; }

/**
 * @brief Cria um novo grafo a partir de um arquivo de descrição e salva em um
 * arquivo de saída.
 *
 * Esta função lê a descrição de um grafo a partir de um arquivo de entrada,
 * inicializa a matriz de adjacência do grafo e, se especificado, cria um grafo
 * completo. Em seguida, salva a representação do grafo em um arquivo de saída.
 *
 * @param descricao Caminho para o arquivo de descrição do grafo.
 * @param arquivoSaida Caminho para o arquivo onde o grafo será salvo.
 *
 * O arquivo de descrição deve conter os seguintes valores na primeira linha:
 * - grau: Grau do grafo (não utilizado na função).
 * - ordem: Número de vértices do grafo.
 * - dir: Indica se o grafo é direcionado (1) ou não (0).
 * - compConexas: Número de componentes conexas (não utilizado na função).
 * - vPond: Indica se os vértices são ponderados (1) ou não (0).
 * - aPond: Indica se as arestas são ponderadas (1) ou não (0).
 * - completo: Indica se o grafo é completo (1) ou não (0).
 * - bipartido: Indica se o grafo é bipartido (não utilizado na função).
 * - arvore: Indica se o grafo é uma árvore (não utilizado na função).
 * - aPonte: Indica se há arestas ponte (não utilizado na função).
 * - vArti: Indica se há vértices de articulação (não utilizado na função).
 *
 * O arquivo de saída conterá a representação do grafo no seguinte formato:
 * - Primeira linha: ordem, dir, vPond, aPond.
 * - Linhas subsequentes: arestas no formato "vértice1 vértice2 [peso]".
 */
void Grafo_matriz::novo_grafo(const string &descricao,
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

  numNos = ordem;
  matriz = new int *[numNos];
  for (int i = 0; i < numNos; i++) {
    matriz[i] = new int[numNos];
    fill(matriz[i], matriz[i] + numNos, 0);
  }

  srand((unsigned)time(nullptr));
  for (int i = 0; i < ordem; i++) {
    double peso = (verticesPonderados) ? (double)(rand() % 10 + 1) : 1.0;
  }

  if (completo) {

    for (int i = 0; i < ordem; i++) {
      for (int j = i + 1; j < ordem; j++) {
        if (!direcionado) {
          adicionaAresta(i, j,
                         arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        } else {
          adicionaAresta(i, j,
                         arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
          adicionaAresta(j, i,
                         arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        }
      }
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

  for (int i = 0; i < ordem; i++) {
    for (int j = 0; j < ordem; j++) {
      if (matriz[i][j] != 0) {
        fout << i + 1 << " " << j + 1;
        if (arestasPonderadas) {
          fout << " " << matriz[i][j];
        }
        fout << endl;
      }
    }
  }

  fout.close();
}

/**
 * @brief Limpa o grafo, removendo todas as arestas.
 *
 * Esta função redefine todos os valores da matriz de adjacência para 0.0,
 * indicando que não há arestas entre os nós. Além disso, redefine o número
 * de arestas para 0.
 *
 * @note Esta função assume que a matriz de adjacência já foi alocada e que
 *       numNos contém o número correto de nós no grafo.
 */
void Grafo_matriz::limpaGrafo() {
  for (int i = 0; i < numNos; i++) {
    for (int j = 0; j < numNos; j++) {
      matriz[i][j] = 0.0;
    }
  }

  numArestas = 0;
}

/**
 * @brief Verifica se o grafo representado pela matriz de adjacência é
 * bipartido.
 *
 * Um grafo é bipartido se os seus vértices puderem ser divididos em dois
 * conjuntos disjuntos tais que não haja arestas entre vértices do mesmo
 * conjunto.
 *
 * @return true se o grafo é bipartido, false caso contrário.
 */
bool Grafo_matriz::eh_bipartido() {
  int *cores = new int[numNos];
  for (int i = 0; i < numNos; i++) {
    cores[i] = -1;
  }

  int *fila = new int[numNos];
  int frente = 0;
  int tras = 0;

  for (int i = 0; i < numNos; i++) {
    if (cores[i] == -1) {
      fila[tras++] = i;
      cores[i] = 0;

      while (frente < tras) {
        int u = fila[frente++];

        for (int v = 0; v < numNos; v++) {
          if (matriz[u][v] != 0) {
            if (cores[v] == -1) {
              cores[v] = 1 - cores[u];
              fila[tras++] = v;
            } else if (cores[v] == cores[u]) {

              delete[] cores;
              delete[] fila;
              return false;
            }
          }
        }
      }
    }
  }

  delete[] cores;
  delete[] fila;
  return true;
}

/**
 * @brief Verifica se o grafo é uma árvore.
 *
 * Esta função verifica se o grafo representado pela matriz de adjacência é uma
 * árvore. Um grafo é considerado uma árvore se for conexo e tiver exatamente
 * (número de nós - 1) arestas.
 *
 * @return true se o grafo é uma árvore, false caso contrário.
 */
bool Grafo_matriz::eh_arvore() {

  int componentesConexos = n_conexo();
  if (componentesConexos > 1) {
    return false;
  }

  if (numArestas != numNos - 1) {
    return false;
  }

  return true;
}

/**
 * @brief Determina o número de componentes conexas no grafo.
 *
 * Esta função utiliza a Busca em Profundidade (DFS) para percorrer o grafo e
 * contar o número de componentes conexas. Ela inicializa um array booleano para
 * rastrear os nós visitados, itera por cada nó e realiza uma DFS se o nó não
 * tiver sido visitado. Cada travessia DFS corresponde a uma nova componente
 * conexa.
 *
 * @return int O número de componentes conexas no grafo.
 */
int Grafo_matriz::n_conexo() {

  bool *visitado = new bool[numNos];
  for (int i = 0; i < numNos; ++i) {
    visitado[i] = false;
  }

  int numComponentes = 0;

  for (int i = 0; i < numNos; ++i) {

    if (!visitado[i]) {
      ++numComponentes;

      dfs(i, visitado);
    }
  }

  delete[] visitado;
  return numComponentes;
}

/**
 * @brief Realiza uma busca em profundidade (DFS) a partir de um vértice dado.
 *
 * Esta função marca o vértice atual como visitado e, em seguida, recursivamente
 * visita todos os vértices adjacentes que ainda não foram visitados.
 *
 * @param vertice O vértice inicial a partir do qual a DFS será realizada.
 * @param visitado Um array booleano que mantém o controle dos vértices
 * visitados.
 */
void Grafo_matriz::dfs(int vertice, bool *visitado) {

  visitado[vertice] = true;

  for (int i = 0; i < numNos; ++i) {
    if (matriz[vertice][i] != 0 && !visitado[i]) {
      dfs(i, visitado);
    }
  }
}

/**
 * @brief Verifica se o grafo é completo.
 *
 * Um grafo é considerado completo se houver uma aresta entre cada par de nós
 * distintos.
 *
 * @return true se o grafo é completo, false caso contrário.
 */
bool Grafo_matriz::eh_completo() {

  for (int i = 0; i < numNos; ++i) {
    for (int j = 0; j < numNos; ++j) {

      if (i != j && matriz[i][j] == 0) {
        return false;
      }
    }
  }

  return true;
}

/**
 * @brief Verifica se o grafo contém uma ponte.
 *
 * Uma ponte (ou aresta de corte) é uma aresta em um grafo cuja remoção aumenta
 * o número de componentes conexas. Esta função itera por todas as arestas na
 * matriz de adjacência, remove temporariamente cada aresta e verifica se o
 * grafo se torna desconexo. Se a remoção de qualquer aresta causar a desconexão
 * do grafo, a função retorna true, indicando a presença de uma ponte.
 *
 * @return true se o grafo contém pelo menos uma ponte.
 * @return false se o grafo não contém nenhuma ponte.
 */
bool Grafo_matriz::possui_ponte() {
  for (int u = 0; u < numNos; ++u) {
    for (int v = 0; v < numNos; ++v) {

      if (matriz[u][v] != 0) {

        int pesoOriginal = matriz[u][v];
        matriz[u][v] = 0;
        if (!direcionado) {
          matriz[v][u] = 0;
        }

        bool *visitado = new bool[numNos];
        for (int i = 0; i < numNos; ++i) {
          visitado[i] = false;
        }

        dfs(0, visitado);

        bool desconexo = false;
        for (int i = 0; i < numNos; ++i) {
          if (!visitado[i]) {
            desconexo = true;
            break;
          }
        }

        delete[] visitado;

        matriz[u][v] = pesoOriginal;
        if (!direcionado) {
          matriz[v][u] = pesoOriginal;
        }

        if (desconexo) {
          return true;
        }
      }
    }
  }
  return false;
}

/**
 * @brief Verifica se o grafo possui arestas ponderadas.
 *
 * Esta função retorna um valor booleano indicando se as arestas
 * do grafo são ponderadas ou não.
 *
 * @return true se as arestas são ponderadas, false caso contrário.
 */
bool Grafo_matriz::aresta_ponderada() { return arestasPonderadas; }

/**
 * @brief Verifica se o grafo possui vértices ponderados.
 *
 * Esta função retorna um valor booleano indicando se os vértices
 * do grafo são ponderados ou não.
 *
 * @return true se os vértices são ponderados, false caso contrário.
 */
bool Grafo_matriz::vertice_ponderado() { return verticesPonderados; }

/**
 * @brief Verifica se o grafo é direcionado.
 *
 * Esta função retorna um valor booleano indicando se o grafo é direcionado.
 *
 * @return true se o grafo for direcionado, false caso contrário.
 */
bool Grafo_matriz::eh_direcionado() { return direcionado; }

/**
 * @brief Obtém o grau do grafo.
 *
 * Esta função retorna o número de arestas (numArestas) no grafo,
 * que representa o grau do grafo.
 *
 * @return int O número de arestas no grafo.
 */
int Grafo_matriz::get_grau() { return numArestas; }

/**
 * @brief Obtém a ordem do grafo.
 *
 * Esta função retorna o número de nós (vértices) no grafo.
 *
 * @return int O número de nós no grafo.
 */
int Grafo_matriz::get_ordem() { return numNos; }
