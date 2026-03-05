#include <iostream>

template<typename T>
void show(T value)
{
    std::cout << "General: " << value << std::endl;
}

template<>
void show<char>(char value)
{
    std::cout << "Character: " << value << std::endl;
}

int main()
{
    show(10);
    show('A');
}