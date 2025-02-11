template <typename T> ListaEncadeada<T>::ListaEncadeada() : head(nullptr) {}

template <typename T> ListaEncadeada<T>::~ListaEncadeada() {
  No<T> *atual = head;
  while (atual) {
    No<T> *temp = atual;
    atual = atual->prox;
    delete temp;
  }
}

template <typename T> void ListaEncadeada<T>::inserir(const T &dado) {
  // Método original: insere no início
  No<T> *novo = new No<T>(dado);
  novo->prox = head;
  head = novo;
}

template <typename T> void ListaEncadeada<T>::append(const T &dado) {
  // Método para inserir no final
  No<T> *novo = new No<T>(dado);
  if (head == nullptr) {
    head = novo;
  } else {
    No<T> *atual = head;
    while (atual->prox != nullptr) {
      atual = atual->prox;
    }
    atual->prox = novo;
  }
}

template <typename T> No<T> *ListaEncadeada<T>::getHead() const { return head; }
