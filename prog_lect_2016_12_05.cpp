class Date {
    private:
        int day, month, year;
    public:
        Date (int d, int m, int y)
            : day(d)
            , month(m)
            , year(y)
        {
            // Проверка корректности
        }
    public:
        int GetDay() const {
            return day;
        }
    // GetMonth, GetYear

    Date& void operator ++ () {
        ++day;
        if (...) {
            ++month;
            if (...) {
                ++year:
            }
        
        }
        
        // Date * const this;
        return *this;  // this - указатель на объект, с которым мы работаем в функции класса (левая часть оператора; то, что идёт перед точкой)
    }
    
    Date operator ++ (int) {
        Date old = *this;
        ++*this;
        return old;
    }
    
    Date operator - (int days) const {
        
    }
    
    Date& operator -= (int days) {
        // ...
        return *this;
    }
    
    int operator - (const Date& other) const {
        
    }
};

int main() {
    Date d(1, 2, 1999);
    d.GetDay();
    ++d;
    // d.operator++();  // то же самое, что ++d
    
    // d++;  // lvalue
    // d.operator++(42); // Постфиксный ++ принимает дополнительный int на вход
}

//--------------------------------------------------
class C{
    public:
        void f(int x, double y) const {
            // do something
        }
        
        void g(int x, double y) const;
};

void C::g(int x, double y) const {  // Функция не перестала быть внутренней
    // do something
}

void h(const C& c, int x, double y) {
    // do something
}

int main() {
    C obj;
    obj.f(1, 3.14);
    obj.g(2, 2.72);
    h(obj, 3, 6.28);
}

//----Шаблон---класса----------------------------
#inclue <iostream>
#include <vector>

template <typename T, size_t N>  // Размер должен быть известен во время компиляции
class Matrix {
    private:
        std::vector<std::vector<T>> data;
    public:
        Matrix(const T& x = T()) {
            data.resize(N);
            for (size_t i = 0; i != N; ++i) {
                data[i].resize(N);
                data[i][i] = x;
            }
        }
        
        T& operator()(size_t i, size_t j) {
            return data[i][j];
        }
        
        const T& operator()(size_t i, size_t j) const {
            return data[i][j];
        }
};

template <typename T, size_t N>
Matrix<T, N>& operator += (
    Matrix<T, N>& a,
    const Matrix<T, N>& b
) {
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != N; ++j) {
            a(i, j) += b(i, j);
        }
    }
    return a;
}

template <typename T, size_t N>
Matrix<T, N> operator + (
    const Matrix<T, N>& a,
    const Matrix<T, N>& b
) {
    // Matrix<T, N> sum; // Matrix<T, N> sum(a)
    // for (size_t i = 0; i != N; ++i) {
        // for (size_t j = 0; j != N; ++j) {
            // sum(i, j) = a(i, j) + b(i, j);  // sum(i, j) += b(i, j)
        // }
    // }
    // return sum;
    Matrix<T, N> sum(a);
    sum += b;
    return sum;
}

template <typename T, size_t N>
void printMatrix(const Matrix<T, N>& m) {
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != M; ++j) {
            std::cout << m(i, j) << '\t';
        }
        std::cout << std::endl;
    }
}

template <typename T, size_t N>
std::istream& operator >> (
    std::istream& in,
    Matrix<T, N>& m,
) {
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != N; ++j) {
            in >> m(i, j);
        }
    }
    return in;
}


// Скалярная матрица: сложение, умножение соответствуют этим же операциям над иксом
// (x 0 0)
// (0 x 0)
// (0 0 x)

int main() {
    Matrix<int, 3> m; // не надо ресайзить
    
    std::cin >> m;
    std::cout << "Result\n";
    printMatrix(m);
    
    return 0;
}