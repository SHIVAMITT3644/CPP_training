#include <iostream>
#include "CalculatorUtils.h"
#include <limits>
#include <dlfcn.h>

const char LIBRARY_PATH[] = "./lib/libMathExplicit.so";
typedef double (*MathFunction)(double, double);

MathFunction addition       = nullptr;
MathFunction subtraction    = nullptr;
MathFunction multiplication = nullptr;
MathFunction division       = nullptr;

void runCalculatorOperation(int userInputChoice, double firstOperand, double secondOperand)
{
    double result;

    switch (userInputChoice)
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

bool loadMathLibrary(void* &handle)
{
    bool libraryLoaded = false; 

    handle = dlopen(LIBRARY_PATH, RTLD_LAZY);

    if (handle)
    {
        addition       = (MathFunction)dlsym(handle, "addition");
        subtraction    = (MathFunction)dlsym(handle, "subtraction");
        multiplication = (MathFunction)dlsym(handle, "multiplication");
        division       = (MathFunction)dlsym(handle, "division");

        if (addition && subtraction && multiplication && division)
        {
            libraryLoaded = true;
        }
        else
        {
            std::cerr << "Error loading symbols from library.\n";
            dlclose(handle); 
        }
    }
    else
    {
        std::cerr << "Error loading library: " << dlerror() << "\n";
    }

    return libraryLoaded;
}

int main()
{
    void* handle = nullptr;

    if (!loadMathLibrary(handle)) 
    {
        std::cout << "Library could not be loaded. Exiting program.\n";
    }
    else
    {
        int userInputChoice;
        double firstOperand, secondOperand ;

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

        dlclose(handle);
    }

    std::cout << "Thank you for using the program\n";
    return 0;
}
