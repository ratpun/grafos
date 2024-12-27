# Projeto de Grafos - DCC059

**Departamento de Ciência da Computação - UFJF**  
**Disciplina**: Teoria dos Grafos  
**Professor**: Gabriel Souza  

---

## Sobre o Projeto

Este projeto implementa operações básicas com grafos, permitindo:  
- **Leitura e análise de grafos**: com representações por matriz de adjacência ou lista de adjacência.  
- **Criação de grafos aleatórios**: com base em propriedades definidas em um arquivo de descrição.  

---


# Projeto de Grafos - Casos de Uso

## Casos de Uso do Programa

### **Caso 1: Descrição do Grafo com Matriz de Adjacência**
```bash
main.out -d -m grafo.txt
```
- Carrega o grafo do arquivo `grafo.txt` e imprime sua descrição utilizando a **matriz de adjacência**.  
- Exemplo de saída:
  ```
  Grau: 3
  Ordem: 3
  Direcionado: Sim
  Componentes conexas: 1
  Vertices ponderados: Sim
  Arestas ponderadas: Sim
  Completo: Sim
  Bipartido: Não
  Arvore: Não
  Aresta Ponte: Não
  Vertice de Articulação: Não
  ```

---

### **Caso 2: Descrição do Grafo com Lista de Adjacência**
```bash
main.out -d -l grafo.txt
```
- Igual ao **Caso 1**, mas utilizando a **lista de adjacência** para carregar o grafo.

---

### **Caso 3: Criação de Grafo Aleatório com Matriz de Adjacência**
```bash
main.out -c -m descricao.txt grafo.txt
```
- Lê as propriedades de um arquivo de descrição (`descricao.txt`), cria um grafo aleatório com base nessas propriedades utilizando a **matriz de adjacência** e salva o grafo gerado em `grafo.txt`.

---

### **Caso 4: Criação de Grafo Aleatório com Lista de Adjacência**
```bash
main.out -c -l descricao.txt grafo.txt
```
- Igual ao **Caso 3**, mas utilizando a **lista de adjacência** para criar e salvar o grafo.


