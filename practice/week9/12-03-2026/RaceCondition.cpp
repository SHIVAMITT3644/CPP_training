#include <thread>
#include <iostream>

int myAmount = 0;

void addAmount()
{
for(int i = 1; i<= 100000; i++)
    ++myAmount;
}

int main()
{
    std::thread tj(addAmount);
    std::thread tl(addAmount);

    tj.join();
    tl.join();

    std::cout << myAmount << "\n" ;

    return 0;
}