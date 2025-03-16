# Projeto de Grafos - DCC059  

**Departamento de Ciência da Computação - UFJF**  
**Disciplina**: Teoria dos Grafos  
**Professor**: Gabriel Souza  

---

## Sobre o Projeto  

### Trabalho 3 – Coloração de Arestas  

Este projeto dá continuidade ao Trabalho 2, focando na implementação e análise de algoritmos para a **coloração de arestas** de um grafo. Foram implementados três métodos diferentes:  
- **Coloração Gulosa**  
- **Coloração Randomizada**  
- **Coloração Reativa**  

A implementação suporta duas representações de grafos: **Matriz de Adjacência** e **Lista de Adjacência**. O objetivo é comparar a eficiência e qualidade das soluções encontradas por cada algoritmo em diferentes instâncias de grafos.

---

## 📌 **Descrição do Problema**  

A coloração de arestas é um problema clássico da teoria dos grafos, onde o objetivo é atribuir cores às arestas de um grafo de forma que duas arestas adjacentes não tenham a mesma cor. Esse problema pertence à classe NP-difícil, e por isso, utilizamos heurísticas para obter soluções aproximadas.

---

## 📂 **Estrutura do Projeto**  

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

---

## ⚙️ **Compilação e Execução**  

### **Compilação**  
O código pode ser compilado com:

```bash
g++ -o main.out main.cpp src/*.cpp -I./include/ -g -Wall -Werror
```

### **Execução**  
O programa pode ser executado em dois modos: **Matriz de Adjacência** e **Lista de Adjacência**.  

#### **Modo Matriz**
```bash
./main.out -p -m entradas/grafo.txt
```

#### **Modo Lista**
```bash
./main.out -p -l entradas/grafo.txt
```

Os parâmetros são:  
- **-p**: Indica que a coloração será executada.  
- **-m** ou **-l**: Escolhe a estrutura de armazenamento (**matriz** ou **lista**).  

### **Análise de Memória**  
Para verificar a alocação e uso de memória, o código pode ser analisado com **Valgrind**:  

```bash
valgrind ./main.out -p -m entradas/grafo.txt
valgrind ./main.out -p -l entradas/grafo.txt
```

---

## 📑 **Formato do Arquivo de Entrada**  

O grafo deve ser descrito em um arquivo `.txt` no seguinte formato:

1. **Primeira linha:**  
   ```
   <número de vértices> <direcionado> <ponderadoVertices> <ponderadoArestas>
   ```
   Exemplo:  
   ```
   5 0 0 0
   ```

2. **Segunda linha (opcional):** Lista de pesos dos vértices (se ponderado).  

3. **Demais linhas:** Cada linha representa uma aresta:  
   ```
   <origem> <destino> <peso>
   ```
   Se o grafo não for ponderado, o peso pode ser ignorado.

Exemplo:
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

---

## 🏗️ **Algoritmos Implementados**  

### **1️⃣ Coloração Gulosa**
- Atribui a menor cor disponível para cada aresta, garantindo que duas arestas adjacentes nunca tenham a mesma cor.
- Simples e eficiente, mas pode gerar soluções não ótimas.

### **2️⃣ Coloração Randomizada**
- Variação do método guloso onde a cor de cada aresta é escolhida **aleatoriamente** dentro de um conjunto de cores permitidas.
- Evita que o algoritmo sempre siga a mesma sequência, buscando explorar outras possibilidades.

### **3️⃣ Coloração Reativa**
- Adaptação do método randomizado onde o fator de escolha de cores (`alpha`) é ajustado dinamicamente.
- Se os resultados estiverem ruins, `alpha` é reduzido para restringir a aleatoriedade.
- Se os resultados estiverem bons, `alpha` é aumentado para explorar mais variações.

---

## 📊 **Comparação de Resultados**  

Os algoritmos foram testados em várias instâncias de grafos reais da literatura, variando de **6 mil a 62 mil vértices**. O desempenho foi medido em termos de:  
- **Tempo de execução**
- **Número total de cores utilizadas**

### **Resumo dos Resultados**
| Grafo  | Representação | Tempo de Leitura (s) | Guloso (Cores, Tempo) | Randomizado (Cores, Tempo) | Reativo (Cores, Tempo, Alpha) |
|--------|--------------|---------------------|----------------------|----------------------|----------------------|
| 62k    | Lista        | 149.8               | 8, 29.6s             | 22, 287.4s           | 15, 288.4s, 0.52     |
| 62k    | Matriz       | 59.9                | 8, 10.3s             | 20, 29.6s            | 15, 28.4s, 0.54      |
| 36k    | Lista        | 48.3                | 8, 10.5s             | 18, 113.5s           | 15, 100.7s, 0.51     |
| 36k    | Matriz       | 120.0               | 8, 35.8s             | 18, 268.8s           | 15, 245.7s, 0.50     |
| 22k    | Lista        | 20.0                | 8, 3.98s             | 18, 43.4s            | 14, 41.4s, 0.50      |
| 22k    | Matriz       | 96.2                | 8, 12.6s             | 19, 104.9s           | 14, 104.0s, 0.51     |

Observações:  
- A **representação por Lista** é mais eficiente para leitura e execução de coloração gulosa.  
- A **representação por Matriz** tem vantagens em algumas instâncias pequenas.  
- O **algoritmo reativo** consegue melhorar os resultados do randomizado em algumas instâncias, mas pode ser sensível ao parâmetro `alpha`.

---


