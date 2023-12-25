#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

template<typename T>
class my_vector {
public:
    my_vector();   // Конструктор по умолчанию

    my_vector(const my_vector&);   // Конструктор копирования

    ~my_vector();   // Деструктор

    my_vector& operator=(const my_vector&);  // Оператор присваивания

    void push_back(const T& value);   // Метод добавления элемента в конец

    [[nodiscard]] size_t size() const; // Метод получения размера

    [[nodiscard]] size_t capacity() const;  // Метод получения вместимости

    T& operator[](size_t i); // Перегрузка оператора [] для не константных объектов

    const T& operator[](size_t i) const; // Перегрузка оператора [] для константных объектов

    template<typename C>
    friend std::istream& operator>>(std::istream& in, my_vector<C>& rhs);  // Перегрузка оператора ввода

    template<typename C>
    friend std::ostream& operator<<(std::ostream& out, const my_vector<C>& rhs); // Перегрузка оператора вывода

private:
    T* _data;       // Динамический массив с данными
    size_t _size;  // Размер
    size_t _capacity;    // Вместимость
};

#include "vector.tpp"

#endif // VECTOR_H_

