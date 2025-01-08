#include "Grafo.h"

#include "Grafo_lista.h"
#include "no_Aresta.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Grafo_lista::Grafo_lista()
    : primeiroVertice(nullptr), numNos(0), pesoNos(nullptr),
      direcionado(false), verticesPonderados(false), arestasPonderadas(false),
      numArestas(0), visitado(nullptr), componentes(nullptr), numComponentes(0) {}

Grafo_lista::~Grafo_lista()
{

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {

    NoAresta *aAtual = vAtual->getPrimeiraAresta();
    while (aAtual != nullptr)
    {
      NoAresta *aDel = aAtual;
      aAtual = aAtual->getProxima();
      delete aDel;
    }

    NoVertice *vDel = vAtual;
    vAtual = vAtual->getProximoVertice();
    delete vDel;
  }
}

void Grafo_lista::carrega_grafo(const string &arquivo)
{
  ifstream fin(arquivo.c_str());
  if (!fin.is_open())
  {
    cerr << "Erro ao abrir arquivo " << arquivo << endl;
    return;
  }

  int dir, vPond, aPond;
  fin >> numNos >> dir >> vPond >> aPond;
  if (!fin.good())
  {
    cerr << "Erro ao ler a primeira linha de " << arquivo << endl;
    return;
  }

  direcionado = (dir == 1);
  verticesPonderados = (vPond == 1);
  arestasPonderadas = (aPond == 1);

  if (verticesPonderados)
  {
    for (int i = 0; i < numNos; i++)
    {
      double pesoVert;
      fin >> pesoVert;
      if (!fin.good())
      {
        cerr << "Erro ao ler peso do vertice " << i << endl;
        return;
      }
      insereVertice(i + 1, pesoVert);
    }
  }
  else
  {

    for (int i = 0; i < numNos; i++)
    {
      insereVertice(i + 1, 1.0);
    }
  }

  numArestas = 0;
  while (true)
  {
    int origem, destino;
    double peso = 1.0;
    fin >> origem >> destino;
    if (!fin.good())
    {
      break;
    }
    if (arestasPonderadas)
    {
      fin >> peso;
      if (!fin.good())
      {
        break;
      }
    }

    insereAresta(origem, destino, peso);
    numArestas++;
  }

  fin.close();
}

