#include "Grafo.h"
#include "Grafo_matriz.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

    // Alocação da matriz de adjacência
    matriz = new double *[numNos];
    for (int i = 0; i < numNos; i++)
    {
        matriz[i] = new double[numNos];
        // Inicializar a matriz com 0 (sem arestas)
        for (int j = 0; j < numNos; j++)
        {
            matriz[i][j] = 0.0;
        }
    }
}

Grafo_matriz::~Grafo_matriz()
{
    // Desalocar a matriz de adjacência
    for (int i = 0; i < numNos; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void Grafo_matriz::carrega_grafo(const string &arquivo)
{
    ifstream fin(arquivo.c_str());
    if (!fin.is_open())
    {
        cerr << "Erro ao abrir arquivo " << arquivo << endl;
        return;
    }

    // 1) Lê a primeira linha (4 valores):
    //    [numVertices] [dir=0/1] [vPond=0/1] [aPond=0/1]
    int dir, vPond, aPond;
    fin >> numVertices >> dir >> vPond >> aPond;
    if (!fin.good())
    {
        cerr << "Erro ao ler a primeira linha de " << arquivo << endl;
        return;
    }

    // Ajusta flags internas
    direcionado = (dir == 1);
    verticesPonderados = (vPond == 1);
    arestasPonderadas = (aPond == 1);

    // 2) Aloca a matriz de adjacência
    matriz = new double *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        matriz[i] = new double[numVertices];
        fill_n(matriz[i], matriz[i] + numVertices, 0); // Inicializa com 0 (sem arestas)
    }

    // 3) Se os vértices são ponderados, lê uma linha com 'numVertices' pesos
    //    Caso não sejam ponderados, podemos usar peso 1.0 para todos
    if (verticesPonderados)
    {
        for (int i = 0; i < numVertices; i++)
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

    // 4) Agora lemos as arestas até o fim do arquivo:
    //    Se arestasPonderadas == 1, formato: <origem> <destino> <peso>
    //    Se arestasPonderadas == 0, formato: <origem> <destino>
    numArestas = 0;
    while (true)
    {
        int origem, destino;
        double peso = 1.0; // Peso default se não for ponderada
        fin >> origem >> destino;
        if (!fin.good())
        {
            break; // chegou no fim ou deu erro de leitura
        }
        if (arestasPonderadas)
        {
            fin >> peso;
            if (!fin.good())
            {
                break; // leitura de peso falhou
            }
        }
        // Insere a aresta na matriz de adjacência
        adicionaAresta(origem - 1, destino - 1, peso); // Ajuste para índice 0
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

    // Lê os parâmetros
    int grau, ordem, dir, compConexas, vPond, aPond, completo, bipartido,
        arvore, aPonte, vArti;
    fin >> grau >> ordem >> dir >> compConexas >> vPond >> aPond >> completo >>
        bipartido >> arvore >> aPonte >> vArti;

    // Configura o grafo
    direcionado = (dir == 1);
    verticesPonderados = (vPond == 1);
    arestasPonderadas = (aPond == 1);

    fin.close();

    // Limpar qualquer dado antigo
    limpaGrafo();

    // Aloca a matriz de adjacência
    numVertices = ordem;
    matriz = new double *[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        matriz[i] = new double[numVertices];
        fill(matriz[i], matriz[i] + numVertices, 0); // Inicializa com 0 (sem arestas)
    }

    // Gerar vértices
    srand((unsigned)time(nullptr));
    for (int i = 0; i < ordem; i++)
    {
        double peso = (verticesPonderados) ? (double)(rand() % 10 + 1) : 1.0;
        // Aqui não há necessidade de adicionar vértices explicitamente,
        // pois a matriz de adjacência já está preparada para armazenar as arestas.
    }

    // Gerar arestas de acordo com as restrições
    if (completo)
    {
        // Grafo completo: Conectar todos os pares de vértices
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
    // Outras opções (como árvore, bipartido, aleatório) podem ser implementadas de forma similar
    // A lógica para essas opções será análoga ao que você já implementou, mas usando a matriz de adjacência.

    // Salvar grafo no arquivo de saída
    ofstream fout(arquivoSaida.c_str());
    if (!fout.is_open())
    {
        cerr << "Erro ao criar arquivo de saída " << arquivoSaida << endl;
        return;
    }

    fout << ordem << " " << (direcionado ? 1 : 0) << " "
         << (verticesPonderados ? 1 : 0) << " " << (arestasPonderadas ? 1 : 0)
         << endl;

    // Salvar a matriz de adjacência
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j < ordem; j++)
        {
            if (matriz[i][j] != 0)
            {                                  // Só salvar as arestas existentes
                fout << i + 1 << " " << j + 1; // Ajuste para índice 1
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
    // Redefine a matriz de adjacência, setando todos os valores como 0.0
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            matriz[i][j] = 0.0; // Desfaz as arestas
        }
    }

    // Redefine o número de arestas
    numArestas = 0;
}

bool Grafo_matriz::eh_bipartido() {
    int* cores = new int[numVertices];  // Array para armazenar as cores
    for (int i = 0; i < numVertices; i++) {
        cores[i] = -1;  // -1 indica que o vértice ainda não foi colorido
    }

    int* fila = new int[numVertices];  // Array para simular a fila
    int frente = 0; // Índice para a frente da fila
    int tras = 0;   // Índice para o final da fila

    // Tenta colorir o grafo usando BFS
    for (int i = 0; i < numVertices; i++) {
        if (cores[i] == -1) { // Se o vértice não foi colorido
            fila[tras++] = i;  // Adiciona o vértice na fila
            cores[i] = 0;      // Começa com a cor 0 (pode ser qualquer valor)

            while (frente < tras) {
                int u = fila[frente++];  // Remove o vértice da frente da fila

                // Verifica os vizinhos de u
                for (int v = 0; v < numVertices; v++) {
                    if (matriz[u][v] != 0) { // Se há aresta de u para v
                        if (cores[v] == -1) { // Se v não foi colorido
                            cores[v] = 1 - cores[u]; // A cor de v é oposta à de u
                            fila[tras++] = v;  // Adiciona v na fila
                        } else if (cores[v] == cores[u]) {
                            // Se v e u têm a mesma cor, não é bipartido
                            delete[] cores; // Libera a memória alocada para cores
                            delete[] fila;  // Libera a memória alocada para fila
                            return false;
                        }
                    }
                }
            }
        }
    }

    delete[] cores; // Libera a memória alocada para cores
    delete[] fila;  // Libera a memória alocada para fila
    return true; // Se conseguiu colorir todos os vértices sem problemas, é bipartido
}

bool Grafo_matriz::eh_arvore()
{
    // Verifica se o grafo é conexo
    int componentesConexos = n_conexo();
    if (componentesConexos > 1)
    {
        return false; // Não é árvore se o grafo não for conexo
    }

    // Verifica se o número de arestas é igual ao número de vértices - 1
    if (numArestas != numVertices - 1)
    {
        return false; // Não é árvore se as arestas não forem exatamente (vértices - 1)
    }

    // Se for conexo e não tiver ciclo, é uma árvore
    return true;
}

int Grafo_matriz::n_conexo()
{
    // Inicializa o vetor de visitados
    bool *visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i)
    {
        visitado[i] = false;
    }

    int numComponentes = 0;

    // Percorre todos os vértices
    for (int i = 0; i < numVertices; ++i)
    {
        // Se o vértice não foi visitado, é uma nova componente conexa
        if (!visitado[i])
        {
            ++numComponentes; // Incrementa o contador de componentes conexos

            // Realiza a DFS para visitar todos os vértices da componente
            dfs(i, visitado);
        }
    }

    delete[] visitado; // Libera a memória
    return numComponentes;
}

void Grafo_matriz::dfs(int vertice, bool *visitado)
{
    // Marca o vértice atual como visitado
    visitado[vertice] = true;

    // Percorre todos os vértices adjacentes
    for (int i = 0; i < numVertices; ++i)
    {
        if (matriz[vertice][i] != 0 && !visitado[i])
        {
            dfs(i, visitado); // Chamada recursiva para visitar o vértice adjacente
        }
    }
}

bool Grafo_matriz::eh_completo()
{
    // Itera sobre todos os pares de vértices na matriz
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            // Se i != j e não há uma aresta entre i e j, o grafo não é completo
            if (i != j && matriz[i][j] == 0)
            {
                return false;
            }
        }
    }
    // Se passou por todos os pares sem encontrar ausência de aresta, é completo
    return true;
}

bool Grafo_matriz::possui_ponte()
{
    for (int u = 0; u < numVertices; ++u)
    {
        for (int v = 0; v < numVertices; ++v)
        {
            // Verifica se há uma aresta entre u e v
            if (matriz[u][v] != 0)
            {
                // Remove a aresta temporariamente
                double pesoOriginal = matriz[u][v];
                matriz[u][v] = 0;
                if (!direcionado)
                {
                    matriz[v][u] = 0;
                }

                // Verifica se o grafo continua conexo
                bool *visitado = new bool[numVertices];
                for (int i = 0; i < numVertices; ++i)
                {
                    visitado[i] = false;
                }

                // Realiza a DFS a partir de um vértice válido
                dfs(0, visitado);

                // Checa se há vértices desconexos
                bool desconexo = false;
                for (int i = 0; i < numVertices; ++i)
                {
                    if (!visitado[i])
                    {
                        desconexo = true;
                        break;
                    }
                }

                delete[] visitado;

                // Restaura a aresta
                matriz[u][v] = pesoOriginal;
                if (!direcionado)
                {
                    matriz[v][u] = pesoOriginal;
                }

                // Se a remoção causou desconexão, temos uma ponte
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





