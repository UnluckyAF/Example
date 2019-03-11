#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
class Matrix;

template <typename T>
class ConstIterator {
private:
    const Matrix<T>* matrix;
    size_t row = 0, column = 0;

public:
    ConstIterator(const Matrix<T>* mat, const size_t& r, const size_t& c)
    : matrix(mat)
    , row(r)
    , column(c) {
    }
    bool operator==(const ConstIterator<T>& it2) const {
        return matrix == it2.matrix && row == it2.row && column == it2.column;
    }
    bool operator!=(const ConstIterator<T>& it2) const {
        return !(*this == it2);
    }
    const T& operator*() const {
        return (*matrix)[row][column];
    }
    ConstIterator<T>& operator++() {
        ++column;
        if (column == (*matrix)[0].size()) {
            ++row;
            column = 0;
        }
        return *this;
    }
    ConstIterator<T> operator++(int) {
        auto tmp(*this);
        ++(*this);
        return tmp;
    }
};

template <typename T>
class Iterator {
private:
    Matrix<T>* matrix;
    size_t row = 0, column = 0;

public:
    Iterator(Matrix<T>* mat, const size_t& r, const size_t& c)
    : row(r)
    , column(c) {
        matrix = mat;
    }
    bool operator==(const Iterator<T>& it2) const {
        return matrix == it2.matrix && row == it2.row && column == it2.column;
    }
    bool operator!=(const Iterator<T>& it2) const {
        return !(*this == it2);
    }
    T& operator*() {
        return (*matrix)[row][column];
    }
    const T& operator*() const {
        return (*matrix)[row][column];
    }
    Iterator<T>& operator++() {
        ++column;
        if (column == (*matrix)[0].size()) {
            ++row;
            column = 0;
        }
        return *this;
    }
    Iterator<T> operator++(int) {
        auto tmp(*this);
        ++(*this);
        return tmp;
    }
};

template <typename T>
class Matrix {
private:
    size_t rows = 0, columns = 0;
    vector<vector<T>> table;

public:
    Matrix(const vector<vector<T>>& v) {
        table = v;
        rows = v.size();
        if (rows) {
            columns = v[0].size();
        }
    }
    vector<T>& operator[](const size_t& i) {
        return table[i];
    }
    const vector<T>& operator[](const size_t& i) const {
        return table[i];
    }
    pair<size_t, size_t> size() const {
        return {rows, columns};
    }
    void resize(const size_t& r, const size_t& c) {
        table.resize(r, vector<T> (c, 0));
        rows = r;
        for (auto v : table) {
            v.resize(c);
        }
        columns = c;
    }
    Matrix<T>& transpose() {
        auto tmp(*this);
        table.resize(tmp.size().second);
        rows = tmp.size().second;
        columns = tmp.size().first;
        for (size_t j = 0; j < tmp.size().second; ++j) {
            table[j].resize(tmp.size().first);
            for (size_t i = 0; i < tmp.size().first; ++i) {
                table[j][i] = tmp[i][j];
            }
        }
        return *this;
    }
    Matrix<T> transposed() const {
        auto tmp(*this);
        return tmp.transpose();
    }
    Matrix<T>& operator*=(const Matrix<T>& other) {
        assert((*this).size().second == other.size().first);
        auto tmp(*this);
        columns = other.size().second;
        for (size_t i = 0; i < tmp.size().first; ++i) {
            table[i].resize(other.size().second);
            for (size_t j = 0; j < other.size().second; ++j) {
                table[i][j] = 0;
                for (size_t k = 0; k < tmp.size().second; ++k) {
                    table[i][j] += tmp[i][k] * other[k][j];
                }
            }
        }
        return *this;
    }
    Matrix<T> operator*(const Matrix<T>& other) {
        auto tmp(*this);
        return tmp *= other;
    }
    auto begin() const {
        return ConstIterator<T>(this, 0, 0);
    }
    auto begin() {
        return Iterator<T>(this, 0, 0);
    }
    auto end() const {
        return ConstIterator<T>(this, rows, 0);
    }
    auto end() {
        return Iterator<T>(this, rows, 0);
    }
};


template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& m) {
    for (size_t i = 0; i < m.size().first - 1; ++i) {
        out << m[i][0];
        for (size_t j = 1; j < m.size().second; ++j) {
            out << '\t' << m[i][j];
        }
        out << endl;
    }
    out << m[m.size().first - 1][0];
    for (size_t j = 1; j < m.size().second; ++j) {
        out << '\t' << m[m.size().first - 1][j];
    }
    return out;
}

template <typename T>
Matrix<T>& operator+=(Matrix<T>& a, const Matrix<T>& b) {
    for (size_t i = 0; i < a.size().first; ++i) {
        for (size_t j = 0; j < a.size().second; ++j) {
            a[i][j] += b[i][j];
        }
    }
    return a;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b) {
    auto tmp(a);
    return tmp += b;
}

template <typename T, typename N>
Matrix<T>& operator*=(Matrix<T>& a, const N& s) {
    for (size_t i = 0; i < a.size().first; ++i) {
        for (size_t j = 0; j < a.size().second; ++j) {
            a[i][j] *= s;
        }
    }
    return a;
}

template <typename T, typename N>
Matrix<T> operator*(const Matrix<T>& a, const N& s) {
    auto tmp(a);
    return tmp *= s;
}

int main() {
    vector<vector<int>> v = {{1, 2, 3}, {2, 3, 4}};
    const Matrix<int> t(v), k = v, z(t);
    //cout << (t.begin() == t.begin());
    //cout << *(++t.begin());
    cout << ":EERWER" << endl;
    auto p = t.begin();
    cout << *(p++) << endl;
    cout << *(p++) << endl;
    cout << *(p++) << endl;
    cout << *(p++) << endl;
    cout << *(p++) << endl;
    cout << *(p++) << endl;
    cout << (p == t.end());
    for (auto i = t.begin(); i != t.end(); ++i) {
        cout << *i << " ";
    }
}