void Grafo_lista::novo_grafo(const string &descricao,
                             const string &arquivoSaida)
{
  ifstream fin(descricao.c_str());
  if (!fin.is_open())
  {
    cerr << "Erro ao abrir arquivo de descrição " << descricao << endl;
    return;
  }

  int grau, ordem, dir, compConexas, vPond, aPond, completo, bipartido,
      arvore, aPonte, vArti;
  fin >> grau >> ordem >> dir >> compConexas >> vPond >> aPond >> completo >>
      bipartido >> arvore >> aPonte >> vArti;

  direcionado = (dir == 1);
  verticesPonderados = (vPond == 1);
  arestasPonderadas = (aPond == 1);

  fin.close();

  limpaGrafo();

  srand((unsigned)time(nullptr));
  for (int i = 0; i < ordem; i++)
  {
    double peso = (verticesPonderados) ? (double)(rand() % 10 + 1) : 1.0;
    insereVertice(i + 1, peso);
  }

  int *conjuntoA = nullptr;
  int *conjuntoB = nullptr;
  if (bipartido)
  {
    conjuntoA =
        new int[(ordem + 1) / 2];
    conjuntoB = new int[ordem / 2];
  }

  if (completo)
  {

    for (int i = 1; i <= ordem; i++)
    {
      for (int j = i + 1; j <= ordem; j++)
      {
        if (!direcionado)
        {
          insereAresta(i, j,
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        }
        else
        {
          insereAresta(i, j,
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
          insereAresta(j, i,
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        }
      }
    }
  }
  else if (arvore)
  {

    int *vertices = new int[ordem];
    for (int i = 0; i < ordem; i++)
    {
      vertices[i] = i + 1;
    }

    for (int i = ordem - 1; i > 0; i--)
    {
      int j = rand() % (i + 1);
      swap(vertices[i], vertices[j]);
    }

    for (int i = 1; i < ordem; i++)
    {
      int origem = vertices[i - 1];
      int destino = vertices[i];
      insereAresta(origem, destino,
                   arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
    }

    delete[] vertices;
  }
  else if (bipartido)
  {

    int tamanhoA = 0, tamanhoB = 0;

    for (int i = 1; i <= ordem; i++)
    {
      if (i % 2 == 0)
      {
        conjuntoA[tamanhoA++] = i;
      }
      else
      {
        conjuntoB[tamanhoB++] = i;
      }
    }

    for (int i = 0; i < tamanhoA; i++)
    {
      for (int j = 0; j < tamanhoB; j++)
      {
        if (rand() % 2 == 0)
        {
          insereAresta(conjuntoA[i], conjuntoB[j],
                       arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
        }
      }
    }

    delete[] conjuntoA;
    delete[] conjuntoB;
  }
  else
  {

    int tamanhoComp = ordem / compConexas;
    int **componentes = new int *[compConexas];
    for (int i = 0; i < compConexas; i++)
    {
      componentes[i] = new int[tamanhoComp];
      for (int j = 0; j < tamanhoComp; j++)
      {
        componentes[i][j] = j + 1 + (i * tamanhoComp);
      }
    }

    for (int i = 0; i < compConexas; i++)
    {
      for (int u = 0; u < tamanhoComp; u++)
      {
        for (int k = 0; k < grau; k++)
        {
          int v = componentes[i][rand() % tamanhoComp];
          if (componentes[i][u] != v && !existeAresta(componentes[i][u], v))
          {
            insereAresta(componentes[i][u], v,
                         arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
          }
        }
      }
      delete[] componentes[i];
    }

    delete[] componentes;
  }

  if (aPonte)
  {
    int u = 1, v = 2;
    if (!existeAresta(u, v))
    {
      insereAresta(u, v, arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
    }
  }

  ofstream fout(arquivoSaida.c_str());
  if (!fout.is_open())
  {
    cerr << "Erro ao criar arquivo de saída " << arquivoSaida << endl;
    return;
  }

  fout << ordem << " " << (direcionado ? 1 : 0) << " "
       << (verticesPonderados ? 1 : 0) << " " << (arestasPonderadas ? 1 : 0)
       << endl;

  if (verticesPonderados)
  {
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr)
    {
      fout << vAtual->getPesoVertice() << " ";
      vAtual = vAtual->getProximoVertice();
    }
    fout << endl;
  }

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    NoAresta *aAtual = vAtual->getPrimeiraAresta();
    while (aAtual != nullptr)
    {
      fout << vAtual->getIdVertice() << " " << aAtual->getIdVertice();
      if (arestasPonderadas)
      {
        fout << " " << aAtual->getPesoAresta();
      }
      fout << endl;
      aAtual = aAtual->getProxima();
    }
    vAtual = vAtual->getProximoVertice();
  }

  fout.close();
}

bool Grafo_lista::eh_bipartido()
{

  for (unsigned long mascara = 0; mascara < (1UL << numNos); mascara++)
  {

    bool ok = true;

    NoVertice *uV = primeiroVertice;
    while (uV != nullptr && ok)
    {
      int u = uV->getIdVertice();
      NoAresta *a = uV->getPrimeiraAresta();
      while (a != nullptr)
      {
        int v = a->getIdVertice();

        int corU = ((mascara >> (u - 1)) & 1);
        int corV = ((mascara >> (v - 1)) & 1);
        if (corU == corV)
        {

          ok = false;
          break;
        }
        a = a->getProxima();
      }
      uV = uV->getProximoVertice();
    }

    if (ok)
    {
      return true;
    }
  }

  return false;
}

int Grafo_lista::n_conexo()
{

  bool *visitado = new bool[numNos + 1];
  for (int i = 1; i <= numNos; i++)
  {
    visitado[i] = false;
  }

  int componentesConexas = 0;

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    int idVertice = vAtual->getIdVertice();

    if (!visitado[idVertice])
    {
      componentesConexas++;

      dfs_marcar_componente(idVertice, visitado);
    }

    vAtual = vAtual->getProximoVertice();
  }

  delete[] visitado;

  return componentesConexas;
}

int Grafo_lista::get_grau()
{
  int grauMaximo = 0;
  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {

    int contador = 0;
    NoAresta *aAtual = vAtual->getPrimeiraAresta();
    while (aAtual != nullptr)
    {
      contador++;
      aAtual = aAtual->getProxima();
    }
    if (contador > grauMaximo)
    {
      grauMaximo = contador;
    }
    vAtual = vAtual->getProximoVertice();
  }
  return grauMaximo;
}

int Grafo_lista::get_ordem()
{
  return numNos;
}

bool Grafo_lista::eh_direcionado()
{
  return direcionado;
}

bool Grafo_lista::vertice_ponderado()
{
  return verticesPonderados;
}

bool Grafo_lista::aresta_ponderada()
{
  return arestasPonderadas;
}

bool Grafo_lista::eh_completo()
{

  if (numNos <= 1)
  {
    return true;
  }

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    int idOrigem = vAtual->getIdVertice();

    NoVertice *vAux = primeiroVertice;
    while (vAux != nullptr)
    {
      int idDestino = vAux->getIdVertice();

      if (idOrigem != idDestino)
      {

        bool existeOD = existeAresta(idOrigem, idDestino);
        if (!existeOD)
        {
          return false;
        }

        if (this->direcionado)
        {
          bool existeDO = existeAresta(idDestino, idOrigem);
          if (!existeDO)
          {
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

bool Grafo_lista::eh_arvore()
{

  if (n_conexo() != 1)
  {
    return false;
  }

  if (tem_ciclo())
  {
    return false;
  }

  return true;
}

bool Grafo_lista::possui_articulacao()
{

  int *disc = new int[numNos + 1];
  int *low = new int[numNos + 1];
  bool *visitado = new bool[numNos + 1];
  int *pai = new int[numNos + 1];
  bool *articulacao = new bool[numNos + 1];

  for (int i = 1; i <= numNos; i++)
  {
    disc[i] = -1;
    low[i] = -1;
    visitado[i] = false;
    pai[i] = -1;
    articulacao[i] = false;
  }

  int tempo = 0;

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    int idVertice = vAtual->getIdVertice();
    if (!visitado[idVertice])
    {
      int filhosRaiz = 0;
      dfs_articulacao(idVertice, tempo, disc, low, visitado, pai, articulacao, filhosRaiz);

      if (filhosRaiz > 1)
      {
        articulacao[idVertice] = true;
      }
    }
    vAtual = vAtual->getProximoVertice();
  }

  bool existeArticulacao = false;
  for (int i = 1; i <= numNos; i++)
  {
    if (articulacao[i])
    {
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

void Grafo_lista::dfs_articulacao(int u, int &tempo, int disc[], int low[],
                                  bool visitado[], int pai[], bool articulacao[],
                                  int &filhosRaiz)
{

  visitado[u] = true;

  disc[u] = low[u] = ++tempo;

  bool isRoot = (pai[u] == -1);
  if (isRoot)
  {
    filhosRaiz = 0;
  }

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(u);
  NoLista *atual = vizinhos;
  while (atual != nullptr)
  {
    int v = atual->idVertice;

    if (!visitado[v])
    {
      if (isRoot)
      {
        filhosRaiz++;
      }
      pai[v] = u;

      dfs_articulacao(v, tempo, disc, low, visitado, pai, articulacao,
                      filhosRaiz);

      low[u] = std::min(low[u], low[v]);

      if (!isRoot && low[v] >= disc[u])
      {
        articulacao[u] = true;
      }
    }
    else if (v != pai[u])
    {

      low[u] = std::min(low[u], disc[v]);
    }

    atual = atual->proximo;
  }

  liberarLista(vizinhos);
}

bool Grafo_lista::possui_ponte()
{

  int *disc = new int[numNos + 1];
  int *low = new int[numNos + 1];
  bool *visitado = new bool[numNos + 1];
  int *pai = new int[numNos + 1];

  for (int i = 1; i <= numNos; i++)
  {
    disc[i] = -1;
    low[i] = -1;
    visitado[i] = false;
    pai[i] = -1;
  }

  int tempo = 0;

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    int idVertice = vAtual->getIdVertice();
    if (!visitado[idVertice])
    {
      if (dfs_ponte(idVertice, tempo, disc, low, visitado, pai))
      {

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

void Grafo_lista::insereVertice(int id, double pesoVertice = 1.0)
{

  if (encontraVertice(id) != nullptr)
    return;

  NoVertice *novoV = new NoVertice(id, pesoVertice);
  novoV->setProximoVertice(primeiroVertice);
  primeiroVertice = novoV;
}

void Grafo_lista::insereAresta(int origem, int destino, double peso = 1.0)
{

  if (origem == destino)
    return;

  if (existeAresta(origem, destino))
    return;

  NoVertice *vOrigem = encontraVertice(origem);
  if (!vOrigem)
    return;

  vOrigem->insereAresta(destino, peso);

  if (!direcionado)
  {
    NoVertice *vDestino = encontraVertice(destino);
    if (!vDestino)
      return;
    vDestino->insereAresta(origem, peso);
  }
}

NoVertice *Grafo_lista::encontraVertice(int id)
{
  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    if (vAtual->getIdVertice() == id)
    {
      return vAtual;
    }
    vAtual = vAtual->getProximoVertice();
  }
  return nullptr;
}

bool Grafo_lista::existeAresta(int origem, int destino)
{
  NoVertice *vOrigem = encontraVertice(origem);
  if (!vOrigem)
    return false;
  NoAresta *aAtual = vOrigem->getPrimeiraAresta();
  while (aAtual != nullptr)
  {
    if (aAtual->getIdVertice() == destino)
    {
      return true;
    }
    aAtual = aAtual->getProxima();
  }
  return false;
}

void Grafo_lista::limpaGrafo()
{
  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    NoAresta *aAtual = vAtual->getPrimeiraAresta();
    while (aAtual != nullptr)
    {
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

Grafo_lista::NoLista *Grafo_lista::getVizinhosIgnorandoDirecao(int idVert)
{
  Grafo_lista::NoLista *vizinhos = nullptr;

  NoVertice *vOrigem = encontraVertice(idVert);
  if (vOrigem != nullptr)
  {

    NoAresta *aAtual = vOrigem->getPrimeiraAresta();
    while (aAtual != nullptr)
    {

      Grafo_lista::NoLista *novoVizinho = new Grafo_lista::NoLista(aAtual->getIdVertice());
      novoVizinho->proximo = vizinhos;
      vizinhos = novoVizinho;
      aAtual = aAtual->getProxima();
    }
  }

  if (this->direcionado)
  {
    NoVertice *vAtual = primeiroVertice;
    while (vAtual != nullptr)
    {
      NoAresta *aAtual = vAtual->getPrimeiraAresta();
      while (aAtual != nullptr)
      {
        if (aAtual->getIdVertice() == idVert)
        {
          Grafo_lista::NoLista *novoVizinho = new Grafo_lista::NoLista(vAtual->getIdVertice());
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

void Grafo_lista::liberarLista(NoLista *lista)
{
  while (lista != nullptr)
  {
    NoLista *temp = lista;
    lista = lista->proximo;
    delete temp;
  }
}

void Grafo_lista::dfs_marcar_componente(int idVertice, bool visitado[])
{

  visitado[idVertice] = true;

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(idVertice);

  NoLista *atual = vizinhos;
  while (atual != nullptr)
  {
    if (!visitado[atual->idVertice])
    {
      dfs_marcar_componente(atual->idVertice, visitado);
    }
    atual = atual->proximo;
  }

  liberarLista(vizinhos);
}

bool Grafo_lista::tem_ciclo()
{

  bool *visitado = new bool[numNos + 1];
  for (int i = 1; i <= numNos; i++)
  {
    visitado[i] = false;
  }

  NoVertice *vAtual = primeiroVertice;
  while (vAtual != nullptr)
  {
    int idVertice = vAtual->getIdVertice();

    if (!visitado[idVertice])
    {
      if (dfs_detecta_ciclo(idVertice, visitado, -1))
      {
        delete[] visitado;
        return true;
      }
    }

    vAtual = vAtual->getProximoVertice();
  }

  delete[] visitado;

  return false;
}

bool Grafo_lista::dfs_detecta_ciclo(int idVertice, bool visitado[], int pai)
{

  visitado[idVertice] = true;

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(idVertice);

  NoLista *atual = vizinhos;
  while (atual != nullptr)
  {
    int vizinho = atual->idVertice;

    if (!visitado[vizinho])
    {
      if (dfs_detecta_ciclo(vizinho, visitado, idVertice))
      {
        liberarLista(vizinhos);
        return true;
      }
    }

    else if (vizinho != pai)
    {
      liberarLista(vizinhos);
      return true;
    }

    atual = atual->proximo;
  }

  liberarLista(vizinhos);

  return false;
}

bool Grafo_lista::dfs_ponte(int u, int &tempo, int disc[], int low[], bool visitado[],
                            int *pai)
{

  visitado[u] = true;

  disc[u] = low[u] = ++tempo;

  NoLista *vizinhos = getVizinhosIgnorandoDirecao(u);
  NoLista *atual = vizinhos;
  while (atual != nullptr)
  {
    int v = atual->idVertice;

    if (!visitado[v])
    {

      if (dfs_ponte(v, tempo, disc, low, visitado, &u))
      {
        liberarLista(vizinhos);
        return true;
      }

      low[u] = std::min(low[u], low[v]);

      if (low[v] > disc[u])
      {
        liberarLista(vizinhos);
        return true;
      }
    }
    else if (pai == nullptr || v != *pai)
    {

      low[u] = std::min(low[u], disc[v]);
    }

    atual = atual->proximo;
  }

  liberarLista(vizinhos);
  return false;
}