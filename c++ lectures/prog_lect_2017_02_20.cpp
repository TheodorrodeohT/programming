#include <iostream>
#include <string>
#include <vector>

// HAS-A --- первый тип отношений  --- реализуется наследование
// IS-A --- второй тип отношений --- реализуется композиция

// Полиморфизм, виртуальные функции

class Animal {
public:
    // virtual std::string voice() const{ // VIRTUAL + override + = 0
    //     return "Not implemented";
    // }
    virtual std::string voice() const = 0;
};

std::string Animal::voice() const { // чё эт
    return "not implemented";
}

class Cat: public Animal {
public:
    std::string voice() const override { // OVERRIDE, final
        return "Meow";
    }
};

class Dog: public Animal {
public:
    std::string voice() const override {
        return "Woof2";
    }
};

int main() {
    Animal a;
    std::cout << A.voice << "\n";
    
    Cat c;
    std::cout << c.Animal::voice() << std::endl;
    std::cout << c.voice() << std::endl;
    
    Dog d;
    std::cout << d.voice() << std::endl;
    
    std::cout << "===============" << std::endl;
    
    std::vector<Animal*> animals;
    
    // animals.push_back(&a):
    animals.push_back(&c):
    animals.push_back(&d):
    
    for (const auto& a : animals)
        std::cout << a.voice() << "\n";
    
    return 0;
}

//--------------------Фабрика--------------------------

class Animal {
public:
// Если есть виртуальный конструктор, то и виртуальный деструктор также необходим
    virtual std::string voice() const = 0;
    virtual ~Animal() {
        std::cout << "~Animal()\n";
    }
};

std::string Animal::voice() const { // чё эт
    return "not implemented";
}

class Cat: public Animal {
public:
    std::string voice() const override { // OVERRIDE, final
        return "Meow";
    }
    ~Cat override () {
        std::cout << "~Cat()\n";
    }
};

class Dog: public Animal {
public:
    std::string voice() const override {
        return "Woof2";
    }
    ~Dog override () {
        std::cout << "~Dog()\n";
    }
};

std:: vector<std::unique_ptr<Animal>> factory() {
    std::string line;
    std::vector<std::unique_ptr<Animal>> result;
    while (std::cin >> line) {
        if (line == "cat") {
            result.emplace_back(new Cat); // EMPLACE!
            // result.push_back(std::unique_ptr<Cat> (new Cat));
        } else if (line == "dog") {
            result.emplace_back(new Dog);
            // result.push_back(new Cat);
        }
    }
    return result;
}

int main() {
    auto animals = factory();
    
    for (const auto& animal : animals)
        std::cout << animal->voice() << "\n";
    
    return 0;
}

//----------------------------------------------
class A {
public:
    A() { std::cout << "A()\n"; }
    ~A() { std::cout << "~A()\n"; }
};

class B: public A {
public:
    B() { std::cout << "B()\n"; }
    ~B() { std::cout << "~B()\n"; }
    
};

class C {
public:
    C() { std::cout << "C()\n"; }
    ~C() { std::cout << "~C()\n"; }
    
};

class D: public B {
public:
    C element;
    D() { std::cout << "D()\n"; }
    ~D() { std::cout << "~D()\n"; }
};

int main() {
    D d; // Вывод ABCD ~D~C~B~A, потому что всё идёт изнутри наружу (наследование) 
    std::cout << "Object created!\n";
}