#include "FW.h"
#include <iostream>

using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;

template <typename T> class Set {
private:
  ListaEnlazada<T> *arr;
  int size;
  int capacity;


public:
  Set(int cap = 10) {
    size = 0;
    capacity = cap;
    arr = new ListaEnlazada<T>[capacity];
  }
  void Insert(T data) {

    if (fillFactor() >= maxFillFactor) {
      rehashing();
    }
    bool repeated = false;
    size_t hashcode = getHashCode(data);
    int index = hashcode % capacity;
    for (auto it = arr[index].begin(); it != arr[index].end(); ++it) {
      if ((*it) == data) {
        repeated = true;
        break;
      }
    }
    if (arr[index].size() >= maxColision) {
      rehashing();
      Insert(data);
    } else {
      if (!repeated) {
        arr[index].push_back(data);
        size++;
      }
    }
  }
  bool Remove(T data) {
    size_t hashcode = getHashCode(data);
    int index = hashcode % capacity;
    ListaEnlazada<T> list;
    bool eliminated = false;
    for (auto it = arr[index].begin(); it != arr[index].end(); ++it) {
      if ((*it) != data) {
        list.push_front(*it);
      } else { eliminated = true;}
    }
    arr[index] = list;
    if (eliminated){
      size--;
    }
    return eliminated;
  }
  bool Contains(T data) {
    size_t hashcode = getHashCode(data);
    int index = hashcode % capacity;
    for (auto it = arr[index].begin(); it != arr[index].end(); ++it) {
      if ((*it) == data) {
        return true;
      }
    }
    return false;
  }
  Set Union(const Set &other) const {
    Set result(this->capacity);
    for (int i = 0; i < this->capacity; i++) {
      for (auto it = arr[i].begin(); it != arr[i].end(); ++it) {
        result.Insert(*it);
      }
    }
    for (int i = 0; i < other.capacity; i++) {
      for (auto it = other.arr[i].begin(); it != other.arr[i].end(); ++it) {
        result.Insert(*it);
      }
    }
    return result;
  }

  Set Intersect( Set &other)  {
    Set result(std::min(this->capacity, other.capacity));

    for (int i = 0; i < this->capacity; i++) {
      for (auto it = arr[i].begin(); it != arr[i].end(); ++it) {
        if (other.Contains(*it)) {
          result.Insert(*it);
        }
      }
    }

    return result;
  }
  Set Difference( Set &other) {
    Set result(this->capacity);

    for (int i = 0; i < this->capacity; i++) {
      for (auto it = arr[i].begin(); it != arr[i].end(); ++it) {
        if (!other.Contains(*it)) {
          result.Insert(*it);
        }
      }
    }

    return result;
  }

  void display() const {
    for (int i = 0; i < capacity; ++i) {
      for (auto it = arr[i].begin(); it != arr[i].end(); ++it) {
        cout << *it << " ";
      }
    }
    cout << endl;
  }
  ~Set() { delete[] arr; }

private:
  void rehashing() {
    ListaEnlazada<T> *nuevo;
    nuevo = new ListaEnlazada<T>[capacity * 2];
    size = 0;
    for (int i = 0; i < capacity; i++) {
      for (auto it = arr[i].begin(); it != arr[i].end(); ++it) {
        size_t hashcode = getHashCode((*it));
        int index = hashcode % (capacity * 2);
        nuevo[index].push_front((*it));
        size++;
      }
    }
    capacity = capacity * 2;
    delete[] arr;
    arr = nuevo;
  }
  size_t getHashCode(T data) {
    std::hash<T> ptr_hash;
    return ptr_hash(data);
  }
  double fillFactor() { return size / (capacity * maxColision); }
};

int main() {
  Set<int> set1;
  Set<int> set2;

  set1.Insert(1);
  set1.Insert(2);
  set1.Insert(3);
  set1.Insert(4);
  set1.Insert(488);

  set2.Insert(3);
  set2.Insert(4);
  set2.Insert(5);
  set2.Insert(6);

  cout << "SET 1 : "<< endl;
  set1.display();
  cout << "SET 2 : "<< endl;

  set2.display();
  cout <<  "-------INSERTANDO 2 EN SET 1  (REPETIDO)-------" << endl;
  set1.Insert(2);
  cout << "SET 1 : "<< endl;
  set1.display();
  cout << "SET 2 : "<< endl;
  set2.display();

  cout <<  "-------ELIMINANDO 488 EN SET 1------- " << endl;
  set1.Remove(488);
  cout << "SET 1 : "<< endl;
  set1.display();

  cout << "-------BUSCANDO 488 EN SET 1-------" << endl;
  cout << set1.Contains(488) << endl;


  Set<int> unionSet = set1.Union(set2);
  Set<int> intersectSet = set1.Intersect(set2);
  Set<int> differenceSet = set1.Difference(set2);
  cout << "SET UNION : "<< endl;

  unionSet.display();
  cout << "SET INTERSECT : "<< endl;

  intersectSet.display();
  cout << "SET DIFFERENCE : "<< endl;

  differenceSet.display();

  return 0;
}
