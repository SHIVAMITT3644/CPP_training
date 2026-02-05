#include <iostream>

class Student
{
    int money;

    public:
    Student(int mooney)
    {
        this->money = mooney;
    }

    void giveMoney(int amount, Student &student)
{
    if (amount > 0)
    {
        if (this->money >= amount)
        {
            this->money -= amount;
            student.money += amount;
        }
        else
        {
            std::cout << "Not enough balance\n";
        }
    }
    else
    {
        std::cout << "Invalid amount\n";
    }
}

    void showMoney()
    {
        std::cout << money << "\n";
    }
};

int main()
{
    Student shivam(100), nikita(500);

    // how give and showw money is working internally we need not to worry fro that
    shivam.showMoney();
    nikita.showMoney();

    nikita.giveMoney(200, shivam);
    shivam.showMoney();
    nikita.showMoney();

    nikita.giveMoney(-200, shivam);

    shivam.giveMoney(700, nikita);
    shivam.showMoney();
    nikita.showMoney();

    shivam.giveMoney(300, nikita);
    shivam.showMoney();
    nikita.showMoney();

    return 0;
}