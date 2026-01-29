#include <iostream>
#include <memory>


int main()
{
    std::shared_ptr <int> p1;
    p1 = std::make_shared<int>(10);

    std::weak_ptr <int> p2 = p1;

    std::cout << *p1 << " " << *(p2.lock()) << "\n";
    std::cout << p1.use_count() << '\n';
    std::cout << p2.use_count() << '\n';

    p1.reset();

    std::cout << p1.use_count() << '\n';
    std::cout << p2.use_count() << '\n';
    std::cout << *p1 << " " << "\n";
    std::cout << *(p2.lock()) << "\n";

    return 0;
}