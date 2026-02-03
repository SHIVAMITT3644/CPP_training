#include <iostream>

class Student
{
private:
    int rollNo;
    bool rollSet{false};

public:
    bool setRoll(int roll)
    {
        if (roll < 100)
            return false;

        rollNo = roll;
        rollSet = true;
        return true;
    }

    void getRoll(int outRoll)
    {
        if (!rollSet)
        {
            std::cout << "Roll not set yet\n";
        }
        else
        {
            std::cout << "Roll No = " << rollNo;
        }
    }
};
int main()
{
    Student s1;
    int r;

    if (!s1.setRoll(11))
    {
        std::cout << "Invalid roll\n";
    }

    s1.getRoll(r);

    return 0;
}