#include <iostream>

int& getRef()
{
    int x = 10;   
    return x;     
}

int main()
{
    int& ref = getRef();  
    std::cout << ref;    
}
