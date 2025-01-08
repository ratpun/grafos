#include "Grafo.h"
#include "Grafo_matriz.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Construtor da classe Grafo_matriz
 *
 * @param n Número de vértices no grafo
 * @param dir Direcionado ou não
 * @param pondArestas Arestas ponderadas ou não
 * @param pondVertices Vértices ponderados ou não
 */

Grafo_matriz::Grafo_matriz(int n, bool dir, bool pondArestas, bool pondVertices)
{
    if (n <= 0)
    {
        cerr << "Número de vértices inválido" << endl;
        return;
    }

    numNos = n;
    direcionado = dir;
    arestas_ponderadas = pondArestas;
    vertices_ponderados = pondVertices;

    pesoNos = new float[numNos];

    matriz = new double *[numNos];
    for (int i = 0; i < numNos; i++)
    {
        matriz[i] = new double[numNos];

        for (int j = 0; j < numNos; j++)
        {
            matriz[i][j] = 0.0;
        }
    }
}

Grafo_matriz::~Grafo_matriz()
{

    for (int i = 0; i < numNos; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;

    delete[] pesoNos;
}

void Grafo_matriz::insereVertice(int id, double peso)
{
    if (id < 0 || id >= numNos)
    {
        cerr << "ID do vértice inválido." << std::endl;
        return;
    }
    if (verticesPonderados)
    {
        pesoNos[id] = peso;
    }
}

void Grafo_matriz::adicionaAresta(int origem, int destino, double peso)
{
    if (origem < 0 || origem >= numNos || destino < 0 || destino >= numNos)
    {
        std::cerr << "Origem ou destino inválido." << std::endl;
        return;
    }

    matriz[origem][destino] = peso;

    if (!direcionado)
    {
        matriz[destino][origem] = peso;
    }
}

bool Grafo_matriz::existeAresta(int origem, int destino)
{
    if (origem < 0 || origem >= numNos || destino < 0 || destino >= numNos)
    {
        return false;
    }

    return matriz[origem][destino] != 0;
}

void Grafo_matriz::carrega_grafo(const string &arquivo)
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

    matriz = new double *[numNos];
    for (int i = 0; i < numNos; i++)
    {
        matriz[i] = new double[numNos];
        fill_n(matriz[i], matriz[i] + numNos, 0);
    }

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

        adicionaAresta(origem - 1, destino - 1, peso);
        numArestas++;
    }

    fin.close();
}

void Grafo_matriz::novo_grafo(const string &descricao, const string &arquivoSaida)
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

    numNos = ordem;
    matriz = new double *[numNos];
    for (int i = 0; i < numNos; i++)
    {
        matriz[i] = new double[numNos];
        fill(matriz[i], matriz[i] + numNos, 0);
    }

    srand((unsigned)time(nullptr));
    for (int i = 0; i < ordem; i++)
    {
        double peso = (verticesPonderados) ? (double)(rand() % 10 + 1) : 1.0;
    }

    if (completo)
    {

        for (int i = 0; i < ordem; i++)
        {
            for (int j = i + 1; j < ordem; j++)
            {
                if (!direcionado)
                {
                    adicionaAresta(i, j, arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
                }
                else
                {
                    adicionaAresta(i, j, arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
                    adicionaAresta(j, i, arestasPonderadas ? (double)(rand() % 10 + 1) : 1.0);
                }
            }
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

    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            if (matriz[i][j] != 0)
            {
                fout << i + 1 << " " << j + 1;
                if (arestasPonderadas)
                {
                    fout << " " << matriz[i][j];
                }
                fout << endl;
            }
        }
    }

    fout.close();
}

void Grafo_matriz::limpaGrafo()
{

    for (int i = 0; i < numNos; i++)
    {
        for (int j = 0; j < numNos; j++)
        {
            matriz[i][j] = 0.0;
        }
    }

    numArestas = 0;
}

bool Grafo_matriz::eh_bipartido()
{
    int *cores = new int[numNos];
    for (int i = 0; i < numNos; i++)
    {
        cores[i] = -1;
    }

    int *fila = new int[numNos];
    int frente = 0;
    int tras = 0;

    for (int i = 0; i < numNos; i++)
    {
        if (cores[i] == -1)
        {
            fila[tras++] = i;
            cores[i] = 0;

            while (frente < tras)
            {
                int u = fila[frente++];

                for (int v = 0; v < numNos; v++)
                {
                    if (matriz[u][v] != 0)
                    {
                        if (cores[v] == -1)
                        {
                            cores[v] = 1 - cores[u];
                            fila[tras++] = v;
                        }
                        else if (cores[v] == cores[u])
                        {

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

bool Grafo_matriz::eh_arvore()
{

    int componentesConexos = n_conexo();
    if (componentesConexos > 1)
    {
        return false;
    }

    if (numArestas != numNos - 1)
    {
        return false;
    }

    return true;
}

int Grafo_matriz::n_conexo()
{

    bool *visitado = new bool[numNos];
    for (int i = 0; i < numNos; ++i)
    {
        visitado[i] = false;
    }

    int numComponentes = 0;

    for (int i = 0; i < numNos; ++i)
    {

        if (!visitado[i])
        {
            ++numComponentes;

            dfs(i, visitado);
        }
    }

    delete[] visitado;
    return numComponentes;
}

void Grafo_matriz::dfs(int vertice, bool *visitado)
{

    visitado[vertice] = true;

    for (int i = 0; i < numNos; ++i)
    {
        if (matriz[vertice][i] != 0 && !visitado[i])
        {
            dfs(i, visitado);
        }
    }
}

bool Grafo_matriz::eh_completo()
{

    for (int i = 0; i < numNos; ++i)
    {
        for (int j = 0; j < numNos; ++j)
        {

            if (i != j && matriz[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

bool Grafo_matriz::possui_ponte()
{
    for (int u = 0; u < numNos; ++u)
    {
        for (int v = 0; v < numNos; ++v)
        {

            if (matriz[u][v] != 0)
            {

                double pesoOriginal = matriz[u][v];
                matriz[u][v] = 0;
                if (!direcionado)
                {
                    matriz[v][u] = 0;
                }

                bool *visitado = new bool[numNos];
                for (int i = 0; i < numNos; ++i)
                {
                    visitado[i] = false;
                }

                dfs(0, visitado);

                bool desconexo = false;
                for (int i = 0; i < numNos; ++i)
                {
                    if (!visitado[i])
                    {
                        desconexo = true;
                        break;
                    }
                }

                delete[] visitado;

                matriz[u][v] = pesoOriginal;
                if (!direcionado)
                {
                    matriz[v][u] = pesoOriginal;
                }

                if (desconexo)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo_matriz::aresta_ponderada()
{
    return arestasPonderadas;
}

bool Grafo_matriz::vertice_ponderado()
{
    return verticesPonderados;
}

bool Grafo_matriz::eh_direcionado()
{
    return direcionado;
}

int Grafo_matriz::get_grau()
{
    return numArestas;
}

int Grafo_matriz::get_ordem()
{
    return numNos;
}
