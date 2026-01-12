#include <iostream>
#include <string>

using namespace std;

void greeting(string name)
{
    cout << "Hello" + name + "! How are you?" << endl;
} 

int add(int number1 , int number2)
{
    return number1 + number2;
}

void printAreaAndCircumference(float radius);

int subtract(int number1 , int number2);

void printPrimeNumberInRange(int number1 , int number2);

void defaultGreeting(string name = "shivam");

int main()
{
    greeting(" shivam pratap");

    cout << add(5 , 6) << endl;
    cout << subtract(5 , 6) << endl;
    
    printAreaAndCircumference(3);
    printPrimeNumberInRange(2,26);



    //default parameter function
    cout << "\ndefault Parameter function \n" ;
    
    defaultGreeting();
    defaultGreeting("Shivam Pratap");

    return 0;
}

int subtract(int number1 , int number2)
{
    return number1 - number2;
}

void printAreaAndCircumference(float radius)
{
    cout << "Area of circle having radius " << radius << " is " << 3.14 * radius * radius << endl;
    cout << "Circumference of circle having radius " << radius << " is " << 2 * 3.14 * radius << endl;

}

void printPrimeNumberInRange(int number1, int number2)
{
    int i , j , isPrime;

    cout << "Prime number between " << number1 << " to " << number2 << " is ";

    for(i = number1; i <= number2; i++)
    {
        if(i <= 1)continue;

        isPrime = 1;
        
        for(j = 2; j*j <=i; j++)
        {
            if(i%j == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if(isPrime)
        {
            cout << " " << i;
        }
    }

    cout << endl;
}

void defaultGreeting(string name)
{
    cout << "Hello " << name << endl ;
}