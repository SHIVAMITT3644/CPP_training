#include <iostream>
#include <thread>

void printj(std::string message, int numberInde)
{
    for(int i = 1; i <= numberInde; i++)
    {
        std::cout << message << " " << i << "\n";
    }
}

int main()
{
    std::cout << "Start of Main j \n ";

    std::thread t1(printj, "Hello" , 5);    
    std::thread t2(printj, "Bye" , 5);
    t1.join();
    t2.join();
   
    std::cout << "End of Main j \n ";

    return 0;
}