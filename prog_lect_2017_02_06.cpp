// Читать про идиому RAII

class A {
};

class B{
};

class C{
 private:
    A* a;  // Такой указатель лучше обернуть в отдельный класс  --- принцип RAII
    B* b;
    
 public:
    C() {
        a = new A;  // Можно так оставить
        try {
            b = new B;
        } catch(...) {
            delete a;
            throw;
        }
        // b = new B;
    }
    ~C() noexcept {
        // ...
    }
};

//------Код в соответствии с идиомой RAII------------
// Делаем указатели правильно (с классами для них)

template <typename T>
class T_wrapper {
 private:
    T* ptr;
 public:
    T_wrapper(): ptr(new A) {}
    
    T_wrapper(consts T_wrapper& other): a(new T(*other.ptr)) {}  // Конструктор копирования
    
    T_wrapper& operaot = (const T-wrapper& other) {
        *ptr = *other.ptr;
        return *this;
    }
    
    ~T_wrapper() noexcept {
        delete ptr;
    };
    
    const T* Get() pconst {
        return prt;
    }
    
    T* Get() {
        return ptr;
    }
};

class C{
 private:
    T_wrapper<A> a;
    T_wrapper<B> b;
    
 public:  // Можно вообще не писать public
    C() {
    }
    // C(): a(), b() {}
    ~C() noexcept {
    }
};

int main() {
    A a;
    B b;
    C c;
}

//---------------------------------------
template <typename T>
class  Matrix {
 private:
    size_t m, n;
    T ** data;  // Указатель на указатель --- массив, элементами которого являются указатели на начало строки
 public: // Что бы было, если бы взяли низкоуровневый массив ^^^
    Matrix(size_t rows, size_t columns)
    : m(rows)
    , n(columns)
    {
        data = new T*[rows];  // Может произойти исключение, поэтому стоит обернуть в try-catch --> 93 строка
        for (size_t i = 0; i != rows; ++i{
            try {
                data[i] = new T[columns]; // Как здесь
            } catch (...) {
                for (size_t j = 0; j != i; ++j)
                    delete[] data[j];
                delete[] data;
                throw;
            }
            for (size_t j = 0; j != columns; ++j {
                data[i][j] = 0;
            }
        }
    }
    
    ~Matrix() {
        for (size_t i = 0; i != rows; ++i)
            delete [] data[i];
        delete[] data;
    }
};

//--------------------------------------------------------------
// Почитать что такое explicit (явный вызок конструктора, без мам, пап и операторов присваивания)
#include <iostream>
#include <memory>

namespace my_std { // напишем свой unique_ptr
template <typename T>
class unique_ptr {
 private:
    T* ptr;
 public:
    explicit unique_ptr(T* src = nullptr): ptr(src) {} 
    
    unique_ptr(const unique_ptr&) = delete;  // прочитать, что означает =  (не надо генерировать конструктор)
    void operator = (const unique_ptr&) = delete;  // --//--
    
    unique_ptr(unique_ptr&& tmp): ptr(tmp.ptr) {  // && --- ссылка на временный объект
        tmp.ptr = nullptr;
    }
    
    unique_ptr& operator = (unique_ptr&& tmp) {
        delete ptr;
        ptr = tmp.ptr;
        tmp.ptr = nullptr;
        return *this;
    }
    
    unique_ptr& operator = (T* src) {
        delete ptr;
        return *this;
    }
    
    ~unique_ptr() noexcept {
        delete ptr;
    }
    
    const T& operator* () const {
        return *ptr;
    }
}
}

char * foo() {  // Потенциальный источник багов, потому что мы эту функцию можем позвать без всего. Тогда вся память утечёт.
    // ...
    return mystd::unique_ptr<char>(new char[100]);
}

int main() {
    // int* ptr = new int(42);
    /* std::unique_ptr<int> ptr(new int(42)); */ // Вместо верхней строки, delete не нужон
    // //...
    // delete ptr;
    mystd::unique_ptr<int> ptr1;
    ptr1 = new int(17);
    auto ptr2(foo());
    
    // std::unique_ptr<int> ptr3(new int[100]); // Не тот delete будет вызываться.
    
    mystd::unique_ptr<int> ptr2(
        static_cast<mystd::unique_ptr<int>&&> ptr(1);  // не получится разыменовать
    );
    
    mystd::unique_ptr<int> ptr2(
        std::move(ptr1);  // Это лучше, чем на 172
    );
    
    /* std::unique_ptr<int>* ptr2 = &ptr; */
    /* auto ptr2(ptr); */ // Будет ошибка, потому что unique_ptr копировать нельзя     
}

//---------------------------------------
#include <memory>

int main() {
    std::shared_ptr<int> ptr1(new int(17));  // имеет встроенный счётчик ссылок
    
    auto ptr2 = ptr1;
    
    std::shared_ptr<int> ptr3;
    ptr3 = ptr1;  // Умные указатели можно копировать
}