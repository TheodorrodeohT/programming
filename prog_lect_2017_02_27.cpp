//------------Реализация---класса---vector---для---целых---чисел------------------------
// Tip: Все контейнеры стандартной библиотеки не содержат виртуальных конструкторов
#include <algorithm>  // copy
#include <cstddef>  // size_t

class Vector {
private:
    using T = int;
    
    T * data = nullptr;  // Можно указать в конструкторе
    size_t sz = 0;  // -//-
    size_t cp = 0;  // -//-
    
public:
    // Конструктор
    Vector() {}
    
    Vector(const Vector& other) // конструктор копирования
        : data(new T[other.sz])  // (!) Может выпасть исключение на закончившуюся память, но нестрашное
        , sz(other.sz)
        , cp(sz)
    {
        // for (size_t i = 0; i != other.sz; ++i)  // Можно писать через цикл, но пока пользуемся std::copy
        //     data[i] = other.data[i];
        // data[i] == *(data + i) -- синтаксический сахар
        std:copy(
            other.data,
            other.data + other.sz,
            data
        );
    }

    Vector(Vector&&)  //  конструктор перемещения
        : data(other.data)
        , sz(other.sz)
        , cp(other.cp)
    {
        other.data = nullptr;
        other.sz = 0;  // Потому что этот объект ещё может быть использованным
        other.cp = 0;  // Поэтому нужны эти две строки, для согласованности
    }
    
    Vector(size_t n, T elem);  // Написать самостоятельно
    
    // Деструктор
    ~Vector() {
        delete[] data;
    }
    
    // Оператор присваивания
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    
    // Работа с размером
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    
    void resize(size_t n) {
        if (n <= sz) {
            sz = n;
            return;
        } else if (sz < n && n <= cp) {
            /* std::fill(
                data + sz,
                data + n,
                0
            ); */
            for (size_t i = sz; i != n; ++i)
                data[i] = 0;
            sz = n;
            return;
        } else {
            T* new_data = new T[n];  // (!) Может дать исключение
            std::copy(  // (!) При T != int может выпасть исключение
                data,
                data + sz,
                new_data
            );
            delete[] data;
            data = new_data;
            sz = cp = n;
        }
    }
    
    void reserve(size_t n);
    
    // Методы front(), back()
    T front() const;  // Можно возвращать константную ссылку
    T& front();
    T back() const;
    T& back();
    
    // Оператор []
    T operator[](size_t i) const;
    T& operator[](size_t i);
    
    // Добавление элементов
    void push_back(T elem);
    void pop_back();  // Ни у стека, ни у вектора тип не возвращает
};

int main() {
    Vector v;
    v.resize(1);
    
    return 0;
}