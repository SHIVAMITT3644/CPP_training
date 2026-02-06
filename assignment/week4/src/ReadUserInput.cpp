#include "ReadUserInput.h"

void ReadUserInput::readCompleteLineWithNoSkipWS(std::istream& inputStream, std::string& output)
{
    output.clear();
    inputStream >> std::noskipws;

    char currentCharacter;

    while (inputStream >> currentCharacter)
    {
        if (currentCharacter == '\n')
        {
            break;
        }

        output.push_back(currentCharacter);
    }

    inputStream >> std::skipws;
}

int ReadUserInput::readValidatedUserInput(const std::string& inputMessage)
{
    bool isValid = false;
    int validatedValue = 0;

    while (!isValid)
    {
        std::cout << inputMessage;

        readCompleteLineWithNoSkipWS(std::cin, rawInput);

        isValid = validateWholeNumber(rawInput, validatedValue);

        if (!isValid)
        {
            std::cout << "\nError: Please enter a valid whole number.\n";
        }
    }

    return validatedValue;
}

double ReadUserInput::readValidatedMatrixValue(int rowIndex, int columnIndex)
{
    bool isValid = false;
    double validatedValue = 0.0;

    while (!isValid)
    {
        std::cout << "Enter value for Position Matrix["  << rowIndex << "][" << columnIndex << "] : ";

        readCompleteLineWithNoSkipWS(std::cin, rawInput);

        isValid = validateDecimalNumber(rawInput, validatedValue);

        if (!isValid)
        {
            std::cout << "\nError: Please enter a valid numeric value.\n";
        }
    }

    return validatedValue;
}

int ReadUserInput::readMatrixOperationChoice()
{
    int userChoice = 0;

    while (true)
    {
        userChoice = readValidatedUserInput("Enter your choice for matrix operation : ");

        if (userChoice == 1 || userChoice == 2)
        {
            return userChoice;
        }

        std::cout << "\nPlease Enter Valid Choice\n";
    }
}

int ReadUserInput::readValidMatrixDimensionLength(const std::string& message)
{
    int dimensionValue = 0;

    while (true)
    {
        dimensionValue = readValidatedUserInput(message);

        if (dimensionValue > 0)
        {
            return dimensionValue;
        }

        std::cout << "\nError: Matrix dimensions must be greater than zero.\n";
    }
}

void ReadUserInput::readMatrixDimension(int& rowLength, int& columnLength, const std::string& rowMessage, const std::string& columnMessage)
{
    rowLength = readValidMatrixDimensionLength(rowMessage);
    columnLength = readValidMatrixDimensionLength(columnMessage);
}

int ReadUserInput::readUserChoice()
{
    int userChoice = 0;

    while (true)
    {
        userChoice = readValidatedUserInput("\nEnter 1 to continue and Enter 0 to exit the program : ");

        if (userChoice == 0 || userChoice == 1)
        {
            return userChoice;
        }

        std::cout << "\nPlease Enter Valid Choice\n";
    }
}
