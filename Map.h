// Map.h
#ifndef MAP__H
#define MAP__H

template<typename KeyType, typename ValueType>
class Map {
private:
  struct Node {
    KeyType key;
    ValueType value;
    Node* next;

    Node(const KeyType& k, const ValueType& v)
      : key(k), value(v), next(nullptr) {}
  };

  Node* head;

public:
  Map()
    : head(nullptr) {}

  void insert(const KeyType& key, const ValueType& value) {
    Node* newNode = new Node(key, value);
    if (head == nullptr) {
      head = newNode;
    } else {
      Node* current = head;
      while (current->next != nullptr) {
        if (current->key == key) {
          current->value = value;
          return;
        }
        current = current->next;
      }
      if (current->key == key) {
        current->value = value;
      } else {
        current->next = newNode;
      }
    }
  }

  ValueType& operator[](const KeyType& key) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
      if (current->key == key) {
        return current->value;  // Key found, return existing value
      }
      prev = current;
      current = current->next;
    }

    Node* newNode = new Node(key, ValueType());
    if (prev == nullptr) {
      head = newNode;  // Insert as the new head node
    } else {
      prev->next = newNode;  // Insert after the last node
    }
    return newNode->value;  // Return the newly inserted value
  }

  bool containsKey(const KeyType& key) {
    Node* current = head;

    while (current != nullptr) {
      if (current->key == key)
        return true;

      current = current->next;
    }

    return false;
  }

  ~Map() {
    Node* current = head;
    while (current != nullptr) {
      Node* nextNode = current->next;
      delete current;
      current = nextNode;
    }
  }
};

#endif