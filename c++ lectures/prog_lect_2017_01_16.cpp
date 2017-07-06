//---------Обработка---ошибок---(исключения)----------

#include <vector>
#include <string>

class C{
 public:
    C() {
        std::cout << "C()\n";
    }
    C(const C&) {
        std::cout << "C(const C&)\n";
    }
    C& operator = (const C&) {
        std::cout << "operator =\n";
    }
    ~C() {
        // Деструктор
    }
}

void bar() {
    // ...
    std::string s;
    double y;
    C z;  // Деструктор вызовется
    // ...
    throw 42;  // <-- Здесь ошибка. Надо её сгенерировать.
    // В этот момент происходит скрутка стека (с корня вверх) = аварийное покидание функции bar()
    // Все переменные корректно "умирают". Вызываются деструкторы и пр.
    // ...
}

void foo(int x) {
    // ...
    std::vector<int> v;
    // ...
    try {
        // ...
        bar();
        // ...
    } catch (const std::string& s) {  // Если напишем (...), то ошибка обработается
        std::cout << "Exception: " << s << "\n";
    } catch (inx x) {  // Catch - перегруженная функция с 1 аргументом
        std::cout << "Exception: " << x "\n";
    } catch (...) {
        std::cout << "Exception\n";
    }
    // ...
}

int main() {
    // ...
    foo(17);
    // ...
}

//----------------------------------------------------

#include <stdexcept>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v(7);
    // std::cout << v[10] << "\n";  // Не проверяет корректность индекса
    try {
        std::cout << v.at(10) << "\n";  // Генерирует исключение при неверном индексе
    } catch (std::out_of_range&) {  // или std::exception& в библиотеке <exception>
        std::cout << "Exception caught\n";
    }
}

//----------------------------------------------------

#include <exception>
#incude <iostream>
#include <vector>

class C {
 public:
    static int counter;
    C() {
        ++counter;
        if (counter & 2 == 0)
            throw std::exception();
    }
    
    ~C() {
        throw 17;  // Опасно вызывать исключение в деструкторе
    }
}

int C::counter = 0;

// int main() throw (std::string, int, std::exception) { можно было писать так
// int main() noexcept { появилось это взамент верхнего - синоним к throw() - гарантия того,
// что функция не генерирует исключение
int main() {
    try {
        std::vector<C> v(100500);
        std::cout << v.size() << "\n";
        // std::vector<int> v(-1); тоже упадёт
        // std::vector<
    } catch (...) {
       std::cout << "Exception!\n";
    }
}

//----------------------------------------------------

#include <exception>
#include <iostream>

class IncorrectDate: public std::exception {  // наследование
};

class Date { 
 public:
    Date(int d, int m, int y) {
        if (m <= 0 || m > 12) {
            throw IncorrectDate();
        }
    }
};

int main() {
    try {
        int d, m, y;
        std::cin >> d >> m >> y;
        Date date(d, m, y);
        // ...
    } catch (const IncorrectDate& e) {
        std::cout << "Bad date! " << e.what() << "\n";
    }
}

//----------------------------------------------------

#include <iostream>

int main() {
    static_assert(2 * 2 == 5, "Something strange!\n");  // проверка на этапе компиляции
    int x = 2;
    const int z = x;
    static_assert(z * z == 4, "Something strange!\n");  // Не должно работать, т.к. переменная объявляется после компиляции
}

//----------------------------------------------------

template <int M, int N>  // Шаблонные параметры известны вр время компиляции
class Matrix {
 public:
    Matrix Inverse() const {
        static assert(M == N, "Cannot invert non-square matrices\n";
        return *this;
    }
};

int main() {
    static_assert(sizeof(size_t) == 8, "Not a 64-bit platform!");
    Matrix<3, 4> m;
    m.Inverse();
}

//----------------------------------------------------

#include <cassert>
#include <iostream>

int main() {
    int x, y;
    std::cin >> x >> y;
    
    assert(x == y);  // работает runtime (в debug-режиме)
}