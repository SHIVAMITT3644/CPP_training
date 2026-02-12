#include <iostream>
using namespace std;

class Bonus;  

class Salary {
private:
    int basicSalary;

public:
    Salary(int s) {
        basicSalary = s;
    }

    friend void calculateTotal(Salary, Bonus);
};

class Bonus {
private:
    int bonusAmount;

public:
    Bonus(int b) {
        bonusAmount = b;
    }

    friend void calculateTotal(Salary, Bonus);
};


void calculateTotal(Salary s, Bonus b) {
    int totalIncome = s.basicSalary + b.bonusAmount;
    cout << "Total Income = " << totalIncome << endl;
}

int main() {
    Salary s1(30000);
    Bonus b1(5000);

    calculateTotal(s1, b1);

    return 0;
}