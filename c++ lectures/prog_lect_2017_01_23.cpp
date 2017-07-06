
void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

void swap(int * a, int * b) { // придётся делать кучу проверок
    int c = *a;
    *a = *b;
    *b = c;
}

int main() {
    int x = 1, y = 2;
    swap(x, y); // 1-z версия
    swap(&x, &y); // 2-z версия
    swap(nullptr, &y);
}

//----------------------------------------
#incluide <iostream>

int& f() {
    int x = 17;
    return x;
}

int main() {
    int * ptr;
    {
        int x = 17;
        ptr = &x;
    }
    std::cout << *ptr << "\n";
}

//----------------------------------------
#inlclude <iostream>

class C{
public:
    C() {
        std::cout << "C()\n";
    }
    ~C() {
        std::cout << "~C()\n";
    }
};

int main() {
    int * ptr = new int(42);  // new делает:
    // (1) запрашивает кусок памяти для int и получает её адрес
    // (2) Конструирует int в этой ячейке
    * ptr = 17;
    std::cout << *ptr << "\n";    
    delete prt;  // вернули память:
    // (1) вызываем деструктор (у int деструктора нет)
    // (2) возвращаем память ОС
    
    // int x
    // delete &x;  // жуткая ошибка
}

//----------------------------------------
#inlclude <iostream>

class C{
 public:
    C() {
        std::cout << "C()\n";
    }
    ~C() {
        std::cout << "~C()\n";
    }
};

int main() {
    C * ptr = new C;
    delete ptr;  // вызывает деструктор
}

//----------------------------------------

int main() {
    int * ptr = new int[10]; // НИЗКОУРОВНЕВЫЙ МАССИВ
    // 0 | 0 | 0 | 0 | 0...
    *ptr = 17;
    // 17| 0 | 0 | 0 | 0...
    *(ptr + 1) = 42
    // 17| 42| 0 | 0 | 0...
    // ptr + i;
    // ++ptr; ptr++;
    // --ptr; ptr--;
    // int * ptr2 = ptr + 9;
    // ptr2 - ptr
    // т.о. можно осздавать НИЗКОУРОВНЕВЫЕ МАССИВЫ
    delete[] ptr;
    
    int ptr = 42;
}

//----------------------------------------
// Играемся с языком Си
#include <iostream>
int main() {
    char * s1 = new char[100];
    for (size_t i = 0; i != 100; ++i)
        s1[i] = 'b';
    delete[] s1;
    
    char * s = new char[10];  // Должна быть ошибка
    // std::cin >> s;
    for (size_t i = 0; i != 11; ++i)
        s[i] = 'a';
    std::cout << "Hello, " << s << "\n";
    delete[] s;
}

//----------------------------------------
// Играемся с языком Си
#include <iostream>
int main() {
    std::string 2;
    
    char * s = new char[10];
    std::cin >> s;
    s[4] = 0;  // Что это такое
    // for (size_t i = 0; i != 11; ++i)
    //    s[i] = 'a';
    std::cout << "Hello, " << s << "\n"; // выводит aaaa
    delete[] s;
}

//----------------------------------------
// Играемся с Си
#include <iostream>

int main() {  // Ошибка
    char * s;
    std::cin >> s;
    std::cout << s << "\n";
}

int main() {  // Не ошибка
    char * s = new char[100];
    std::cin >> s;
    std::cout << s << "\n";
    delete[] s;
}

//----------------------------------------
// Играемся с Си
#include <algorithm>
#include <iostream>
#include <cstring>

bool strcmp // написать дома



int main() {
    char * s1 = new char[100];  // Ещё 1 ячейка под символ с кодом 0
    char * s2 = new char[100];
    std::cin >> s1;
    std::cin >> s1;
    // std::cout <<< (s1 == s2) << "\n";  // При одинаковых строках выдаст 0 (еслиразный new char[xxx])
    // std::copy(s1, s1 + 100, s2);
    strcpy(s2, s1);
    std::cout << (strcmp(s1, s2) == 0) <<"\n";  // Нормально
    delete[] s1;
    delete[] s1;
}