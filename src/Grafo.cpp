#include "../include/Grafo.hpp"
#include "../include/IntList.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <ctime>

using namespace std;
const double INF = 1e9;

void Grafo::carrega_grafo(const string &nomeArquivo) {
  cout << "Carregando: " << nomeArquivo << endl;

  ifstream arquivo(nomeArquivo, ios::in | ios::binary);
  if (!arquivo) {
    cerr << "Erro ao abrir o arquivo " << nomeArquivo << "\n";
    return;
  }

  arquivo.rdbuf()->pubsetbuf(
      nullptr, 1024 * 1024); // Define buffer para leitura mais rápida

  // Lê informações do cabeçalho do grafo
  arquivo >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;

  // Criar os vértices com pesos se necessário
  int peso;
  for (int i = 1; i <= ordem; i++) {
    peso = (ponderadoVertices ? (arquivo >> peso, peso) : 0);
    inserir_vertice(i, peso);
  }

  // Lê as arestas
  int origem, destino;
  while (arquivo >> origem >> destino) {
    peso = (ponderadoArestas ? (arquivo >> peso, peso) : 1);
    inserir_aresta(origem, destino, peso);
  }

  arquivo.close();
}

// void Grafo::carrega_grafo(const string &nomeArquivo) {

//   cout << nomeArquivo.c_str() << endl;
//   ifstream arquivo(nomeArquivo.c_str());
//   if (!arquivo) {
//     cerr << "Erro ao abrir o arquivo " << nomeArquivo << "\n";
//     return;
//   }
//   arquivo >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;

//   // Insere os vértices
//   if (ponderadoVertices) {
//     for (int i = 1; i <= ordem; i++) {
//       int peso;
//       arquivo >> peso;
//       inserir_vertice(i, peso);
//     }
//   } else {
//     for (int i = 1; i <= ordem; i++) {
//       inserir_vertice(i, 0);
//     }
//   }

//   // Lê as arestas
//   int origem, destino, peso;
//   while (arquivo >> origem >> destino) {
//     if (ponderadoArestas) {
//       arquivo >> peso;
//       inserir_aresta(origem, destino, peso);
//     } else {
//       // Para grafos não ponderados, usar 1 para indicar a presença da aresta
//       inserir_aresta(origem, destino, 1);
//     }
//   }

//   arquivo.close();
// }

// Retorna o grau (ou grau máximo) do grafo.
// Para grafos direcionados, considera a soma do outdegree e indegree.
int Grafo::get_grau() const {
  int max_grau = 0;
  for (int i = 1; i <= ordem; i++) {
    IntList vizinhos = get_vizinhos(i);
    int out_deg = vizinhos.size();
    int in_deg = 0;
    for (int j = 1; j <= ordem; j++) {
      if (j == i)
        continue;
      IntList viz = get_vizinhos(j);
      for (int k = 0; k < viz.size(); k++) {
        if (viz.get(k) == i) {
          in_deg++;
          break;
        }
      }
    }
    int total = (direcionado ? (out_deg + in_deg) : out_deg);
    if (total > max_grau)
      max_grau = total;
  }
  return max_grau;
}

// Função auxiliar DFS para marcar os vértices alcançados (desconsidera a
// direção)
void dfs_util(const Grafo *g, int v, bool *visitado) {
  visitado[v] = true;
  IntList viz = g->get_vizinhos(v);
  for (int i = 0; i < viz.size(); i++) {
    int w = viz.get(i);
    if (!visitado[w])
      dfs_util(g, w, visitado);
  }
  // Para garantir a conectividade em grafos direcionados, varre os vértices que
  // apontam para v
  for (int i = 1; i <= g->get_ordem(); i++) {
    if (!visitado[i]) {
      IntList viz_i = g->get_vizinhos(i);
      for (int j = 0; j < viz_i.size(); j++) {
        if (viz_i.get(j) == v) {
          dfs_util(g, i, visitado);
          break;
        }
      }
    }
  }
}

// Retorna o número de componentes conexas
int Grafo::n_conexo() const {
  bool *visitado = new bool[ordem + 1];
  for (int i = 0; i <= ordem; i++)
    visitado[i] = false;
  int count = 0;
  for (int i = 1; i <= ordem; i++) {
    if (!visitado[i]) {
      dfs_util(this, i, visitado);
      count++;
    }
  }
  delete[] visitado;
  return count;
}

