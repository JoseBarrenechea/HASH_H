#include "FW.h"
#include <iostream>
using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;

template <typename TK, typename TV> class ChainHash {
private:
  struct LV {
    TK key;
    TV value;
    size_t hashcode;
    LV(TK _k, TV _v) {
      key = _k;
      value = _v;
    }
  };
  ListaEnlazada<LV> *array;
  int capacity;
  int size;

public:
  ChainHash(int _cap = 10) {
    capacity = _cap;
    array = new ListaEnlazada<LV>[capacity];
    size = 0;
  }
  ~ChainHash() { delete[] array; }

  void insert(TK key, TV value) {
    if (fillFactor() >= maxFillFactor) {
      rehashing();
    }
    size_t hashcode = getHashCode(key);
    int index = hashcode % capacity;
    bool repeated = false;
    for (auto it = array[index].begin(); it != array[index].end(); ++it) {
      if ((*it).key == key) {
        (*it).value = value;
        repeated = true;
        break;
      }
    }

    if (bucket_size(index) >= maxColision) {
      rehashing();
      hashcode = getHashCode(key);
      index = hashcode % capacity;
      insert(key, value);
    } else {
      if (repeated == false) {
        LV dat = LV(key,value);
        array[index].push_front(dat);
        size++;
      }
    }
  }

  TV get(TK key) {
    size_t hashcode = getHashCode(key);
    int index = hashcode % capacity;
    TV value;
    for (auto it = array[index].begin(); it != array[index].end(); ++it) {
      if ((*it).key == key) {
        value = (*it).value;
        return value;
      }
    }
  }

  bool Contains(TK key) {
    size_t hashcode = getHashCode(key);
    int index = hashcode % capacity;
    for (auto it = array[index].begin(); it != array[index].end(); ++it) {
      if ((*it).key == key) {
        return true;
      }
    }
    return false;
  }

  void remove(TK key) {
    size_t hashcode = getHashCode(key);
    int index = hashcode % capacity;
    ListaEnlazada<LV> list;
    bool eliminated = false;

    for (auto it = array[index].begin(); it != array[index].end(); ++it) {
      if ((*it).key != key) {
        list.push_front(*it);
      } else {
        eliminated = true;
      }
    }
    array[index] = list;
    if (eliminated) {
      size--;
    }
  }

  int bucket_count() { return capacity; }

  int bucket_size(int index) { return array[index].size(); }

  void display() const {
    for (int i = 0; i < capacity; ++i) {
      for (auto it = array[i].begin(); it != array[i].end(); ++it) {
        cout << "[" << (*it).key << "] = " << (*it).value << endl;
      }
    }
  }

private:
  double fillFactor() { return size / (capacity * maxColision); }

  size_t getHashCode(TK key) {
    std::hash<TK> ptr_hash;
    return ptr_hash(key);
  }

  void rehashing() {
    ListaEnlazada<LV> *nuevo;
    nuevo = new ListaEnlazada<LV>[capacity * 2];
    size = 0;
    for (int i = 0; i < capacity; i++) {
      for (auto it = array[i].begin(); it != array[i].end(); ++it) {
        size_t hashcode = getHashCode((*it).key);
        int index = hashcode % (capacity * 2);
        nuevo[index].push_front(LV((*it).key, (*it).value));
        size++;
      }
    }
    capacity = capacity * 2;
    delete[] array;
    array = nuevo;
  }
};

int main() {
  ChainHash<string, int> hashTable(10);

  hashTable.insert("adrian", 1);
  hashTable.insert("ete sech", 2);
  hashTable.insert("tilin", 3);

  cout << "Tamaño de collisiones: " << hashTable.bucket_count() << endl;

  hashTable.display();
  cout << "REMOVIENDO VALOR" << endl;
  hashTable.remove("ete sech");
  hashTable.display();

  return 0;
}
