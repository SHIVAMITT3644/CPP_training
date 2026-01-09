#include <iostream>


namespace myspace 
{
    void hello() 
    {
        std::cout << "Hello from namespace!" << std::endl;
    }
}

using namespace myspace;

int main() 
{
    hello();

    return 0;
}
