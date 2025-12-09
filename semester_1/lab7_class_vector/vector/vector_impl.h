#pragma once

class Vector {
    private:
    int* data;
    size_t size;
    size_t capacity;

public:
    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }
    int& operator[](size_t index) {
        return data[index];
    }
    const int& operator[](size_t index) const {
        return data[index];
    }
    int& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Out of Vectors range");
        }
        return data[index];
    }
    const int& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Out of Vectors range");
        }
        return data[index];
    }
    Vector() {
        size = 0;
        capacity = 5;
        data = new int[capacity];
    }
    Vector(size_t n) {
        size = n;
        if (size == 0)
            capacity = 5;
        else {
            capacity = 2 * size;
        }
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }
    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    Vector(std::initializer_list<int> list) {
        size = list.size();
        capacity = size * 2;
        data = new int[capacity];
        for (size_t i = 0; int item : list) {
            data[i] = item;
            ++i;
        }
    }
    ~Vector() {
        delete[] data;
    }
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        size = other.size;
        capacity = other.capacity;
        delete[] data;
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);

        return *this;
    }
    void Swap(Vector& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
    }
    const Vector& PushBack(int a) {
        if (size = capacity) {
            Vector second(*this);
            second.capacity = second.capacity * 2;
            second[size] = a;
            second.size++;
            return second;
        }
        else {
            data[size] = a;
            size++;
            return *this;
        }
    }
    void PopBack(int a) {
        if (size == 0) {
            throw std::out_of_range("Out of Vectors range");
        }
        size--;
    }
    const Vector& Clear() {
        size_t temp = capacity;
        delete[] data;
        Vector second;
        second.data = new int[temp];
        second.capacity = temp;
        second.size = 0;
        return second;
    }
    const Vector& Reserve(size_t n) {
        if (n > capacity) {
            Vector second(*this);
            second.capacity = n;
            return second;
        }
        return *this;
    }
};
std::ostream& operator<<(std::ostream& out, const Vector& vec) {

    for (size_t i = 0; i < vec.Size(); ++i) {
        if (vec.Size() == 0) {
            out << "[]";
            return out;
        }
        if (i == 0) {
            out << "[";
        }
        if (i == vec.Size() - 1) {
            out << vec[i] << "]";
        }
        else {
            out << vec[i] << "," << " ";
        }
    }
    out << std::endl;
    return out;
};

