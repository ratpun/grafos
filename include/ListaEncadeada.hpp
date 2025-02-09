#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

// Estrutura de nó genérica
template <typename T> struct No {
  T dado;
  No<T> *prox;
  No(const T &d) : dado(d), prox(0) {}
};

template <typename T> class ListaEncadeada {
private:
  No<T> *head;

public:
  ListaEncadeada();
  ~ListaEncadeada();
  void inserir(const T &dado);
  // Retorna o ponteiro para o primeiro nó (para iteração)
  No<T> *getHead() const;
};

#include "ListaEncadeada.tpp"
#endif
