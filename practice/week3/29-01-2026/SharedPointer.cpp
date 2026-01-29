#include <iostream>
#include <memory>
 
int main()
{
    std::shared_ptr <int> p1;
    p1 = std::make_unique<int>(10);

    std::shared_ptr <int> p2;

    std::cout << p1.use_count() << '\n';

    p2 = p1;

    std::cout << p1.get() << '\n';
    std::cout << p2.get() << '\n';
    std::cout << p1.use_count() << '\n';
    std::cout << p2.use_count() << '\n';

    p1.reset();

    std::cout << p1.get() << '\n';
    std::cout << p2.get() << '\n';
    std::cout << p1.use_count() << '\n';
    std::cout << p2.use_count() << '\n';

    return 0;
}