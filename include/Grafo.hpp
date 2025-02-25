#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "IntList.hpp"
#include <string>
using namespace std;

class Grafo {
protected:
  int ordem;              // número de vértices
  bool direcionado;       // true se direcionado, false caso contrário
  bool ponderadoVertices; // se os vértices têm peso
  bool ponderadoArestas;  // se as arestas têm peso
public:
  Grafo()
      : ordem(0), direcionado(false), ponderadoVertices(false),
        ponderadoArestas(false) {}
  virtual ~Grafo() {}

  // Funções de acesso
  int get_ordem() const { return ordem; }
  bool eh_direcionado() const { return direcionado; }
  bool vertice_ponderado() const { return ponderadoVertices; }
  bool aresta_ponderada() const { return ponderadoArestas; }

  // Carrega o grafo a partir de um arquivo de texto
  void carrega_grafo(const string &nomeArquivo);
  // Retorna o grau (ou grau máximo) do grafo
  int get_grau() const;
  // Retorna a quantidade de componentes conexas (desconsiderando a direção)
  int n_conexo() const;
  // Informa se o grafo é completo
  bool eh_completo() const;

  virtual IntList get_vizinhos(int vertice) const = 0;
  // Métodos virtuais para inserir vértices e arestas
  virtual void inserir_vertice(int id, int peso = 0) = 0;
  virtual void inserir_aresta(int origem, int destino, int peso = 0) = 0;

  // Estrutura para armazenar o resultado da função de distância
  struct ResultadoDistancia {
    int no1;
    int no2;
    double distancia;
  };

  // Nova função virtual para obter o peso de uma aresta entre dois nós.
  virtual double getPesoAresta(int origem, int destino) const = 0;

  // Função para calcular, entre todos os pares de nós, qual é o par que possui
  // a maior menor distância
  virtual ResultadoDistancia calculaMaiorMenorDistancia() const;
  virtual void deleta_no(int id) = 0;
  virtual void deleta_aresta(int origem, int destino) = 0;

  virtual void imprime_grafo() const = 0;
  virtual void colore_arestas() = 0;
};

#endif
