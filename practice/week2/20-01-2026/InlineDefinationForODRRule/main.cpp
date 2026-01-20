#include <iostream>
#include "square.h"

int main() 
{  
    std::cout << "a square has " << square() << " sides\n";  
    std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n'; 
    return 0; 
}