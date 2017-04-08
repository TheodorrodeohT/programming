//----------------------------------------------
#include <iostream>
#include <vector>

template <typename T, size_t N>
class Matrix {
    private:
     std::veector<std::vectpr<T>> data;
    public:
     Matrix() {
         data.resize(N);
         for (auto& row : data)
             row.resize(N);
     }
     T& operator() (size_t i, size_t j) {
         return data[i][j];
     }
     T operator ()(size_t, size_t j) const {
         return data[i][j];
     }
     
     using iterator = decltype(data.begin());
     using const_iterator = decltype(data.cbegin());
     
     // Благодаря using заместо typename можно писать iterator
     typename
     std::vector<std::vector<T>>::iterator
     end() {
         return data.end();
     }
     
     typename  // Хотим написать имя сложного типа, в середине которого есть сложный шаблонный параметр
     std::vector<std::vector<T>>::iterator
     begin() {
         return data.begin();
     }
     decltype(data.begin())  // decltype - определить типа выражения в скобках (== auto)
     end() {
         return data.end();
     }
     decltype(data.cbegin())  // константный
     end() const {
         return data.end();
     }
     typename
     std::vector<std::vector<T>>::const_iterator  // константный итератор
     begin() const {
         return data.begin();
     }
}

//----------------------------------------------
#include <iostream>
#include <vector>

template <typename T, size_t N>  // forward declaration
class Matrix;

template<Typename T, size_t N>
class Matrix_iterator {
    private:
    // Matrix<T, N>* m;
    // Matrix<T, N>& m;
    // Matrix<T, N> m;  // Так не получится
    
    // В целях упрощения делаем через ссылку
     Matrix<T, N>& matrix;
     size_t i, j;
    public:
     Matrix_iterator(
        Matrix<T, N>& m,
        size_t _i,
        size_t _j
        )
            : matrix(_m)
            , i(_i)
            , j(_j)
     {
     }
    
    //  Matrix<int, 3> m;
    //  for (auto it = m.begin(); it != m.end(); ++it)
    //      std::cout << *it << " ";
    
    bool operator == (Matrix_iterator other) const {
        return i == other.i && j == other.j;
    }
    bool operator != (Matrix_iterator other) const {
        return !(*this == other);
    }
    
    T& operator * () {
        return matrix(i, j);
    }
    
    Matrix_iterator<T, N> begin() {
        return Matrix_iterator<T, N>(*this, 0, 0);
    }
    
    Matrix_iterator<T, N> end() {
        return Matrix_iterator<T, N>(*this, 0, n);
    }
    
    /*
    T* operator -> () {
        return &matrix(i, j);
    }
    */
    
    Matrix_iterator& operator++ () {
        ++i;
        if (i == N) {
            i = 0;
            ++j;
        }
        return *this;
    }
    
    Matrix_iterator operator++ (int) {
        auto copy = *this;
        ++*this;
        return copy;
    }
};


template <typename T, size_t N>
class Matrix {
    private:
     std::veector<std::vectpr<T>> data;
    public:
     Matrix() {
         data.resize(N);
         for (auto& row : data)
             row.resize(N);
     }
     T& operator() (size_t i, size_t j) {
         return data[i][j];
     }
     T operator ()(size_t, size_t j) const {
         return data[i][j];
     }
     
     // ++
     // ==
     // !=
     // *
     // ->  a->b  (*a).b
}

int main() {
    Matrix<int, 3> m;
    
    size_t i = 1;
    for (int& elem : m) 
        elem = i++;

    for (size_t i = 0; i != 3; ++i)
        for (size_t j = 0; j != 3; ++j)
            std::cout << m(i, j) << "\t";
        std::cout << std::endl;
}

//--------------------------------------
struct Complex {
    double re, im;
};

int main() {
    std::vector<Complex> v;
    
    for (auto it = v.begin(); it != v.end(); ++it) {
        stsd::cout << (*it).re << " " << (*it).im << std::endl;
        std::cout << it->re << " " << it->im << std::endl;
    }
}