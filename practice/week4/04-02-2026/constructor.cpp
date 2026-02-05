#include <iostream>

class Customer
{
    public:
    std::string name;
    int acc_number , balance;

    Customer ()
    {
        std::cout << "Constructor Called";
    }

    Customer(std::string name , int acc_number , int balance)
    {
        this -> name = name;
        this -> acc_number = acc_number;
        this -> balance = balance;

        std :: cout << "\n1st parameterized constructor is called \n";
    }

    Customer (int acc_number,std::string name  , int balance)
    {
        this -> name = name;
        this -> acc_number = acc_number;
        this -> balance = balance;

        std :: cout << "\n2nd parameterized constructor is called \n";
    }

    inline Customer(int acc_number , int balance , std::string name) : acc_number(acc_number) , balance(balance){
        this -> name = name;
        std :: cout << "\n3rd parameterized constructor is called \n";
    }
};

int main()
{
    Customer C1;

    Customer C2("1st",900,33);

    std::cout << C2.name << " " << C2.acc_number << " " << C2.balance << " ";

    Customer C3(900, 33,"3rd");

    std::cout << C3.name << " " << C3.acc_number << " " << C3.balance << " ";

    Customer C4(900,"2nd" , 78);

    std::cout << C4.name << " " << C4.acc_number << " " << C4.balance << " ";

}