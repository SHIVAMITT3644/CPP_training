#include <iostream>

template<class T = int, class U = float>
class Data
{
    T value;
    U size;

public:
    Data(T v = 0, U s = 0) : value(v), size(s) {}

    void show()
    {
        std::cout << "Value: " << value << std::endl;
        std::cout << "Size: " << size << std::endl;
    }
};

int main()
{
    Data<char> d('C', 5.5);
    Data<> d1(10, 5.5);        
    Data<double, int> d2(3.2, 4);  

    d.show();
    std::cout << std::endl;
    d1.show();
    std::cout << std::endl;
    d2.show();
}