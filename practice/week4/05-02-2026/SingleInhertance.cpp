#include <iostream>

class human
{
    public:
    std::string name  = "shin";

    void print()
    {
        std::cout << name;
    }

    human()
    {
        std::cout << "Human Constructor called \n"; 
    }

    ~human()
    {
        std::cout << "Human Destructor called \n"; 
    }
};

class person : public human
{
    public:
    int age = 1 ;

    void print()
    {
        std::cout << age << " " << name <<"\n";
    }

    person()
    {
        std::cout << "person Constructor called \n"; 
    }

    ~person()
    {
        std::cout << "person Destructor called \n"; 
    }
};

int main()
{
    human p1;
    p1.print();
}
