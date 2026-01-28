#include <iostream>

int main()
{
    int *pointer1 = new int;
    *pointer1 = 11;

    std::cout << "Address of dynamically allocated memory is " << pointer1 << "\n";
    std::cout << "value of dynamically allocated memory is " << *pointer1 << "\n";

    int size;
    std::cout << "Enter the size of an array" <<'\n';
    std::cin >> size;

    int *array = new int[size];

    //assign value
    for(int i = 0 ; i < size ; i++)
    {
        *(array + i) = i+1;
    }

    //print value
    for(int i = 0 ; i < size ; i++)
    {
        std::cout << " " << *(array + i);
    }
    std::cout << "\n";

    delete pointer1;
    delete[] array;

    return 0;
}