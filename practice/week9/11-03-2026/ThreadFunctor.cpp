#include <iostream>
#include <thread>

class functor
{
    public:
    void operator ()(int x)
    {
        while(x-- > 0)
        {
            std::cout << x << " ";
        }
         std :: cout << "\n";
    }
};

int main()
{

    std::thread t1(functor() , 10);
    t1.join();

    return 0;
}