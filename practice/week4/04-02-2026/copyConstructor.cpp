#include <iostream>

class Student 
{
    public:
    int roll;
    float marks;

    Student ()
    {

    }

    Student (int roll , float marks)
    {
        this ->marks = marks;
        this->roll = roll;
    }

    Student (Student &S)
    {
        roll = S.roll;
        marks = 99;
    }

    void display()
    {
        std::cout << roll << " " << marks << " " << "\n";
    }
};

int main()
{
    
    Student S1(1,100);
    S1.display();
    
    Student S2(S1);
    S2.display();

    Student S3;
    S3 = S1;
    S3.display();

    Student S4(S1);
    S4.display();

    return 0;
}