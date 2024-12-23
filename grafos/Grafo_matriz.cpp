#include "Grafo_matriz.h"
#include "Aresta.h"
#include "Vertice.h"

Grafo_matriz::Grafo_matriz(int n, bool dir, bool pondArestas, bool pondVertices)
{
    numNos = n;
    direcionado = dir;
    arestas_ponderadas = pondArestas;
    vertices_ponderados = pondVertices;

    matriz = new int *[numNos];
    for (int i = 0; i < numNos; ++i)
    {
        matriz[i] = new int[numNos];
        for (int j = 0; j < numNos; ++j)
        {
            matriz[i][j] = 0;
        }
    }
}

Grafo_matriz::~Grafo_matriz()
{
    for (int i = 0; i < numNos; ++i)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void Grafo_matriz::adicionarAresta(Vertice *vertice)
{
    Aresta *aresta = vertice->arestas; // Pega a primeira aresta do vértice

    while (aresta != nullptr)
    {
        int idOrigem = vertice->id;
        int idDestino = aresta->destino;

        
        if (!direcionado && idOrigem > idDestino) { // verifico se o grafo não é direcionado para realizar um swap
            std::swap(idOrigem, idDestino); // o swap permite uma diminuição do número de verificações e possibilidades.
        }

        // Verificação se a aresta já não está preenchida na matriz
        if (matriz[idOrigem][idDestino] == 0)  // Caso seja igual a 0, a aresta não está na matriz
        {
            if (arestas_ponderadas)
            {
                // Caso seja ponderado, é utilizado o peso da aresta
                if (direcionado)
                    matriz[idOrigem][idDestino] = aresta->peso;
                else // Para grafos não direcionados
                {
                    matriz[idOrigem][idDestino] = aresta->peso;
                    matriz[idDestino][idOrigem] = aresta->peso;
                }
            }
            else
            {
                // Caso não seja ponderado, é adicionado na posição 1
                if (direcionado)
                {
                    matriz[idOrigem][idDestino] = 1;
                }
                else // Para grafos não direcionados
                {
                    matriz[idOrigem][idDestino] = 1;
                    matriz[idDestino][idOrigem] = 1;
                }
            }
        }

        aresta = aresta->prox;
    }
}



void Grafo_matriz::imprimirMatriz() // impressão da matriz de adjacência.
{
    for (int i = 0; i < numNos; ++i)
    {
        for (int j = 0; j < numNos; ++j)
        {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Grafo_matriz::verificarAresta(int origem, int destino) // Verifica se a aresta existe
{
    if(matriz[origem][destino] != 0)
    return true;
    else return false;
}

void Grafo_matriz::removerAresta(int origem, int destino) // caso seja removida uma Aresta, atualiza a matriz;
{
    matriz[origem][destino] = 0;
    if (!direcionado)
    {
        matriz[destino][origem] = 0;
    }
}

void Grafo_matriz::limparGrafo() //limpo o meu grafo de matriz de adjancencia
{
    for (int i = 0; i < numNos; ++i) {
        for (int j = 0; j < numNos; ++j) {
            matriz[i][j] = 0;
        }
    }
}

bool Grafo_matriz::verificarLigacao(int x, int y) {
    if (matriz[x][y] != 0) {
        return true; // Existe uma ligação
    } else {
        return false; // Não existe uma ligação
    }
}

void Grafo_matriz::verificarLigacoes(int x) {
    for(int i = 0; i < numNos; i++) {
        if(matriz[x][i] != 0)
        std::cout << "O vertice " << x << " faz ligação ao vertice " << i << std::endl;
    }
}


