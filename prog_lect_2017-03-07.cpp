//-----------------------------------------------
#include <

// Struct, потому что подчёркиваем, что слова открыты.
template <typename T>
struct VectorBase {  // Вспомогательный класс. Будет владеть сырой памятью (unique_ptr над сырой памятью)
    T * data;
    size_t cp;
    
    VectorBase()
        : data(nullptr)
        , cp(0)
    {
    }
    
    VectorBase(size_t n)
        : data (static_cast<T*>(
            operator new (n * sizeof(T))
        ))
        , cp(n)
        noexcept
    {
    }
    
    VectorBase(const VectorBase&) = delete;  // Запрещаем конструктор копирования
    VectorBase& operator = (const VectorBase&) = delete;  // Запрещаем оператор присваивания с семантикой копирования
    
    VectorBase(VectorBase&& other)
        : data(other.data)
        , cp(other.cp)
        noexcept
    {
        other.data = nullptr;
        other.cp = 0;
    }
    
    VectorBase& operator = (VectorBase&& other) noexcept {  // Оператор присваивания с move семантикой (например возвращаем из функции)
        // std::swap(data, other.data);  // свопаем только адреса (дешево, быстро и безопасно)
        // std::swap(cp, other.cp);
        swap(other);
        return *this;
    }
    
    ~VectorBase() noexcept {
        operator delete (data);
    }
    
    void swap(VectorBase& other) {
        std::swap(data, other.data);
        std::swap(cp, other.cp);
    }
};

template <typename IterIn, typename IterOut>
iterOut uninitialized_copy(
    IterIn first, IterIn last, IterOut out
)
{
    using T = decltype(*out);
    IterOut current = out;
    try {
        while (first != last)
            new (&*current++) T(*first++);
        return current;
    } catch(...) {
        while (out != current) {
            out->~T();
            ++out;
        }
        throw;
    }
}

template <typename IterIn, typename IterOut>
iterOut uninitialized_move(
    IterIn first, IterIn last, IterOut out
)
{
    using T = decltype(*out);
    IterOut current = out;
    try {
        while (first != last)
            new (&*current++) T(std::move(*first++));  // std::move() делает static_cast
        return current;
    } catch(...) {
        while (out != current) {
            out->~T();
            ++out;
        }
        throw;
    }
}

template <typename T>
class Vector {
private:
    // T * data;
    // size_t cp;
    VectorBase<T> base;
    size_t sz;
    
    void destroy() {
        for (size_t i = 0; i != sz; ++i) 
            base.data[i].~T();
    }
    
public:
    Vector(const Vector& other)  // Наивно, надо переписать с учётом VectorBase<T> base;
    : data( static_cast<T*>(  // Зовём сырую память
        operator new (n * sizeof(T))  // (!) может выкинуть исключение (память)
      ))
    , sz(other.sz)
    , cp(other.sz)
    {  // Конструктор копирования
        // data = new T[other.sz];  // Наивно, потому что дважды копируем элементы. Аналог std::copy
        // for (size_t i = 0; i != other.sz; ++i) {
        //     data[i] = other.data[i];
        // }
        size_t i = 0;
        try {
            for (; i != sz; ++i)
                new (data + i) T(other[i]);  // (!) может выкинуться исключение из T.
        } catch(...) {
            for (size_t j = 0; j != i; ++j)
                data[j].~T();  // == *(data + j).~T();
            operator delete(data);
            throw;
        }
        
    }
    
    Vector(const Vector& other) // Хорошая версия
        : base(other.sz)
        , sz(other.sz)
    {
        std::uninitialized_copy(
            other.base.data,
            other.base.data + sz,
            base.data
        );
    }
    
    size_t size() const noexcept {
        return sz;
    }
    
    ssize_t capacity() const noexcept {
        return base.cp;
    }
    
    void reserve(size_t n) {
        if (n <= capacity())
            return;
        
        VectorBase<T> vb_new(n);
        unitialized_move(
            base.data,
            base.data + size(),
            vb_new.data
        );
        
        destroy();
        base = std::move(vb_new);
    }
    
    Vector& operator = (const Vector& other) {  // Идиома copy and swap
        Vector tmp(other);
        swap(tmp);  // Себя свопает с кем-то.
        return *this;
    }
    
    void swap(Vector& other) noexcept {
        base.swap(other.base);
        std::swap(sz, other.sz);
    }
    
    ~Vector() {
        destroy();
    }
};

template <typename T>
void swap(T& a, T& b) {
    T c = std::move(a);
    a = std::move(b);
    b = std::move(c);
}

int main() {
    T * data;
    
    //data = new T[n];  // Хотим это дело разбить
    data = static_cast<T*>(  // 1. Получение сырой памяти.
        operator new (n * sizeof(T))  // Передаём на вход количество байт
    );
    
    // 2. Placement new -- "размещающий new", определяем элемент в определённое место в памяти.
    size_t i = ...;
    new (data + i) T();  // Первые скобки -- адрес(== &); можем делать только с памятью, которой владеем
    
    // 3. Руками зовём деструктор, потому что вдруг T выделял ещё памяти.
    data[i].~T();
    
    operator delete(data);
}