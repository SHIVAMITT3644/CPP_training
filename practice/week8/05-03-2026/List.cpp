#include <iostream>
#include <list>

int main()
{
    std::list<int> numbers;

    // push_back
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // push_front
    numbers.push_front(5);

    std::cout << "Initial list: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // front and back
    std::cout << "Front: " << numbers.front() << std::endl;
    std::cout << "Back: " << numbers.back() << std::endl;

    // insert
    auto it = numbers.begin();
    ++it;
    numbers.insert(it, 15);

    std::cout << "After insert: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // erase
    it = numbers.begin();
    // it = std::next(it,1);
    numbers.erase(it);

    std::cout << "After erase first element: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // remove
    numbers.remove(20);

    std::cout << "After remove 20: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // size
    std::cout << "Size: " << numbers.size() << std::endl;

    // sort
    numbers.push_back(1);
    numbers.push_back(50);
    numbers.sort();

    std::cout << "After sort: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // reverse
    numbers.reverse();

    std::cout << "After reverse: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // pop_back
    numbers.pop_back();

    // pop_front
    numbers.pop_front();

    std::cout << "After pop operations: ";
    for(int n : numbers)
        std::cout << n << " ";
    std::cout << std::endl;

    // empty
    std::cout << "Is list empty? " << numbers.empty() << std::endl;

    // clear
    numbers.clear();

    std::cout << "After clear, size: " << numbers.size() << std::endl;

    return 0;
}