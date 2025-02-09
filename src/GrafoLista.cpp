#include "../include/GrafoLista.hpp"
#include "../include/IntList.hpp"
#include "../include/ListaEncadeada.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

GrafoLista::GrafoLista() { vertices = new ListaEncadeada<Vertice *>(); }

GrafoLista::~GrafoLista() {
  // Itera sobre a lista de vértices e deleta cada um
  No<Vertice *> *no = vertices->getHead();
  while (no) {
    delete no->dado;
    no = no->prox;
  }
  delete vertices;
}

void GrafoLista::inserir_vertice(int id, int peso) {
  Vertice *v = new Vertice(id, peso);
  vertices->inserir(v);
}

Vertice *GrafoLista::encontrar_vertice(int id) const {
  No<Vertice *> *no = vertices->getHead();
  while (no) {
    if (no->dado->id == id)
      return no->dado;
    no = no->prox;
  }
  return 0;
}

void GrafoLista::inserir_aresta(int origem, int destino, int peso) {
  // Validação: não permitir laços
  if (origem == destino) {
    cerr << "Erro: Laço não permitido (origem e destino iguais: " << origem
         << ")." << endl;
    return;
  }

  // Busca o vértice de origem
  Vertice *v = encontrar_vertice(origem);
  if (!v) {
    cerr << "Erro: Vértice " << origem << " não encontrado." << endl;
    return;
  }

  // Verifica se já existe uma aresta de 'origem' para 'destino'
  No<Aresta> *no = v->arestas->getHead();
  while (no) {
    if (no->dado.destino == destino) {
      cerr << "Erro: Aresta de " << origem << " para " << destino
           << " já existe." << endl;
      return;
    }
    no = no->prox;
  }

  // Se não houver conflito, insere a aresta na lista do vértice de origem
  v->arestas->inserir(Aresta(destino, peso));

  // Se o grafo não for direcionado, insere a aresta simetricamente
  if (!direcionado) {
    Vertice *v2 = encontrar_vertice(destino);
    if (!v2) {
      cerr << "Erro: Vértice " << destino << " não encontrado." << endl;
      return;
    }
    // Verifica se a aresta reversa já existe na lista do vértice de destino
    no = v2->arestas->getHead();
    while (no) {
      if (no->dado.destino == origem) {
        cerr << "Erro: Aresta de " << destino << " para " << origem
             << " já existe." << endl;
        return;
      }
      no = no->prox;
    }
    v2->arestas->inserir(Aresta(origem, peso));
  }
}

IntList GrafoLista::get_vizinhos(int id) const {
  IntList lista;
  Vertice *v = encontrar_vertice(id);
  if (!v)
    return lista;
  No<Aresta> *no = v->arestas->getHead();
  while (no) {
    lista.add(no->dado.destino);
    no = no->prox;
  }
  return lista;
}
