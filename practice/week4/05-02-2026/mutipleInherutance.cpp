#include <iostream>
using namespace std;

class Person
{
public:
    string name;

    Person(string name)
    {
        this->name = name;
    }
};

class Employee
{
public:
    int salary;

    Employee(int salary)
    {
        this->salary = salary;
    }
};

class Manager : public Person, public Employee
{
public:
    Manager(string name, int salary)
        : Person(name), Employee(salary)
    {
    }

    void show()
    {
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};

int main()
{
    Manager m("Shivam", 90000);
    m.show();

    return 0;
}
