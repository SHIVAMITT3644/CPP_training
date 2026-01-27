#include <iostream>

int main()
{
    int intergerNumber = 10;
    int *intergerPointer = &intergerNumber;

    std::cout << "address that take by this Interger is from " << intergerPointer << "  to  " << intergerPointer + 1 << "\n";

    double doubleNumber = 10;
    double *doublePointer = &doubleNumber;

    std::cout << "address that take by this double is from " << doublePointer << "  to  " << doublePointer + 1 << std :: endl;

    std::cout << "size of pointer for int is " << sizeof(intergerPointer) << " and  for double is " << sizeof(doublePointer) << std :: endl;
 
    //printing each element of array

    int array[] = {1,2,3,4,5};
    int *pointer = array;

    std :: cout << "Array is : \n";

    for(int i = 0; i < 5; i++)
    {
        std :: cout << *(pointer + i)<<std::endl;
    }

    //character array
    char characterArray[5] = "ABCD";
    char name = 'S';
 
    //address of name 
    std :: cout << (void*)&name << '\n';

    //value of name
    std :: cout << name << '\n';


    //address of character array
    std :: cout << (void*)characterArray<<'\n';

    //value of character array
    std :: cout << characterArray << std :: endl;
    return 0;
}