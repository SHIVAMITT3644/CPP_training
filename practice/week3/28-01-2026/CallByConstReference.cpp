#include <iostream>

void printRef(const int& y)
{
    std::cout << y << '\n';
    //++ref;  not allowed: ref is const
}

int main()
{
    int x { 5 };
    printRef(x);

    const int z { 5 };
    printRef(z);

    printRef(5);

    return 0;
}