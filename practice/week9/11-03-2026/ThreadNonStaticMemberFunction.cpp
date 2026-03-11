#include <iostream>
#include <thread>

class functor
{
    public:
    void print(int x)
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
    functor f1;

    std::thread t1( &functor::print, & f1 ,10);
    t1.join();

    return 0;
}