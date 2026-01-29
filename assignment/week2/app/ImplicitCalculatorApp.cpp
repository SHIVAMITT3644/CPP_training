#include <iostream>
#include <limits>
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"

void displayCalculatorMenu()
{
    std::cout << "-----------------------------------------\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication\n";
    std::cout << "4. Division\n";
    std::cout << "5. Exit\n";
}

bool checkForGarbageAfterInput()
{
    char bufferCharacter;
    bool hasGarbage = false;

    while (std::cin.get(bufferCharacter) && bufferCharacter != '\n')
    {
        if (bufferCharacter != ' ' && bufferCharacter != '\t')
        {
            hasGarbage = true; 
        }
    }

    return hasGarbage;
}

void readValidatedInteger(int &userInputChoice)
{
    bool inputValid = false;

    while (!inputValid)
    {
        std::cout << "\nPlease enter your choice : ";

        std::cin >> userInputChoice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Please enter a valid integer value only.\n";
        }
        else if (checkForGarbageAfterInput())
        {
            std::cout << "Error: Please enter a valid integer value only.\n";
        }
        else
        {

            inputValid = true;
        }
    }
}

void readValidatedDouble(double &operandValue)
{
    bool inputValid = false;

    while (!inputValid)
    {
        std::cin >> operandValue;

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Please enter a valid number only.\n";
        }
        else if (checkForGarbageAfterInput())
        {
            std::cout << "Error: Please enter a valid number only.\n";
        }
        else
        {
            inputValid = true;
        }
    }
}

void readOperands(double &firstOperand, double &secondOperand)
{
    std ::cout << "Enter first Operand : ";
    readValidatedDouble(firstOperand);

    std ::cout << "Enter second Operand : ";
    readValidatedDouble(secondOperand);
}

double performAddition(double firstOperand, double secondOperand)
{
    return addition(firstOperand, secondOperand);
}

double performSubtraction(double firstOperand, double secondOperand)
{
    return subtraction(firstOperand, secondOperand);
}

double performMultiplication(double firstOperand, double secondOperand)
{
    return multiplication(firstOperand, secondOperand);
}

double performDivision(double firstOperand, double secondOperand)
{
    return division(firstOperand, secondOperand);
}

void displayResult(double result, double firstOperand, double secondOperand, std ::string operation)
{
    std::cout << "\n"
              << operation << " of " << firstOperand << " and " << secondOperand << " is " << result << "\n";
}

void runCalculatorOperation(int choice, double firstOperand, double secondOperand)
{
    double result;

    switch (choice)
    {
        case 1:
            result = performAddition(firstOperand, secondOperand);
            displayResult(result, firstOperand, secondOperand, "Addition");
            break;

        case 2:
            result = performSubtraction(firstOperand, secondOperand);
            displayResult(result, firstOperand, secondOperand, "Subtraction");
            break;

        case 3:
            result = performMultiplication(firstOperand, secondOperand);
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
        readValidatedInteger(userInputChoice);

        if (userInputChoice >= 1 && userInputChoice <= 4)
        {
            readOperands(firstOperand, secondOperand);
        }

        runCalculatorOperation(userInputChoice, firstOperand, secondOperand);

    } while (userInputChoice != 5);

    std::cout << "Thank you for using the program\n";
    return 0;
}
