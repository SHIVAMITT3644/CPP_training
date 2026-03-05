#include <iostream>

class Printer
{
public:
    template<typename T>
    void print(T value);   
};

template<typename T>
void Printer::print(T value)
{
    std::cout << value << std::endl;
}

int main()
{
    Printer p;

    p.print(10);
    p.print(3.14);
    p.print("Hello");
}