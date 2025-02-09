template <typename T> ListaEncadeada<T>::ListaEncadeada() : head(0) {}

template <typename T> ListaEncadeada<T>::~ListaEncadeada() {
  No<T> *current = head;
  while (current) {
    No<T> *temp = current;
    current = current->prox;
    delete temp;
  }
}

template <typename T> void ListaEncadeada<T>::inserir(const T &dado) {
  No<T> *novo = new No<T>(dado);
  novo->prox = head;
  head = novo;
}

template <typename T> No<T> *ListaEncadeada<T>::getHead() const { return head; }
