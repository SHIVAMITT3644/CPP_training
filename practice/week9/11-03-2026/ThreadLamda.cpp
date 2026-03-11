#include <iostream>
#include <thread>

int main()
{
    auto funck = [](int x)
    {
        while(x-- > 0)
        {
            std::cout << x << " ";
        }
         std :: cout << "\n";
    };

    std::thread t1(funck , 10);
    t1.join();

    return 0;
}