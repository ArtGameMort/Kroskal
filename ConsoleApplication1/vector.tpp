template<typename T>
T& my_vector<T>::operator[](size_t i) {
    if (i >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    return _data[i];
}

template<typename T>
const T& my_vector<T>::operator[](size_t i) const {
    if (i >= _size) {
        throw std::out_of_range("Index out of range.");
    }
    return _data[i];
}

template<typename T>
std::istream& operator>>(std::istream& in, my_vector<T>& rhs) {
    size_t _size;
    in >> _size;
    for (size_t i = 0; i < _size; ++i) {
        int num;
        in >> num;
        rhs.push_back(num);
    }
    return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& rhs) {
    for (size_t i = 0; i < rhs._size; ++i) {
        out << rhs._data[i] << ' ';
    }
    return out;
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector& rhs) {
    if (&rhs == this) {
        return *this;
    }
    delete[] _data;
    _data = new T[rhs._capacity];
    _capacity = rhs._capacity;
    _size = rhs._size;
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = rhs._data[i];
    }
    return *this;
}

template<typename T>
my_vector<T>::my_vector(const my_vector& rhs) : _data(new T[rhs._capacity]), _size(rhs._size), _capacity(rhs._capacity) {
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = rhs._data[i];
    }
}

template<typename T>
my_vector<T>::my_vector() : _data(nullptr), _size(0), _capacity(0) {}

template<typename T>
my_vector<T>::~my_vector() {
    delete [] _data;
}

template<typename T>
void my_vector<T>::push_back(const T& value) {
    if (_size + 1 > _capacity) {
        T* tmp = new T[_size];
        for (size_t i = 0; i < _size; ++i) {
            tmp[i] = _data[i];
        }
        delete[] _data;

        if (_capacity == 0) _capacity = 1;
        else _capacity *= 2;
        _data = new T[_capacity];

        for (size_t i = 0; i < _size; ++i) {
            _data[i] = tmp[i];
        }
        delete[] tmp;
    }
    _data[_size] = value;
    ++_size;
}

template<typename T>
size_t my_vector<T>::size() const { return _size; }


template<typename T>
size_t my_vector<T>::capacity() const { return _capacity; }