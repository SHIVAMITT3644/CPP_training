#include <iostream>

class Customer
{
    public:
    std::string name;
    int acc_number ;
    int *balance;

    Customer(std::string name , int acc_number , int balance)
    {
        this -> name = name;
        this -> acc_number = acc_number;
        this->balance = new int;
        *this->balance = balance;
    }

    ~Customer()
    {
        delete balance;
    }

};

int main()
{
    Customer C2("1st",900,33);
    return 0;

}