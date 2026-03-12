#include <mutex>
#include <thread>
#include <iostream>

int myAmount = 0;
std::mutex k;

void addAmount()
{

    for (int i = 1; i <= 100000; i++)
    {

        if (k.try_lock())
        {
            ++myAmount;
            k.unlock();
        }
    }
}

int main()
{
    std::thread tj(addAmount);
    std::thread tl(addAmount);

    tj.join();
    tl.join();

    std::cout << myAmount << "\n";

    return 0;
}