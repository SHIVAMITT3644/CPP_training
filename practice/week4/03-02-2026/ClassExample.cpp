#include <iostream>

class Student
{
//    public: 
    int rollNo , age;
    std::string name , grade ;

    //if member of class is private then how to acces of class member

    public:
    void setName(std::string na)
    {
        name = na;
    }

    void getName()
    {
        std :: cout << name;
    }

    void setRoll(int roll)
    {
        if(roll <100)
        return;
        rollNo = roll;
    }

    void getRoll()
    {
        std :: cout << rollNo;
    }

};

int main()
{
    Student s1 , s2;
    // s1.name = "shivam";
    // s1.age = 21;
    // s1.rollNo = 132;
    // s1.grade = "A++";

    // s2.name = "satvik";
    // s2.age = 34;
    // s2.rollNo = 198;
    // s2.grade = "A+++";

    // std :: cout << s1.name << " " << s1.age << " " << s1.rollNo << " " << s1.grade;
    // std :: cout << "\n" << s2.name << " " << s2.age << " " << s2.rollNo << " " << s2.grade << "\n";

    // s1.setName("shivam");
    // s1.getName();
    s1.setRoll(11);
    s1.getRoll();

    return 0;
}