#include <iostream>
using namespace std;

int main()
{
    int age = 21;
    float height = 5.8f;
    double salary = 20000.75;
    char grade = 'A';
    bool passed = true;
    string name = "Shivam";
    wchar_t symbol = L'$';

    cout << "Name :" << name << endl;
    cout << "Age :" << age << endl;
    cout << "Height :" << height << endl;
    cout << "Salary :" << salary << endl;
    cout << "Grade :" << grade << endl;
    cout << "Passed :" << passed << endl;

    wcout << L"Wide character symbol:" << symbol << endl;

    return 0;
}