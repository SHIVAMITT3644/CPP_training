#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() = 0;

    virtual ~Animal() {}
};

// Derived class
class Dog : public Animal {
public:
    void sound() override {
        cout << "Dog barks" << endl;
    }
};

int main() {
    Animal* a = new Dog();  // base class pointer
    a->sound();             // calls Dog's implementation

    delete a;
    return 0;
}