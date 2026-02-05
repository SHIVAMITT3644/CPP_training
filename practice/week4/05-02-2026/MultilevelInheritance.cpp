#include <iostream>

class Human
{
        public:
    std::string name;
    int age;

    Human(std::string name, int age)
    {
        this->name = name;
        this->age = age;
    }

    void print()
    {
        std::cout << name << " " << age << "\n";
    }
};

class Employee : public Human
{
    public:
    float salary;
    
    Employee (std:: string name , float salary , int age) : Human(name , age)
    {
        this->salary = salary;
    }

    void print()
    {
        std::cout << name << " " << age << " " << salary << "\n";
    }
};

class Manager : public Employee
{
    public:    
    int no_of_employee;

    Manager (int no_of_employee , std:: string name , float salary , int age) :  Employee(name, salary, age)
    {
        this->no_of_employee = no_of_employee;
    }

    void print()
    {
        std::cout << name << " " << age << " " << salary << " " << no_of_employee <<  "\n";
    }
};

int main()
{
    Manager m1(200, "shivam" , 90000 , 21);
    m1.print();

    return 0;
}