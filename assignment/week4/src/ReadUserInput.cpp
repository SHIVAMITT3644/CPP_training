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
    bool isInputValid = false;
    int validatedValue = 0;

    while (!isInputValid)
    {
        std::cout << inputMessage;

        readCompleteLineWithNoSkipWS(std::cin, rawInput);

        isInputValid = validateWholeNumber(rawInput, validatedValue);

        if (!isInputValid)
        {
            std::cout << "\nError: Please enter a valid whole number.\n";
        }
    }

    return validatedValue;
}

double ReadUserInput::readValidatedMatrixValue(int rowIndex, int columnIndex)
{
    bool isInputValid = false;
    double validatedValue = 0.0;

    while (!isInputValid)
    {
        std::cout << "Enter value for Position Matrix["  << rowIndex << "][" << columnIndex << "] : ";

        readCompleteLineWithNoSkipWS(std::cin, rawInput);

        isInputValid = validateDecimalNumber(rawInput, validatedValue);

        if (!isInputValid)
        {
            std::cout << "\nError: Please enter a valid numeric value.\n";
        }
    }

    return validatedValue;
}

int ReadUserInput::readMatrixOperationChoice()
{
    int matrixOperationChoice = 0;

    while (true)
    {
        matrixOperationChoice = readValidatedUserInput("Enter your choice for matrix operation : ");
        if (matrixOperationChoice == 1 || matrixOperationChoice == 2)
        {
            return matrixOperationChoice;
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

int ReadUserInput::readContinueProgramChoice()
{
    int userContinueProgramChoice = 0;

    while (true)
    {
        userContinueProgramChoice = readValidatedUserInput("\nEnter 1 to continue and Enter 0 to exit the program : ");
        if (userContinueProgramChoice == 0 || userContinueProgramChoice == 1)
        {
            return userContinueProgramChoice;
        }

        std::cout << "\nPlease Enter Valid Choice\n";
    }
}
