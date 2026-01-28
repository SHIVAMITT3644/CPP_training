#include <iostream>

int main()
{
    short bombs { 1 }; 

    const int& you { bombs };  
    --bombs;                   

    if (you)                   
    {
        std::cout << "Bombs away!  Goodbye, cruel world.\n"; 
    }

    return 0;
}