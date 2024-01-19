

#include <iostream>
using namespace std;

template <typename T> class ListaEnlazada {

  struct Node {
    T data;
    Node *next;
    Node(T dato) {
      data = dato;
      next = nullptr;
    }
  };

  Node *head;
  int size_;

public:
  ListaEnlazada() {
    head = nullptr;
    size_ = 0;
  }

  T front() {
    if (head != nullptr) {
      return head->data;
    } else {
      throw "lista vacia";
    }
  }

  T back() {
    Node *temp = head;
    if (temp != nullptr) {
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      return temp->data;
    } else {
      throw "lista vacia";
    }
  }

  void push_front(T data) {
    Node *nodo = new Node(data);
    nodo->next = head;
    head = nodo;
    size_++;
  }

  void push_back(T data) {
    Node *nodo = new Node(data);

    if (head == nullptr) {
      head = nodo;
      size_++;
      return;
    }

    Node *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = nodo;
    size_++;
  }

  T pop_front() {

    if (head == nullptr) {
      throw "lista vacia";
    }

    Node *temp = head;
    T valor = temp->data;
    head = head->next;
    delete temp;
    temp = nullptr;
    size_--;
    return valor;
  }

  T pop_back() {

    if (head == nullptr) {
      throw "lista vacia";
    }
    T dato;
    if (head->next == nullptr) {
      dato = head->data;
      delete head;
      head = nullptr;
    } else {
      Node *temp = head;
      while (temp->next->next != nullptr) {
        temp = temp->next;
      }
      dato = temp->data;
      delete temp->next;
      temp->next = nullptr;
    }
    size_--;
    return dato;
  }

  T operator[](int i) {
    if (i > size_) {
      throw "fuera de rango";
    }
    Node *temp = head;

    for (int it = 0; it < i; it++) {
      temp = temp->next;
    }
    return temp->data;
  }

  bool empty() { return (size_ == 0); }

  int size() { return size_; }

  void clear() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    size_ = 0;
  }

  void reverse() {
    Node *temp = nullptr;
    while (head != nullptr) {
      Node *last = head;

      Node *novo = new Node(last->data);
      novo->next = temp;
      temp = novo;

      head = head->next;

      delete last;
      last = nullptr;
    }
    head = temp;
  }

  void sort() {
    if (size_ <= 1) {
      return;
    }

    bool swapped = true;

    while (swapped) {
      swapped = false;
      Node *temp = head;
      Node *previous = nullptr;
      Node *nextNode = head->next;

      while (nextNode != nullptr) {
        if (temp->data > nextNode->data) {
          if (previous != nullptr) {
            previous->next = nextNode;
          } else {
            head = nextNode;
          }
          temp->next = nextNode->next;
          nextNode->next = temp;

          previous = nextNode;
          nextNode = temp->next;

          swapped = true;
        } else {
          previous = temp;
          temp = nextNode;
          nextNode = nextNode->next;
        }
      }
    }
  }

  void print() {
    Node *temp = head;
    while (temp != nullptr) {
      cout << "[" << temp->data << "]";
      temp = temp->next;
      cout << "->";
    }
    cout << "NULL" << endl;
  }

  Node *begin() const { return head; }

  // Método para obtener un iterador al final de la lista
  Node *end() const {
    return nullptr; 
  }


  class Iterator {
  private:
    Node *current;

  public:
    Iterator(Node *node) : current(node) {}

    Iterator &operator++() {
      if (current) {
        current = current->next;
      }
      return *this;
    }

    
    T &operator*() { return current->data; }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  Iterator begin() { return Iterator(head); }

  Iterator end() { return Iterator(nullptr); }
};
