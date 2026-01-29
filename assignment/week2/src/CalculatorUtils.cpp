#include <limits>
#include "CalculatorUtils.h"

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



void displayResult(double result, double firstOperand, double secondOperand, std ::string operation)
{
    std::cout << "\n" << operation << " of " << firstOperand << " and " << secondOperand << " is " << result << "\n";
}

bool isInputValid()
{
    bool inputValid = false;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Please enter a valid value only.\n";
    }
    else if (checkForGarbageAfterInput())
    {
        std::cout << "Error: Please enter a valid value only.\n";
    }
    else
    {
        inputValid = true;
    }
    
    return inputValid;
}

int readValidatedUserChoice()
{
    int userInputChoice;

    while (true)
    {
        std::cout << "\nPlease enter your choice : ";

        std::cin >> userInputChoice;

        if(isInputValid())
        {
            break;
        }
    }

    return userInputChoice;
}

double readValidatedOperand()
{
    double operandValue;

    while (true)
    {
        std::cin >> operandValue;

        if(isInputValid())
        {
            break;
        }
    }

    return operandValue;
}