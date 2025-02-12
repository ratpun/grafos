# Projeto de Grafos - DCC059

**Departamento de Ciência da Computação - UFJF**  
**Disciplina**: Teoria dos Grafos  
**Professor**: Gabriel Souza  

---

## Sobre o Projeto

# Trabalho 01 de Grafos em C++

## Descrição

Este projeto implementa um grafo em C++ seguindo os seguintes requisitos:

- **Classe Abstrata `Grafo`:**  
  Implementa funções genéricas para:
  - Carregar o grafo a partir de um arquivo (`carrega_grafo`)
  - Retornar a ordem do grafo (`get_ordem`)
  - Calcular o grau (ou grau máximo) do grafo (`get_grau`)
  - Determinar o número de componentes conexas (`n_conexo`)
  - Informar se o grafo é direcionado (`eh_direcionado`)
  - Informar se os vértices são ponderados (`vertice_ponderado`)
  - Informar se as arestas são ponderadas (`aresta_ponderada`)
  - Verificar se o grafo é completo (`eh_completo`)

- **Classes Derivadas:**  
  São implementadas duas classes filhas, cada uma utilizando uma estrutura diferente para o armazenamento dos dados:
  - **GrafoMatriz:** Utiliza uma matriz de adjacência para armazenar as arestas.  
  - **GrafoLista:** Utiliza listas encadeadas (alocação dinâmica) para representar tanto os vértices quanto as arestas.

- **Validações Implementadas:**  
  O grafo não aceita:
  - **Laços:** Arestas cuja origem é igual ao destino.
  - **Arestas Múltiplas:** Mais de uma aresta entre os mesmos vértices.

## Estrutura do Projeto

A estrutura de diretórios é a seguinte:

```
| include/
| | IntList.hpp
| | ListaEncadeada.hpp
| | ListaEncadeada.tpp
| | Grafo.hpp
| | GrafoMatriz.hpp
| | GrafoLista.hpp
|
| src/
| | IntList.cpp
| | Grafo.cpp
| | GrafoMatriz.cpp
| | GrafoLista.cpp
|
| entradas/
| | grafo.txt
|
| main.cpp
```

## Bibliotecas Utilizadas

Foram utilizadas apenas as seguintes bibliotecas permitidas:

- **fstream**
- **iostream**
- **iomanip**
- **cmath**
- **cstdlib**
- **cstdarg**
- **ctime**
- **string**

## Compilação

Utilize o compilador **clang++ -o** (ou similar) para compilar todos os arquivos. Exemplo de comando:

```bash
clang++ -o -o main.out main.cpp src/*.cpp
```

## Execução

O programa é executado via linha de comando. Os parâmetros indicam:

- **Estrutura de armazenamento:**  
  - `-m` para utilizar matriz de adjacência  
  - `-l` para utilizar lista encadeada
- **Arquivo de entrada:** Caminho para o arquivo com a definição do grafo

Exemplos:

- Para grafo direcionado com matriz:
  ```bash
  ./main.out -d -m entradas/grafo.txt
  ```
- Para grafo direcionado com lista:
  ```bash
  ./main.out -d -l entradas/grafo.txt
  ```

Após a execução, serão exibidas informações como:
- Grau do grafo
- Ordem do grafo
- Se o grafo é direcionado
- Se os vértices são ponderados
- Se as arestas são ponderadas
- Se o grafo é completo

## Exemplo de Arquivo de Entrada (grafo.txt)

O arquivo `grafo.txt` deve estar no seguinte formato:

```
3 1 1 1
2 3 7
1 2 6
2 1 4
2 3 -5
```

Onde:

- **Primeira linha:**  
  - `3` → Número de vértices (ordem do grafo)
  - `1` → Grafo direcionado (1 = sim, 0 = não)
  - `1` → Vértices ponderados (1 = sim, 0 = não)
  - `1` → Arestas ponderadas (1 = sim, 0 = não)

- **Segunda linha:**  
  Lista de pesos dos vértices (neste exemplo, vértice 1 com peso 2, vértice 2 com peso 3 e vértice 3 com peso 7)

- **Linhas seguintes:**  
  Cada linha representa uma aresta, definida por:  
  `origem destino [peso]`  
  *(O peso é informado apenas se as arestas forem ponderadas.)*

### Exemplo de Arquivo com Laço e Aresta Múltipla

Considere o arquivo a seguir, que contém um laço e uma aresta múltipla (estas entradas serão rejeitadas):

```
4 0 0 0
1 2
2 3
3 3   // Laço: aresta de 3 para 3 (não permitido)
2 3   // Aresta múltipla: já existe aresta de 2 para 3 (não permitido)
4 1
```

- A aresta `3 3` não será aceita pois é um laço (origem e destino iguais).
- A segunda ocorrência de `2 3` não será aceita pois já existe uma aresta entre 2 e 3.

## Considerações Finais

- **Formatação do Arquivo:**  
  Certifique-se de que o arquivo de entrada esteja corretamente formatado e localizado no diretório `entradas/` ou ajuste o caminho conforme necessário.

- **Verificações Internas:**  
  As validações para impedir a inserção de laços e arestas múltiplas estão implementadas nos métodos de inserção de arestas (tanto para a classe `GrafoMatriz` quanto para `GrafoLista`).

- **Gerenciamento de Memória:**  
  O código foi escrito com cuidado para evitar vazamentos de memória. Recomenda-se a verificação com ferramentas como o Valgrind, se necessário.

---
