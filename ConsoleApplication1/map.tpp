template<class T>
Node<T>::Node(Node<T> *other, T value) : next(other), value(value) {}

template<typename Key, typename Value>
Map<Key, Value>::Map() : _size(8), _values(new Node<Value> *[_size]), _filled_elements(0) {
    for (size_t i = 0; i < _size; ++i) _values[i] = nullptr;
}

template<typename Key, typename Value>
void Map<Key, Value>::insert(Key key, Value value) {
    size_t hashValue = std::hash<Key>{}(key);
    size_t index = hashValue % _size;
    if (_values[index] == nullptr) {
        ++_filled_elements;
        _values[index] = new Node<Value>(nullptr, value);
    } else {
        auto *currNode = _values[index];
        while (currNode->next) {
            currNode = currNode->next;
        }
        auto *nextNode = new Node<Value>(nullptr, value);
        currNode->next = nextNode;
    }
    if (static_cast<double>(_filled_elements) / static_cast<double>(_size) >= 0.6) {
        arrResize();
    }
}

template<typename Key, typename Value>
Value &Map<Key, Value>::operator[](Key &key) {
    size_t hashValue = std::hash<Key>{}(key);
    size_t index = hashValue % _size;
    return _values[index]->value;
}

template<typename Key, typename Value>
const Value &Map<Key, Value>::operator[](Key &key) const {
    size_t hashValue = std::hash<Key>{}(key);
    size_t index = hashValue % _size;
    return _values[index]->value;
}

template<typename Key, typename Value>
Map<Key, Value>::~Map() {
    for (size_t i = 0; i < _size; ++i) {
        Node<Value> *curr = _values[i];
        while (curr) {
            Node<Value> *next = curr->next;
            delete curr;
            curr = next;
        }
    }
}

template<typename Key, typename Value>
void Map<Key, Value>::arrResize() {
    auto **newValues = new Node<Value> *[_size * 2];
    for (int i = 0; i < _size * 2; ++i) {
        if (i < _size) {
            newValues[i] = _values[i];
        } else {
            newValues[i] = nullptr;
        }
    }
    delete[] _values;
    _values = newValues;
    _size *= 2;
}