#pragma once

#include <iostream>
class Vector {
private:
    int* data;
    size_t size;
    size_t capacity;

public:
    size_t Size() const;

    size_t Capacity() const;

    int& operator[](size_t index);

    const int& operator[](size_t index) const;

    int& At(size_t index);

    const int& At(size_t index) const;

    Vector();

    Vector(size_t n);

    Vector(const Vector& other);

    Vector(std::initializer_list<int> list);

    ~Vector();

    Vector& operator=(const Vector& other);

    void Swap(Vector& other);

    void PushBack(int a);

    void PopBack();

    void Clear();

    void Reserve(size_t n);

};
std::ostream& operator<<(std::ostream& out, const Vector& vec);


