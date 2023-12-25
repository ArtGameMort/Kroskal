#ifndef MAP_H
#define MAP_H

template<class T>
struct Node {
    Node *next;
    T value;

    Node() = default;

    Node(Node *other, T value);
};

template<class Key, class Value>
class Map {
private:
    Node<Value> **_values;
    size_t _size;
    size_t _filled_elements;

    void arrResize();

public:
    Map();

    void insert(Key key, Value value);

    Value &operator[](Key &key);

    const Value &operator[](Key &key) const;

    ~Map();
};

#include "map.tpp"

#endif  // MAP_H