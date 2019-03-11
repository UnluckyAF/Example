#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename T>
class Polynomial {
private:
    vector<T> coef;

public:
    Polynomial() {
        coef.push_back(T());
        shorter();
    }
    void shorter() {
        if (coef.empty()) {
            return;
        }
        auto it = coef.end();
        while (it != coef.begin() && *--it == static_cast<T>(0)) {
        }
        coef.erase(++it, coef.end());
    }
    Polynomial(const vector<T>& v): coef(v) {
        if (coef.empty()) {
            coef.push_back(static_cast<T>(0));
        }
        shorter();
    }
    Polynomial(const T& num) {
        coef.push_back(num);
    }
    template <typename Iter>
    Polynomial(Iter b, Iter e) {
        copy(b, e, inserter(coef, coef.begin()));
        shorter();
    }
    bool operator==(const Polynomial<T>& p) const {
        return coef == p.coef;
    }
    bool operator!=(const Polynomial<T>& p) const {
        return !(*this == p);
    }
    Polynomial<T>& operator+=(const Polynomial<T>& p) {
        if (p.coef.empty()) {
            return *this;
        }
        if (coef.empty()) {
            coef = p.coef;
            return *this;
        }
        auto it = coef.begin(), it2 = p.coef.begin();
        while (it != coef.end() && it2 != p.coef.end()) {
            *it++ += *it2++;
        }
        copy(it2, p.coef.end(), coef.end());
        shorter();
        return *this;
    }
    Polynomial<T>& operator*=(const Polynomial<T>& p) {
        auto tmp(*this);
        coef.resize(coef.size() + p.coef.size() - 1, static_cast<T>(0));
        for (size_t s = 0; s < tmp.coef.size() + p.coef.size() - 1; ++s) {
            coef[s] = static_cast<T>(0);
            for (size_t i = 0, j = s - i; i < tmp.coef.size() && j > 0; ++i, --j) {
                if (j < p.coef.size()) {
                     coef[s] += tmp.coef[i] * p.coef[j];
                }
            }
            if (s < tmp.coef.size()) {
                coef[s] += tmp.coef[s] * p.coef[0];
            }
        }
        shorter();
        return *this;
    }
    Polynomial<T> operator*(const Polynomial<T>& p) const {
        auto tmp(*this);
        tmp *= p;
        return tmp;
    }
    Polynomial<T>& operator-=(const Polynomial<T>& p) {
        auto it = coef.begin(), it2 = p.coef.begin();
        while (it != coef.end() && it2 != p.coef.end()) {
            *it++ -= *it2++;
        }
        transform(it2, p.coef.end(), inserter(coef, coef.end()), [](const T& a) {return -a;});
        shorter();
        return *this;
    }
    Polynomial<T> operator+(const Polynomial<T>& p) const {
        auto tmp(*this);
        tmp += p;
        return tmp;
    }
    Polynomial<T> operator-(const Polynomial<T>& p) const {
        auto tmp(*this);
        tmp -= p;
        return tmp;
    }
    T operator[](const size_t& i) const {
        if (i >= coef.size()) {
            return static_cast<T>(0);
        }
        return coef[i];
    }
    int Degree() const {
        if (coef.size() == 1 && coef[0] == static_cast<T>(0)) {
            return -1;
        }
        return static_cast<int>(coef.size()) - 1;
    }
    auto begin() const {
        return coef.begin();
    }
    auto end() const {
        return coef.end();
    }
    T operator()(const T& point) const {
        T ans = static_cast<T>(0);
        for (auto it = coef.rbegin(); it != coef.rend(); ++it) {
            ans *= point;
            ans += *it;
        }
        return ans;
    }
    Polynomial<T> operator&(const Polynomial<T>& p) const {
        auto ans = Polynomial<T>(static_cast<T>(0));
        for (auto it = coef.rbegin(); it != coef.rend(); ++it) {
            ans *= p;
            ans += *it;
        }
        return ans;
    }
};

template <typename T>
bool operator==(const T& num, const Polynomial<T>& p) {
    return (p == num);
}

template <typename T>
bool operator!=(const T& num, const Polynomial<T>& p) {
    return (p != num);
}

template <typename T>
Polynomial<T> operator+(const T& num, const Polynomial<T>& p) {
    return p + num;
}

template <typename T>
Polynomial<T> operator-(const T& num, const Polynomial<T>& p) {
    return Polynomial<T>(num) - p;
}

template <typename T>
Polynomial<T> operator*(const T& num, const Polynomial<T>& p) {
    return p * num;
}

template <typename T>
ostream& operator<<(ostream& out, const Polynomial<T>& p) {
    if (p.Degree() == -1) {
        return out << static_cast<T>(0);
    }
    size_t ind = p.Degree();
    if (!ind) {
        return out << p[ind];
    }
    for (size_t i = 0; i <= static_cast<size_t>(p.Degree()); ++i) {
        if (p[ind - i] != static_cast<T>(0)) {
            if (p[ind - i] > static_cast<T>(0) && i > 0) {
                out << "+";
            }
            if (!(ind - i)) {
                out << p[ind - i];
                break;
            }
            if (p[ind - i] != static_cast<T>(1) && p[ind - i] != static_cast<T>(-1)) {
                out << p[ind - i] << "*";
            } else if (p[ind - i] == static_cast<T>(-1)) {
                out << "-";
            }
            out << "x";
            if (ind - i > 1) {
                out << "^" << ind - i;
            }
        }
    }
    return out;
}

int main() {
    vector<int> a = {2, 3, 2}, b = {-1, 1, 3, -2}, c = {10};
    Polynomial<int> x(a), z(b), h(c);
    //cout << h(100);
    //cout << x(2);
    //x = 0 * x;
    cout << (x & z)(1);
    for (auto i : x) {
        cout << i << " ";
    }
    cout << endl;
    /*for (size_t i = 0; i <= z.Degree(); ++i) {
        cout << z[i] << " ";
    }*/
    cout << z /*<< " " << x + 2 << x * c*/;
}
