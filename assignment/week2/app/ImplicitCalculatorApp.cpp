#include <iostream>
#include <limits>
#include "MathLibrary.h"

void displayMenu()
{
    std::cout << "-----------------------------------------\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication\n";
    std::cout << "4. Division\n";
    std::cout << "5. Exit\n";
}

bool containsGarbageAfterInput()
{
    char bufferCharacter;

    while (std::cin.get(bufferCharacter) && bufferCharacter != '\n')
    {
        if (bufferCharacter != ' ' && bufferCharacter != '\t')
        {
            return true;
        }
    }

    return false;
}

void readValidatedInteger(int &userInputChoice)
{
    while (true)
    {
        std::cout << "\nplease enter your choice : ";

        if (!(std::cin >> userInputChoice) || containsGarbageAfterInput())
        {
            std::cout << "Error: Please enter a valid integer value only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        return;
    }
}

void readValidatedDouble(double &operandValue)
{
    while (true)
    {
        if (!(std::cin >> operandValue) || containsGarbageAfterInput())
        {
            std::cout << "Error: Please enter a valid number only.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        return;
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

int main()
{
    int userInputChoice;
    double result, firstOperand, secondOperand;

    do
    {
        displayMenu();
        readValidatedInteger(userInputChoice);

        if (userInputChoice >= 1 && userInputChoice <= 4)
        {
            readOperands(firstOperand, secondOperand);
        }

        switch (userInputChoice)
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
            try
            {
                result = performDivision(firstOperand, secondOperand);
                displayResult(result, firstOperand, secondOperand, "Division");
            }
            catch (const std::runtime_error &error)
            {
                std::cout << "\nError: " << error.what() << "\n";
            }
            break;

        case 5:
            std::cout << "\nExiting program...\n";  
            break;

        default:
            std::cout << "\nInvalid choice. Please try again.\n";
        }

    } while (userInputChoice != 5);

    std ::cout << "Thankyou for using the program\n";
    return 0;
}
