#include <iostream>

template <class T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    std::cout << add<int>(3, 4) << std::endl;
    std::cout << add<float>(3.5, 2.1) << std::endl;
}