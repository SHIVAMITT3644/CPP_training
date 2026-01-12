#include <iostream>
using namespace std;

void swapByValue(int number1, int number2)
{
    int temperory;

    temperory = number1;
    number1 = number2;
    number2 = temperory;
}

void swapByReference2(int *number1, int *number2)
{
    int temperory;

    temperory = *number1;
    *number1 = *number2;
    *number2 = temperory;
}

void swapByReference1(int &number1, int &number2)
{
    int temperory;

    temperory = number1;
    number1 = number2;
    number2 = temperory;
}

int main()
{
    int number1 = 11 , number2 = 5;

    cout << "-> Call By Value \n";
    cout << " value of number1 and number2 before swap : "<< number1 << " " << number2 << endl;

    swapByValue(number1 , number2);
    cout << " value of number1 and number2 After swap : "<< number1 << " " << number2 << endl << endl;

    cout << "-> Call By Reference" << endl;
    cout << " value of number1 and number2 before swap : "<< number1 << " " << number2 << endl;

    swapByReference1(number1 , number2);
    cout << " value of number1 and number2 After swap : "<< number1 << " " << number2 << endl << endl;

    cout << "-> Second Method" << "\n";
    swapByReference2(&number1 , &number2);
    cout << " value of number1 and number2 After swap : "<< number1 << " " << number2 << endl;

}