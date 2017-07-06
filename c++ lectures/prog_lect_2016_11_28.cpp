// ----------------------------------------------
#include <algorithm>
#include <list>
#include <vector>

int main() {
    std::vector<int> v = {3, 4, 5};
    std::list<int> l;
    
    // Скомпилируется, но не сработает, т.к. список l - пуст,
    // а алгоритм типа copy работает только с местом
    std::copy(v.begin(), v.end(), l.begin());
}

// Как исправить ситуацию:
int main() {
    std::vector<int> v = {3, 4, 5};
    std::list<int> l;
    
    l.resize(100);
    auto it = std::copy(v.begin(), v.end(), l.begin());
    l.erase(iter, l.end());
}

// Как решить правильно
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

int main() {
    std::vector<int> v = {3, 4, 5};
    std::list<int> l;
    
    // Новые элементы будут добавляться с помощью push_back
    // т.е. работает только с контейнерами, поддерживающими push_back
    auto it = std::copy(
        v.begin(),
        v.end(),
        std::back_inserter(l)  // можно также front_inserter
    );
}

// ----------------------------------------------
#include <iostream>

int main() {
    // unsigned - важно
    unsigned int x = 7;
    // 76543210 - расположение битов
    // 00000111         7
    // 00011100 x << 2: 28
    // 00000011 x >> 1: 3
    
    std::cout << (x << 2) << std::endl;  
    std::cout << (x >> 1) << std::endl;
    
    // Побитовый сдвиг влево соответствует умножению на 2 в степени n
    // Побитовый сдвиг вправо соответствует делению на 2 в степени n с отбрасыванием остатка
    
    
    // Хотим узнать, чему равен k-й бит числа
    
    // & и
    // | или
    // ~ не
    unsigned k = 2;
    bool result = x & (1 << k);
    
    // @=
    x = 31415;
    x |= (1 << k);  // установить k-й бит в 1
    // x      01010100 01010100
    // 1 << 2 00000000 00000100
    //        01010100 01010100
    
    x &= ~(1 << k); // сбросить k-й бит в 0
    // 1 << 2    00000100
    // ~(1 << 2) 11111011
    // 
}

// ----------------------------------------------
// std::bitset

#include <bitset>
#include <iostream>

int main() {
    std::bitset<10> b(7); // <?> - указываем размер в битах
    std::bitset<17> b2("010001101");
    
    // Три стандатрные функции: test, set, reset
    std::cout << b.test(0) << std::endl;
    b.set(4);
    std::cout < b.test(4) << std::endl;
}

// ----------------------------------------------
#include <cmath>
#include <iostream>

// Нельзя перегружать:
// :: ?: .* ->* sizeof (операторы приведения типа)

class Complex {
 public:  // Почитать про public/private
    double x, y;
    
    Complex(double a, double b = 0.0): x(a), y(b) {
    }
    
    double Re() const {
        return x;
    }
    
    double Im() const {
        return y;
    }
    double abs() const {
        return std::sqrt(Re() * Re() + Im() * Im());
    }
};

Complex operator - (const Complex& z) {
    return Complex(-z.Re(), -z.Im());
}

Complex operator + (const Complex& a, const Complex& b) {
    return Complex(a.Re() + b.Re(), a.Im() + b.Im();
}

Complex operator - (const Complex& a, const Complex& b) {
    return Complex(a.Re() - b.Re(), a.Im() - b.Im();
}

std::ostream& operator << (std::ostream& out, const Complex& z) {
    out << z.Re() << " + " << z.Im() << "i";
    return out;
}

Complex operator * (const Complex& a, const Complex& b) {
    return Complex(a.Re() * b.Re() - a.Im() * b.Im(), a.Re() * b.Im() + a.Im() * b.Re());
}

int main() {
    Complex z(3, 2);
    z.x = 0;
    z.y *= -1;
    Complex w = -z;
    Complex u = z + 2.0 * w;
    std::cout << z.Re() << std::endl;
    (std::cout << z) << std::endl; // 3 + 2i
    std::cout << z.abs() << std::endl;
}