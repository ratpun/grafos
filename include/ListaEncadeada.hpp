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
  void append(const T &dado); // Insere no final

  // Retorna o ponteiro para o primeiro nó (para iteração)
  No<T> *getHead() const;
  void setHead(No<T> *novoHead) { head = novoHead; }
};

#include "ListaEncadeada.tpp"
#endif
