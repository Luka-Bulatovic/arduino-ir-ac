// Map.h
#ifndef MAP__H
#define MAP__H

template<typename KeyType, typename ValueType>
class Map {
private:
  static const byte capacity = 8;
  
  struct Node {
    KeyType key;
    ValueType value;

    Node() {}

    Node(const KeyType& k, const ValueType& v)
      : key(k), value(v) {}
  };

  Node items[capacity];

  ValueType nullValue;  // Null value to return when the key is not found.

public:
  byte size;

  Map() { size = 0; }

  void insert(const KeyType& key, const ValueType& value) {
    if(size >= capacity - 1)
      return;
    
    size++;
    items[size-1].key = key;
    items[size-1].value = value;
  }

  ValueType& operator[](const KeyType& key) {
    for(byte i = 0; i < size; i++) {
      if(items[i].key == key)
        return items[i].value;
    }

    return nullValue;
  }

  bool containsKey(const KeyType& key) {
    for(byte i = 0; i < size; i++) {
      if(items[i].key == key)
        return true;
    }

    return false;
  }

  ~Map() {}
};



// Specialized Map for char* keys
template<typename ValueType>
class Map<char*, ValueType> {
private:
  static const byte capacity = 2;
  
  struct Node {
    char* key;
    ValueType value;

    Node() {}

    Node(const char* k, const ValueType& v)
      : key(k), value(v) {}
  };

  Node items[capacity];

  ValueType nullValue;  // Null value to return when the key is not found.

public:
  byte size;

  Map() { size = 0; }

  void insert(const char* key, const ValueType& value) {
    if(size >= capacity - 1)
      return;
    
    size++;
    items[size-1].key = key;
    items[size-1].value = value;
  }

  ValueType& operator[](const char* key) {
    for(byte i = 0; i < size; i++) {
      if(strcmp(items[i].key, key) == 0)
        return items[i].value;
    }

    return nullValue;
  }

  bool containsKey(const char* key) {
    for(byte i = 0; i < size; i++) {
      if(strcmp(items[i].key, key) == 0)
        return true;
    }

    return false;
  }

  ~Map() {}
};

#endif