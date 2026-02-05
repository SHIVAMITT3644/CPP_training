#include <iostream>
using namespace std;

class Human
{
public:
    void breathe()
    {
        cout << "Human is breathing" << endl;
    }
};

class Student : public Human
{
public:
    void study()
    {
        cout << "Student is studying" << endl;
    }
};

class Employee : public Human
{
public:
    void work()
    {
        cout << "Employee is working" << endl;
    }
};

int main()
{
    Student s;
    s.breathe();   // from Human
    s.study();     // from Student

    Employee e;
    e.breathe();   // from Human
    e.work();      // from Employee

    return 0;
}