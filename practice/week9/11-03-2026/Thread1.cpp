#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
typedef unsigned long long uLL;

uLL oddSum = 0;
uLL evenSum = 0;

void sumEven(uLL start, uLL even)
{
    for(uLL i = start; i < even ; i++)
    {
        if((i&1)==0)
        {
            evenSum += i;
        }
    }
}

void sumOdd(uLL start, uLL even)
{
    for(uLL i = start; i < even ; i++)
    {
        if((i&1)==1)
        {
            oddSum += i;
        }
    }
}

int main()
{
    uLL start = 0 , end = 19000000;
   
    auto startTime = std::chrono::high_resolution_clock::now();

    // sumEven(start,end);
    // sumOdd(start,end);

    thread t1(sumEven , start,end);
    thread t2(sumOdd , start,end);

    t2.join();
    t1.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "The Sum Of Odd is "  << oddSum << "\n";
    std::cout << "The Sum Of Even is "  << evenSum << "\n";
    std::cout << "Duration: " << duration.count() << " ms\n";
}

