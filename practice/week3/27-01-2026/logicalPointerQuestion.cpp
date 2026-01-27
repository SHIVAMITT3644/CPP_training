#include <iostream>

void secondProblem(int *pointer1 , int *pointer2)
{
    pointer1 = pointer2;
    *pointer1 = 2;
}

void thirdProblem()
{
    int *pointer1;
    int x = 0;
    pointer1 = &x;
    int y = *pointer1;
    *pointer1 = 1;

    std :: cout << x << " " << y << "\n";
}

void forthProblem()
{
    int a = 5,b = 10;
    int &name = a;
    int *pointer1 = &a;
    (*pointer1)++;
    pointer1 = &b;
    *pointer1 = *pointer1 + 5;
    name += 5;

    std :: cout << a << " " << b << "\n";
}

int fifthProblem(int x , int *py , int **ppz)
{
    int y,z;
    **ppz += 1;
    z = **ppz;
    *py += 2;
    y = *py;
    x +=3;

    return x + y + z;;
}

int main()
{
    char characterArray[8] = "ITT2026";
    char *characterPointer = characterArray;

    std :: cout << characterArray + 4 - 1 << "\n";

    int i = 0 , j = 1;
    secondProblem(&i , &j);
    std :: cout << i << " " << j << "\n";

    thirdProblem();
    forthProblem();

    int c , *b , **a;
    c = 4;
    b = &c;
    a = &b;
    
    std :: cout << fifthProblem(c,b,a) << "\n" ;

    return 0;
}