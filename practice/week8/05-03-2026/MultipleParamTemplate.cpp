#include <iostream>

template<class T, class T1>

class MyClass
{
    public:
    T data1;
    T1 data2;

    MyClass(T data1 , T1 data2)
    {
        this->data1 = data1;
        this->data2 = data2;
    }

    void print()
    {
        std::cout << data1 << " " << data2 << std::endl;
    }
};

int main()
{
    MyClass <int,float> MyObj(1,2.9);
    MyClass <char,char> MyObj1('N','S');

    MyObj.print();
    MyObj1.print();
}