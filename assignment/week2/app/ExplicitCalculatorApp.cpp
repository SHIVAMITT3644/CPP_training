#include <iostream>
#include <limits>
#include <dlfcn.h>

const char LIBRARY_PATH[] = "./lib/libMathExplicit.so";
typedef double (*MathFunction)(double, double);

MathFunction addition       = nullptr;
MathFunction subtraction    = nullptr;
MathFunction multiplication = nullptr;
MathFunction division       = nullptr;

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
    return division(a, b);
}

void displayResult(double result, double a, double b, const std::string &operation)
{
    std::cout << "\n" << operation << " of "
              << a << " and " << b
              << " is " << result << "\n";
}

void runCalculatorOperation(int userInputChoice, double firstOperand, double secondOperand)
{
    double result;

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
            readValidatedInteger(userInputChoice);

            if (userInputChoice >= 1 && userInputChoice <= 4)
            {
                readOperands(firstOperand, secondOperand);
            }

            runCalculatorOperation(userInputChoice, firstOperand, secondOperand);

        } while (userInputChoice != 5);

        dlclose(handle);
    }

    std::cout << "Thank you for using the program\n";
    return 0;
}
