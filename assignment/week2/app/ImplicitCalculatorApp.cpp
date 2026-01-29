#include <iostream>
#include "Addition.h"
#include "Multiplication.h"
#include "Subtraction.h"
#include "Division.h"
#include "CalculatorUtils.h"

void runCalculatorOperation(int choice, double firstOperand, double secondOperand)
{
    double result;

    switch (choice)
    {
        case 1:
            result = addition(firstOperand, secondOperand);
            displayResult(result, firstOperand, secondOperand, "Addition");
            break;

        case 2:
            result = subtraction(firstOperand, secondOperand);
            displayResult(result, firstOperand, secondOperand, "Subtraction");
            break;

        case 3:
            result = multiplication(firstOperand, secondOperand);
            displayResult(result, firstOperand, secondOperand, "Multiplication");
            break;

        case 4:
            if (secondOperand == 0.0)
            {
                std::cout << "\nError: Division by zero is not allowed.\n";
            }
            else
            {
                result = division(firstOperand, secondOperand);
                displayResult(result, firstOperand, secondOperand, "Division");
            }
            break;

        case 5:
            std::cout << "\nExiting program...\n";
            break; 

        default:
            std::cout << "\nInvalid choice. Please try again.\n";
    }
}


int main()
{
    int userInputChoice;
    double firstOperand, secondOperand;

    do
    {
        displayCalculatorMenu();

        userInputChoice = readValidatedUserChoice();

        if (userInputChoice >= 1 && userInputChoice <= 4)
        {
            std ::cout << "Enter first Operand : ";
            firstOperand = readValidatedOperand();

            std ::cout << "Enter second Operand : ";
            secondOperand = readValidatedOperand();   
        }

        runCalculatorOperation(userInputChoice, firstOperand, secondOperand);

    } while (userInputChoice != 5);

    std::cout << "Thank you for using the program\n";
    return 0;
}
