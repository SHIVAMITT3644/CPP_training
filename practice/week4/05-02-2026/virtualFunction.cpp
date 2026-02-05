#include <iostream>

class Animal 
{
    int a;
    public: 
    virtual void speak ()
    {
        std::cout << "HII\n";
    }
};

class Dog : public Animal
{
    public: 
    void speak ()
    {
        std::cout << "BARK \n";
    }
};

int main()
{
    Animal *A1;
    A1 = new Dog();
    A1->speak();

    return 0;   
}