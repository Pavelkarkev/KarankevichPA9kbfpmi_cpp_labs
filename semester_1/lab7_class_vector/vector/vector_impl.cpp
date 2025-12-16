#include "vector_impl.h"
size_t Vector::Size() const {
    return size;
}
size_t Vector::Capacity() const {
    return capacity;
}
int& Vector::operator[](size_t index) {
    return data[index];
}
const int& Vector::operator[](size_t index) const {
    return data[index];
}
int& Vector::At(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Out of Vectors range");
    }
    return data[index];
}
const int& Vector::At(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Out of Vectors range");
    }
    return data[index];
}
Vector::Vector() {
    size = 0;
    capacity = 1;
    data = new int[capacity];
}
Vector::Vector(size_t n) {
    size = n;
    if (size == 0) {
        capacity = 1;
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    } else {
        capacity = size;
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }
}

Vector::Vector(std::initializer_list<int> list) {
    size = list.size();
    capacity = size;
    data = new int[capacity];
    for (size_t i = 0; int item : list) {
        data[i] = item;
        ++i;
    }
}
Vector::~Vector() {
    delete[] data;
}
Vector& Vector::operator=(const Vector& other) {
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
void Vector::Swap(Vector& other) {
    std::swap(data, other.data);
    std::swap(size, other.size);
}
Vector::Vector(const Vector& other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}
void Vector::PushBack(int value) {
    if (size == capacity) {
        size_t new_capacity = capacity * 2;
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        data[size] = value;
        size++;
    } else {
        data[size] = value;
        size++;
    }
}
void Vector::PopBack() {
    if (size == 0) {
        throw std::out_of_range("Out of Vectors range");
    } else {
        size--;
    }
}
void Vector::Clear() {
    size = 0;
}
void Vector::Reserve(size_t n) {
    if (n > capacity) {
        size_t new_capacity = n;
        int* new_data = new int[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
}
std::ostream& operator<<(std::ostream& out, const Vector& vec) {
    if (vec.Size() == 0) {
        out << "[]";
        return out;
    } else {
        
        for (size_t i = 0; i < vec.Size(); ++i) {
            if (i == 0) {
                out << "[";
            }
            if (i == vec.Size() - 1) {
                out << vec[i] << "]";
            } else {
                out << vec[i] << "," << " ";
            }
        }
        
        return out;
    }
}
