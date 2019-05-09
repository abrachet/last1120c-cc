#include <iostream>
#include <vector>
#include <memory>

struct Base {
    int a;

    Base(int a) : a(a) {}
    
    virtual ~Base() = default;

    virtual void print()
    {
        std::cout << a << std::endl;
    }
};

struct Derived : public Base {
    int b;

    Derived(int a) : Base(a), b(a) {}

    virtual void print() override {
        std::cout << "a: " << a << " b: " << b << std::endl;
    } 
};

int main()
{
    std::vector<std::unique_ptr<Base>> vec;

    vec.push_back(std::make_unique<Base>(Base(1)));
    vec.push_back(std::make_unique<Derived>(Derived(1)));

    for (auto& i : vec)
        i->print();
}