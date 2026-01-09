#include <iostream>
using namespace std;

int main()
{
    int age;
    
    cout << "Please enter your age" << endl;
    cin >> age;

    // if else statement 
    if(age <= 0)
    {
        cout << "Please enter valid age" << endl; 
    }
    else if(age > 0 && age < 12)
    {
        cout << "child" << endl;
    }
    else if(age >= 12 && age < 18)
    {
        cout << "teenager" << endl;
    }
    else
    {
        cout << "Adult" << endl;
    }

    //Nested If-else statement

    int marks; 

    cout << "Enter your Marks" << endl;
    cin >> marks;

    if(marks >= 33)
    {
        if(marks >= 33 && marks <=70)
        {
            cout << "Pass" << endl;
        }
        else
        {
            cout << "gracefully Pass" << endl;
        }
    }
    else
    {
        cout << "Fail" << endl;
    }

    // switch statement
    int weekDayNumber;
    
    cout << "Enter week day Number : ";
    cin >> weekDayNumber;

    switch(weekDayNumber)
    {
        case 1:
               cout << "Monday" << endl;
               break;
        case 2:
               cout << "Tuesday" << endl;
               break;
             
        case 3:
               cout << "Wednesday" << endl;
               break;               
        case 4:
               cout << "Thrusday" << endl;
               break;
        case 5:
               cout << "Friday" << endl;
               break;
        case 6:
               cout << "Saturday" << endl;
               break;
        case 7:
               cout << "Sunday" << endl;
               break;
        default:
               cout << "Invalid week day's" << endl;
               break;
                                                                                                              
    }
}