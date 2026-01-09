#include <iostream>
using namespace std;

//these are micro constant
#define MAX_STUDENT 50
#define PI 3.14159

// this is enum constant
enum Day
{
    MONDAY,TUESDAY,WEDNESDAY,THRUSDAY,FRIDAY,SATURDAY,SUNDAY
};

int main()
{
    //CONST KEYWORD CONSTANTS
    const int maxAge = 101;
    const float taxRate = 0.1f;

    //this is variable and also a literal constant
    int age = 10;
    string name = "shivam pratap";

    cout << "Max Student: " << MAX_STUDENT << endl;
    cout << "enum day: " << THRUSDAY << endl;
    cout << "Max Age of Students: " << maxAge << endl;
    cout << "Tax Rate: " << taxRate << endl;
    cout << "Name: " << name << endl;
    cout << "Age Of Student: " << age << endl;
    
}