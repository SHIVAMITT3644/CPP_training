#include <iostream>
#include <memory>

void uniquePtrFunction()
{
    //std::unique_ptr<int> p(new int(10));
    // auto p1 = std::make_unique<int>(10);
    std::unique_ptr<int> p1;
    p1.reset(new int);
    *p1 = 10;
    std::cout << *p1 <<"\n";

    std::unique_ptr<int> p2;
    p2 = move(p1);

    if(p1 == nullptr)
    {
        std::cout << "Ownership given to p2\n";
    }

    std::cout << *p2 << "\n";

    int *rawPointer = p2.get();
    *rawPointer = 20;
    std::cout << "Now the value of p2 is " << *p2 << '\n';
}

int main()
{
    uniquePtrFunction();
}