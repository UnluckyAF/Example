#include <cstddef>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class Vector {
private:
    size_t capacity;
    size_t size;
    T* vec;

public:
    explicit Vector(int s = 1):capacity(s), size(0) {
        vec = new T[s];
    }
    Vector(const int& s, const T& elem): capacity(s), size(s) {
        vec = new T[s];
        for (size_t i = 0; i < s; ++i) {
            *(vec + i) = elem;
        }
    }
    ~Vector() {
        delete vec;
    }
    void push(const T& elem) {
        if (size + 1 > capacity) {
            T* ptr;
            ptr = new T[capacity *= 2];
            for (size_t i = 0; i < size; ++i) {
                *(ptr + i) = *(vec + i);
            }
            delete vec;
            vec = ptr;
        }
        vec[size] = elem;
        ++size;
    }
    void pop() {
        vec[--size] = T(0);
    }
    T& front() const {
        if (!size) {
            throw "Vector is empty.";
        }
        return vec[0];
    }
    T& back() const {
        if (!size) {
            throw "Vector is empty.";
        }
        return vec[size - 1];
    }
    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }
    T& operator[](const size_t& ind) {
        return vec[ind];
    }
    const T& operator[](const size_t& ind) const {
        return vec[ind];
    }
};

#include <iostream>
#include <vector>
int main() {
    Vector<int> a;
    cout << a.Capacity() << " " << a.Size() << " " << /*a.front() <<*/ " " << /*a.back() <<*/ " " << a[0];
    a.push(2);
    cout << a.Capacity() << " " << a.Size() << " " << a.front() << " " << a.back() << " " << a[0];

}