// Verifica se o grafo é completo
bool Grafo::eh_completo() const {
  for (int i = 1; i <= ordem; i++) {
    IntList viz = get_vizinhos(i);
    if (!direcionado) {
      if (viz.size() != ordem - 1)
        return false;
    } else {
      if (viz.size() != ordem - 1)
        return false;
      int in_deg = 0;
      for (int j = 1; j <= ordem; j++) {
        if (j == i)
          continue;
        IntList viz_j = get_vizinhos(j);
        for (int k = 0; k < viz_j.size(); k++) {
          if (viz_j.get(k) == i) {
            in_deg++;
            break;
          }
        }
      }
      if (in_deg != ordem - 1)
        return false;
    }
  }
  return true;
}

Grafo::ResultadoDistancia Grafo::calculaMaiorMenorDistancia() const {
  int n = get_ordem();

  if (n <= 0) {
    ResultadoDistancia res = {-1, -1, -1};
    return res;
  }

  // Aloca uma matriz de distâncias (usando índices 0-based internamente)
  double **dist = new double *[n];
  for (int i = 0; i < n; i++) {
    dist[i] = new double[n];
  }

  // Inicializa a matriz de distâncias
  // Usando os métodos virtuais
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) {
        dist[i - 1][j - 1] = 0;
      } else {
        double peso =
            getPesoAresta(i, j); // deve retornar INF se não houver aresta
        dist[i - 1][j - 1] = peso;
      }
    }
  }

  // Aplica o algoritmo de Floyd–Warshall
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }

  // Procura o par de nós com o maior dos menores caminhos (ignorando os casos
  // sem conexão)
  double maxDist = -1e9;
  int bestI = -1, bestJ = -1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && dist[i][j] < INF && dist[i][j] > maxDist) {
        maxDist = dist[i][j];
        bestI = i;
        bestJ = j;
      }
    }
  }

  // Libera a memória alocada para a matriz de distâncias
  for (int i = 0; i < n; i++) {
    delete[] dist[i];
  }
  delete[] dist;

  ResultadoDistancia res;
  res.no1 = (bestI != -1 ? bestI + 1 : -1);
  res.no2 = (bestJ != -1 ? bestJ + 1 : -1);
  res.distancia = maxDist;
  return res;
}

void Grafo::coloracaoGulosa() {
  clock_t inicio = clock();

  int n = get_ordem();
  if (n == 0) {
    cout << "Grafo vazio! Nenhuma cor necessária." << endl;
    return;
  }

  int *cores = new int[n];
  bool *disponivel = new bool[n];

  for (int i = 0; i < n; i++) {
    cores[i] = -1;
    disponivel[i] = true;
  }

  for (int u = 0; u < n; u++) {
    IntList vizinhos = get_vizinhos(u + 1);

    for (int i = 0; i < vizinhos.size(); i++) {
      int v = vizinhos.get(i) - 1;
      if (v >= 0 && v < n && cores[v] != -1)
        disponivel[cores[v]] = false;
    }

    for (int c = 0; c < n; c++) {
      if (disponivel[c]) {
        cores[u] = c;
        break;
      }
    }

    for (int i = 0; i < vizinhos.size(); i++) {
      int v = vizinhos.get(i) - 1;
      if (v >= 0 && v < n && cores[v] != -1)
        disponivel[cores[v]] = true;
    }
  }

  int maxColor = 0;
  for (int i = 0; i < n; i++)
    if (cores[i] > maxColor)
      maxColor = cores[i];

  delete[] cores;
  delete[] disponivel;

  clock_t fim = clock();
  double tempoExecucao = double(fim - inicio) / CLOCKS_PER_SEC;

  cout << "Número total de cores usadas (Guloso): " << (maxColor + 1) << endl;
  cout << "Tempo de execução (Guloso): " << tempoExecucao << " segundos"
       << endl;
}

