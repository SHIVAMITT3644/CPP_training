#include <iostream>
#include <limits>
#include <dlfcn.h>
#include <stdexcept>

typedef double (*MathFunction)(double, double);

MathFunction addition       = nullptr;
MathFunction subtraction    = nullptr;
MathFunction multiplication = nullptr;
MathFunction division       = nullptr;

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
        std::cout << "\nPlease enter your choice : ";

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
    std::cout << "Enter first operand  : ";
    readValidatedDouble(firstOperand);

    std::cout << "Enter second operand : ";
    readValidatedDouble(secondOperand);
}

double performAddition(double a, double b)
{
    return addition(a, b);
}

double performSubtraction(double a, double b)
{
    return subtraction(a, b);
}

double performMultiplication(double a, double b)
{
    return multiplication(a, b);
}

double performDivision(double a, double b)
{
    if (b == 0)
    {
        throw std::runtime_error("Division by zero");
    }
        
    return division(a, b);
}

void displayResult(double result, double a, double b, const std::string &operation)
{
    std::cout << "\n" << operation << " of "
              << a << " and " << b
              << " is " << result << "\n";
}

int main()
{
    void* handle = dlopen("./lib/libMathExplicit.so", RTLD_LAZY);

    if (!handle)
    {
        std::cerr << "Error loading library: " << dlerror() << "\n";
    }
    else
    {
        addition       = (MathFunction)dlsym(handle, "addition");
        subtraction    = (MathFunction)dlsym(handle, "subtraction");
        multiplication = (MathFunction)dlsym(handle, "multiplication");
        division       = (MathFunction)dlsym(handle, "division");

        if (!addition || !subtraction || !multiplication || !division)
        {
            std::cerr << "Error loading symbols\n";
            dlclose(handle);
        }
        else
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

            dlclose(handle);

            std::cout << "Thank you for using the program\n";
        }     

    }

    return 0;
}
