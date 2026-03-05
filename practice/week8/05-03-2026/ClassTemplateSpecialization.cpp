#include <iostream>

template<typename T>
class Printer
{
public:
    void print(T value)
    {
        std::cout << "General template: " << value << std::endl;
    }
};

template<>
class Printer<char>
{
public:
    void print(char value)
    {
        std::cout << "Specialized for char: " << value << std::endl;
    }
};

int main()
{
    Printer<int> p1;
    Printer<char> p2;

    p1.print(10);
    p2.print('A');
}