void Grafo::coloracaoRandomizada(int iteracoes) {
  clock_t inicio = clock();

  int n = get_ordem();
  if (n == 0) {
    cout << "Grafo vazio! Nenhuma cor necessária." << endl;
    return;
  }

  int *cores = new int[n];
  bool *disponivel = new bool[n];
  int minCores = n;

  srand(time(nullptr));

  for (int it = 0; it < iteracoes; it++) {
    for (int i = 0; i < n; i++) {
      cores[i] = -1;
      disponivel[i] = true;
    }

    for (int u = 0; u < n; u++) {
      IntList vizinhos = get_vizinhos(u + 1);

      for (int i = 0; i < vizinhos.size(); i++) {
        int v = vizinhos.get(i) - 1;
        if (v >= 0 && v < n && cores[v] != -1)
          disponivel[cores[v]] = false;
      }

      int K = max(1, vizinhos.size() / 2 + 1);
      int corEscolhida = rand() % K;
      for (int c = 0; c < n; c++) {
        if (disponivel[c]) {
          corEscolhida = (rand() % 2 == 0) ? corEscolhida : c;
          break;
        }
      }
      cores[u] = corEscolhida;

      for (int i = 0; i < vizinhos.size(); i++) {
        int v = vizinhos.get(i) - 1;
        if (v >= 0 && v < n && cores[v] != -1)
          disponivel[cores[v]] = true;
      }
    }

    // Encontrando a maior cor usada sem `max_element`
    int coresUsadas = 0;
    for (int i = 0; i < n; i++) {
      if (cores[i] > coresUsadas)
        coresUsadas = cores[i];
    }
    coresUsadas++; // Adiciona 1 pois as cores começam de 0

    if (coresUsadas < minCores) {
      minCores = coresUsadas;
    }
  }

  delete[] cores;
  delete[] disponivel;

  clock_t fim = clock();
  double tempoExecucao = double(fim - inicio) / CLOCKS_PER_SEC;

  cout << "Número total de cores usadas (Randomizado): " << minCores << endl;
  cout << "Tempo de execução (Randomizado): " << tempoExecucao << " segundos"
       << endl;
}

void Grafo::coloracaoReativa(int iteracoes, double alpha) {
  clock_t inicio = clock();
  int n = get_ordem();

  if (n == 0) {
    cout << "Grafo vazio! Nenhuma cor necessária." << endl;
    return;
  }

  int *cores = new int[n];
  bool *disponivel = new bool[n];
  int minCores = n;
  double melhorAlpha = alpha;
  srand(time(nullptr));

  for (int it = 0; it < iteracoes; it++) {
    for (int i = 0; i < n; i++) {
      cores[i] = -1;
      disponivel[i] = true;
    }

    for (int u = 0; u < n; u++) {
      IntList vizinhos = get_vizinhos(u + 1);

      // Marca cores usadas pelos vizinhos
      for (int i = 0; i < vizinhos.size(); i++) {
        int v = vizinhos.get(i) - 1;
        if (v >= 0 && v < n && cores[v] != -1)
          disponivel[cores[v]] = false;
      }

      // **Define um número máximo de cores baseado em alpha**
      int limiteCores = max(1, int(n * alpha));
      int melhorCor = -1;
      int opcoes[5]; // Até 5 cores possíveis
      int numOpcoes = 0;

      // **Escolher algumas cores disponíveis aleatoriamente**
      for (int c = 0; c < limiteCores && numOpcoes < 5; c++) {
        if (disponivel[c]) {
          opcoes[numOpcoes++] = c;
        }
      }

      // **Escolhe uma cor aleatória dentre as opções disponíveis**
      if (numOpcoes > 0) {
        melhorCor = opcoes[rand() % numOpcoes];
      } else {
        // Caso extremo: escolher uma cor aleatória dentro do limite
        melhorCor = rand() % limiteCores;
      }

      cores[u] = melhorCor;

      // **Reseta cores para o próximo nó**
      for (int i = 0; i < vizinhos.size(); i++) {
        int v = vizinhos.get(i) - 1;
        if (v >= 0 && v < n && cores[v] != -1)
          disponivel[cores[v]] = true;
      }
    }

    // **Melhor contagem das cores usadas**
    int coresUsadas = 0;
    int maxCor = 0;
    for (int i = 0; i < n; i++) {
      if (cores[i] > maxCor)
        maxCor = cores[i];
    }
    coresUsadas = maxCor + 1;

    // **Atualiza o menor número de cores encontradas**
    if (coresUsadas < minCores) {
      minCores = coresUsadas;
      melhorAlpha = alpha;
    }

    // **Ajuste mais equilibrado do Alpha**
    if (coresUsadas > minCores + 10) {
      alpha *= 0.94; // Reduz alpha se piorou muito
    } else if (coresUsadas > minCores) {
      alpha *= 0.97; // Pequena redução se piorou levemente
    } else {
      alpha *= 1.02; // Pequeno aumento se está estável
    }

    // **Evita que alpha fique muito pequeno ou muito grande**
    if (alpha < 0.2)
      alpha = 0.2;
    if (alpha > 0.7)
      alpha = 0.7;
  }

  delete[] cores;
  delete[] disponivel;

  clock_t fim = clock();
  double tempoExecucao = double(fim - inicio) / CLOCKS_PER_SEC;

  cout << "Número total de cores usadas (Reativo): " << minCores << endl;
  cout << "Melhor Alpha encontrado: " << melhorAlpha << endl;
  cout << "Tempo de execução (Reativo): " << tempoExecucao << " segundos"
       << endl;
}
