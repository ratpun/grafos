# Projeto de Grafos - DCC059

**Departamento de Ciência da Computação - UFJF**  
**Disciplina**: Teoria dos Grafos  
**Professor**: Gabriel Souza  

---

## Sobre o Projeto

# Trabalho 2 – Grafos 

## Descrição

Este projeto expande o Trabalho 1, incorporando funcionalidades dinâmicas para a manipulação de grafos em C++. Além de carregar um grafo a partir de um arquivo, o programa agora permite:

- Inserir novos nós e arestas dinamicamente.
- Remover nós e arestas, com reindexação dos nós remanescentes para manter o grafo isomorfo ao original.
- Calcular a maior menor distância (o maior dos menores caminhos entre dois nós), utilizando o algoritmo de Floyd–Warshall.

O projeto possui duas implementações distintas de armazenamento:

1. **GrafoMatriz:**  
   Utiliza uma matriz de adjacência dinâmica, com capacidade inicial de 10 nós, que é realocada (dobrando a capacidade) quando necessário. Ao remover um nó, a matriz é reconstruída para conter somente os nós remanescentes, com os IDs recalculados de forma sequencial.

2. **GrafoLista:**  
   Utiliza listas encadeadas para armazenar os vértices e suas arestas. A inserção dos nós é feita de modo a preservar a ordem de leitura, e a remoção envolve atualizar os IDs dos nós remanescentes e as referências das arestas.

## Estrutura do Projeto

```
| include/
|    Grafo.hpp
|    GrafoMatriz.hpp
|    GrafoLista.hpp
|    IntList.hpp
|    ListaEncadeada.hpp
|    ListaEncadeada.tpp
|
| src/
|    Grafo.cpp
|    GrafoMatriz.cpp
|    GrafoLista.cpp
|    IntList.cpp
|
| entradas/
|    grafo.txt
|
| main.cpp
```

## Como Compilar

Utilize um compilador C++ (por exemplo, clang++) com as opções:

```bash
clang++ -std=c++17 -Wall -Wextra -g -Iinclude -o main.out main.cpp src/*.cpp
```

## Como Executar

O programa é executado via linha de comando. Exemplos:

- Para a versão Matriz:
  ```bash
  ./main.out -d -m entradas/grafo.txt
  ```
- Para a versão Lista:
  ```bash
  ./main.out -d -l entradas/grafo.txt
  ```

Os parâmetros são:
- **-d** ou **-n**: Indicam se o grafo é direcionado (-d para direcionado, -n para não direcionado).
- **-m** ou **-l**: Selecionam a estrutura de armazenamento (matriz ou lista).
- **nome_arquivo.txt**: Caminho para o arquivo de entrada que descreve o grafo.

## Formato do Arquivo de Entrada

O arquivo deve ter o seguinte formato:

- **Primeira linha:**  
  `<ordem> <direcionado> <ponderadoVertices> <ponderadoArestas>`
  
  Por exemplo, para um grafo com 5 nós não direcionado, sem ponderação:
  ```
  5 0 0 0
  ```

- **Segunda linha (opcional):**  
  Lista de pesos dos vértices, se os vértices forem ponderados.

- **Linhas seguintes:**  
  Cada linha representa uma aresta. Se as arestas forem ponderadas, cada linha deve conter:  
  `<origem> <destino> <peso>`

  Caso contrário, os valores de peso são ignorados (e um peso padrão, geralmente 1, é usado).

Exemplo de arquivo de entrada:
```
5 0 0 0
1 2
2 5
5 4
4 3
3 1
1 4
3 2
1 5
```

## Funcionalidades Dinâmicas

Após o carregamento do grafo, o programa executa as seguintes operações:

1. **Exclusão do Nó:**  
   A função `deleta_no` remove o nó com o id especificado, elimina todas as arestas incidentes e reindexa os nós remanescentes (os IDs dos nós remanescentes serão renumerados de forma sequencial).

2. **Exclusão da Aresta:**  
   A função `deleta_aresta` remove a primeira aresta do nó de id 2, conforme definido pelo método `get_vizinhos`.

3. **Cálculo da Maior Menor Distância:**  
   A função `calculaMaiorMenorDistancia` (implementada de forma genérica na classe base) utiliza os métodos virtuais `getPesoAresta` e (se necessário) `get_vizinhos` para computar, via Floyd–Warshall, os menores caminhos entre todos os pares de nós e determinar o par com a maior distância mínima.

## Considerações Finais

- As operações de inserção, remoção e reindexação devem ser implementadas de forma consistente nas versões matriz e lista para que os resultados sejam idênticos.
- O cálculo da maior menor distância depende de uma correta reconstrução da estrutura do grafo após remoções.
- Se ocorrerem discrepâncias nos resultados, verifique a reindexação dos nós e a atualização das arestas.

---
