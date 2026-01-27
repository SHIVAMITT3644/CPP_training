#include <iostream>

void multiplyByTwo(int (&ptr)[3])
{
    for(int i = 0; i <=2 ;i++)
    {
        ptr[i] = ptr[i] * 2;
    }
}

int main()
{
    int number = 10;
    int &referenceVariable = number;

    //Reference variable is alias of number var
    std :: cout << referenceVariable << std::endl;
    std :: cout << number << std::endl;

    referenceVariable = referenceVariable + 1;
    std :: cout << referenceVariable << std::endl;
    std :: cout << number << std::endl;

    std :: cout << "Address of both " << std::endl;
    std :: cout << &number << std::endl;
    std :: cout << &referenceVariable << std::endl;

    int arr[3] = {5,11,7};

    multiplyByTwo(arr);

    std :: cout << "Array is ";

    for(int i = 0; i <=2 ;i++)
    {
        std :: cout << arr[i] << " ";
    }

    return 0;
}