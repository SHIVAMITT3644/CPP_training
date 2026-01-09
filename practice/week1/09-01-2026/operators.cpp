#include <iostream>
using namespace std;

int main()
{
    int firstNumber = 7;
    int secondNumber = 5;

    //Arithmatic Operator
    cout << firstNumber + secondNumber << endl;
    cout << firstNumber - secondNumber << endl;
    cout << firstNumber / float(secondNumber) << endl;
    cout << firstNumber * secondNumber << endl;
    cout << firstNumber % secondNumber << endl;
    cout << firstNumber++ << endl;
    cout << firstNumber-- << endl;
    cout << firstNumber << endl << endl;

    //relational operator
    cout << (firstNumber < secondNumber) << endl;
    cout << (firstNumber > secondNumber) << endl;
    cout << (firstNumber <= secondNumber) << endl;
    cout << (firstNumber >= secondNumber) << endl;
    cout << (firstNumber == secondNumber) << endl;
    cout << (firstNumber != secondNumber) << endl << endl; 
    
    //logical operators
    bool expression1 = true;
    bool expression2 = false;
    bool expression3 = true;
    bool expression4 = false;

    cout << (expression1 && expression2) << endl;
    cout << (expression1 && expression3) << endl;
    cout << (expression1 || expression2) << endl;
    cout << (expression2 || expression4) << endl;
    cout << (!expression2) << endl;
    cout << (!expression1) << endl << endl;

    // assignment operator
    firstNumber = 11;

    cout << firstNumber <<endl;

    firstNumber += 5;
    secondNumber -= 2;

    cout << firstNumber << endl;
    cout << secondNumber << endl;

    firstNumber /= 4;
    secondNumber %=2 ;

    cout << firstNumber << endl;
    cout << secondNumber << endl << endl;

    //Bitwise operator
    int number1 = 11;

    cout << (number1 << 2) << endl;
    cout << (number1 >> 1) << endl;

    int number2 = 10;

    cout << (number1 & number2) << endl;
    cout << (number1 | number2) << endl;
    cout << (number1 ^ number2) << endl;
    cout << (~number1) << endl << endl;

    //Mislleneous operator
    int variable1 = 5;
    float varibale2 = 7.89;
    char firstLetterOfName = 'S';

    cout << "Size of variable1 = " << sizeof(variable1) << " Size of first letter of name = " << sizeof(firstLetterOfName) << endl;
    
    (5 == 4) ? variable1 = 7 : variable1 = 11;
    cout << "value of variable 1 = " << variable1 << endl;

    variable1 = 10,2,5;
    
    cout << "value of variable 1 = " << variable1 << endl;

    variable1 = (10,2,5);
    
    cout << "value of variable 1 = " << variable1 << endl;
    cout << "value of variable 2 after casting = " << (int)varibale2 << endl;

    cout << "Memory Address of variable 1 = " << (&variable1) << endl;

    return 0;
}