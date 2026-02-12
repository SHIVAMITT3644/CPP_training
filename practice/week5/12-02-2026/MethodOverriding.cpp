#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() {   // Base class function
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() {   // Overriding function
        cout << "Dog barks" << endl;
    }
};

int main() {
    Animal* ptr;
    Dog d;

    ptr = &d;
    ptr->sound(); 

    return 0;
}