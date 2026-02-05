#include <iostream>

class Customer
{
    private :
     static int total_customer;
    public:
    std::string name;
    int acc_number , balance;
   

    Customer(std::string name , int acc_number , int balance)
    {
        this -> name = name;
        this -> acc_number = acc_number;
        this -> balance = balance;
        total_customer ++;
    }
    
    static void display()
    {
        std::cout << total_customer  << "\n";
    }

};

int Customer :: total_customer = 0;

int main()
{
    Customer C1("1st",900,33);
    std::cout << C1.name << " " << C1.acc_number << " " << C1.balance << " " << "\n";
    C1.display();

    Customer C2("1st",900,33);
    std::cout << C2.name << " " << C2.acc_number << " " << C2.balance << " " << "\n";

    Customer :: display() ;
    return 0;

}