// ----------------------------------------------
//stack - основан на контейнере deque
//queue
//priority_queue

// LIFO
// Stack:
#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::stack<int, std::vector<int>> s;
    s.push(1);
    s.push(13);
    s.pop();
    
    std::cout << s.top() << std::endl;  // Будет напечатано 1
    
    if (s.empty()) {
        //...
    }
}

// ----------------------------------------------
//FIFO (first in first out)
// Queue:
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::queue<int/*, std::vector<int>*/> s;  // Вместо вектора deque по умолчанию. Вместо него можно юзать list
    s.push(1);
    s.push(13);
    s.pop();
    
    std::cout << s.front() << std::endl;  // Будет напечатано 13
    
    if (s.empty()) {
        //...
    }
}

// ----------------------------------------------
// Priority queue:
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::prioroty_queue<
        int, 
        std::vector<int>,  // 2 - необязательный шаблонный параметр
        std::greater<int>  // 3 - необязательный параметр - компаратор (по умолчанию std::less<int>)
    > s;
    
    for (int x : {3, 14, 15, 92, 6})
        s.push(x);
    s.pop();
    
    while (!s.empty()) {  // Будет напечатано всё в порядке возрастания (std::greater) (но внутри не отсортированно)
        std::cout << s.top() << std::endl;
        s.pop();
    }
}

// Структура в очереди:
struct Time {
    int h, m, s;
};

bool operator < (const Time& a, const Time& b) {
    return a.h < b.h;  //...
}

int main() {
    std::prioroty_queue<Time> s;
    
    for (int x : {3, 14, 15, 92, 6})
        s.push(x);
    s.pop();
    
    while (!s.empty()) {  // Будет напечатано всё в порядке возрастания (std::greater) (но внутри не отсортированно)
        std::cout << s.top() << std::endl;
        s.pop();
    }
}

// ----------------------------------------------
//en.cppregerence.com/w/cpp/algorithms
// Ф-я erase

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {5, 13, 12, -293, 10};
    std::remove(
        v.begin(),
        v.end(),
        5
    );
    
    for (int x : v)
        std::cout << x << " ";  // В конце окажется две десятки
    std::cout << std::endl;
}

// Как убрать элемент совсем:
int main() {
    std::vector<int> v = {5, 13, 12, -293, 10};
                         {13, 12, -293, 10, 10}
                         [^                 ^)
                         [^                   ^)
    auto iter = std::remove(
        v.begin(),
        v.end(),
        5
    );
    
    v.erase(iter, v.end());
    
    for (int x : v)
        std::cout << x << " ";  // В конце окажется ничего
    std::cout << std::endl;
}

// ----------------------------------------------
// Ф-я unique

int main() {
    std::vector<int> v = {5, 13, 12, 5, -293, 10};
    auto iter = std::unique(
        v.begin(),
        v.end(),
    );
    v.erase(iter, v.end());
    for (int x : v)
        std::cout << x << " ";  // всё останется, как было, поэтому надо сортить
    // {5, 5, 13, 12, 5, -293, 10} на выводе получили бы: 5, 13, 12, 5, -293, 10
    
    std::cout << std::endl;
}

// ----------------------------------------------
// Набор алгоритмов для отсортированных последовательностей
// binary_search - возвращает true/false

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 4, 5, 9, 13, 47};
    
    std::cout <<
        (std::binary_search(v.begin(), v.end(), 4) ? "YES" : "NO") << std::endl;
}

// ----------------------------------------------
// lower_bound - возвращает конкретный итератор на первый элемент, который не меньше заданного

int main() {
    std::vector<int> v = {1, 4, 5, 9, 13, 47};
    
    auto iter = std::lower_bound(
        v.begin(),
        v.end(),
        9  // Если напишем 8, то так же вернёт 3
    );

    if (iter != v.end() && *iter == 8)
        std::cout << "FOUND\n";
    
    std::cout << (iter - v.begin()) << std::endl;  // Вернёт 3
}

// ----------------------------------------------
// Теоретико-множественные операции
// set-intersection (union, difference) - находит пересечение двух отсортированных интервалов

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v1 = {1, 3, 5, 7, 9}, v2 = {1, 2, 3, 4};
    vector<int> out(v1.size());
    
    auto iter = set_intersection(
        v1.begin(),
        v1.end(),
        v2.begin(),
        v2.end(),
        out.bein()
    );
    
    out.erase(iter, out.end());
    
    for (int x : out)
        cout << x << " ";