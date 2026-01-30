#include <iostream>
#include <limits>

bool hasExtraCharactersInInput()
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

bool isInputValid()
{
    bool inputValid = false;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nError: Please enter a valid value only.\n";
    }
    else if (hasExtraCharactersInInput())
    {
        std::cout << "\nError: Please enter a valid value only.\n";
    }
    else
    {
        inputValid = true;
    }

    return inputValid;
}

int readValidatedUserInput()
{
    int userInput;

    while (true)
    {
        std::cin >> userInput;

        if (isInputValid())
        {
            break;
        }
    }

    return userInput;
}

double readValidatedMatrixValue(int rowIndex, int columnIndex)
{
    double matrixValue;

    while (true)
    {
        std::cout << "Enter value for Position Matrix[" << rowIndex << "][" << columnIndex << "] : ";
        std::cin >> matrixValue;

        if (isInputValid())
        {
            break;
        }
    }

    return matrixValue;
}

int readUserChoice()
{
    int userInputChoice;

    while (true)
    {
        std::cout << "\nEnter 1 to continue and Enter 0 to exit the program : ";
        userInputChoice = readValidatedUserInput();

        if (userInputChoice != 1 && userInputChoice != 0)
        {
            std::cout << "\nPlease Enter Valid Choice";
            continue;
        }

        break;
    }

    return userInputChoice;
}

double **allocateMemoryForMatrix(int rowLength, int columnLength)
{
    double **matrix = new double *[rowLength];

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        *(matrix + rowIndex) = new double[columnLength];
    }

    return matrix;
}

void deleteMemoryOfMatrix(double **matrix, int rowLength)
{
    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        delete[] *(matrix + rowIndex);
    }

    delete[] matrix;
}

void readMatrixFromUser(double **matrix, int rowLength, int columnLength)
{
    std::cout << "\nPlease enter your matrix\n";

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columnLength; columnIndex++)
        {
            *(*(matrix + rowIndex) + columnIndex) = readValidatedMatrixValue(rowIndex, columnIndex);
        }
    }
}

void displayMatrix(double **matrix, int rowLength, int columnLength, const std::string &message)
{
    std::cout << "\nMatrix " << message << " Result:\n\n";
    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columnLength; columnIndex++)
        {
            std::cout << *(*(matrix + rowIndex) + columnIndex) << " ";
        }
        std::cout << "\n";
    }
}

void performMatrixAddition(double **firstMatrix, double **secondMatrix, double **sumMatrix, int rowLength, int columnLength)
{
    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columnLength; columnIndex++)
        {
            *(*(sumMatrix + rowIndex) + columnIndex) = *(*(firstMatrix + rowIndex) + columnIndex) + *(*(secondMatrix + rowIndex) + columnIndex);
        }
    }
}

void performMatrixMultiplication(double **firstMatrix, double **secondMatrix, double **multiplicationMatrix,
                                 int firstMatrixRowLength, int firstMatrixColumnLength, int secondMatrixColumnLength)
{
    for (int rowIndex = 0; rowIndex < firstMatrixRowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < secondMatrixColumnLength; columnIndex++)
        {
            *(*(multiplicationMatrix + rowIndex) + columnIndex) = 0;

            for (int innerIndex = 0; innerIndex < firstMatrixColumnLength; innerIndex++)
            {
                *(*(multiplicationMatrix + rowIndex) + columnIndex) += (*(*(firstMatrix + rowIndex) + innerIndex)) * (*(*(secondMatrix + innerIndex) + columnIndex));
            }
        }
    }
}

bool areMatrixAdditionPossible(int firstMatrixRowLength, int secondMatrixRowLength, int firstMatrixColumnLength, int secondMatrixColumnLength)
{
    bool isAdditionPossible = true;

    if (firstMatrixRowLength != secondMatrixRowLength || firstMatrixColumnLength != secondMatrixColumnLength)
    {
        std::cout << "\nError: Matrix addition not possible\n";
        isAdditionPossible = false;
    }

    return isAdditionPossible;
}

bool areMatrixMultiplicationPossible(int secondMatrixRowLength, int firstMatrixColumnLength)
{
    bool isMultiplicationPossible = true;

    if (firstMatrixColumnLength != secondMatrixRowLength)
    {
        std::cout << "\nError: Matrix multiplication not possible\n";
        isMultiplicationPossible = false;
    }

    return isMultiplicationPossible;
}

void performMatrixOperations(double **firstMatrix, double **secondMatrix, int firstMatrixRowLength,
                             int firstMatrixColumnLength, int secondMatrixRowLength, int secondMatrixColumnLength)
{
    if (areMatrixAdditionPossible(firstMatrixRowLength, secondMatrixRowLength, firstMatrixColumnLength, secondMatrixColumnLength))
    {
        double **sumMatrix = allocateMemoryForMatrix(firstMatrixRowLength, firstMatrixColumnLength);

        performMatrixAddition(firstMatrix, secondMatrix, sumMatrix,
                              firstMatrixRowLength, firstMatrixColumnLength);

        displayMatrix(sumMatrix, firstMatrixRowLength, firstMatrixColumnLength, "Addition");

        deleteMemoryOfMatrix(sumMatrix, firstMatrixRowLength);
    }

    if (areMatrixMultiplicationPossible(secondMatrixRowLength, firstMatrixColumnLength))
    {
        double **multiplicationMatrix = allocateMemoryForMatrix(firstMatrixRowLength, secondMatrixColumnLength);

        performMatrixMultiplication(firstMatrix, secondMatrix, multiplicationMatrix,
                                    firstMatrixRowLength, firstMatrixColumnLength, secondMatrixColumnLength);

        displayMatrix(multiplicationMatrix, firstMatrixRowLength, secondMatrixColumnLength, "Multiplication");

        deleteMemoryOfMatrix(multiplicationMatrix, firstMatrixRowLength);
    }
}

bool validateMatrixDimensions(int rowLength, int columnLength)
{
    bool isMatrixDimensionsValid = true;

    if (rowLength <= 0 || columnLength <= 0)
    {
        std::cout << "\nError: Matrix dimensions must be greater than zero.\n";
        isMatrixDimensionsValid = false;
    }

    return isMatrixDimensionsValid;
}

void readDimensionOfMatrix(int &rowLength, int &columnLength, const std::string &messageForRowLength, const std::string &messageForColumnLength)
{
    while (true)
    {
        std::cout << "\n" << messageForRowLength;
        rowLength = readValidatedUserInput();

        std::cout << messageForColumnLength;
        columnLength = readValidatedUserInput();

        if (validateMatrixDimensions(rowLength, columnLength))
        {
            break;
        }
    }
}

int main()
{
    int userInputChoice, firstMatrixRowLength, firstMatrixColumnLength, secondMatrixRowLength, secondMatrixColumnLength;

    do
    {
        readDimensionOfMatrix(firstMatrixRowLength, firstMatrixColumnLength, "Enter rows of first matrix : ", "Enter columns of first matrix : ");

        double **firstMatrix = allocateMemoryForMatrix(firstMatrixRowLength, firstMatrixColumnLength);
        readMatrixFromUser(firstMatrix, firstMatrixRowLength, firstMatrixColumnLength);

        readDimensionOfMatrix(secondMatrixRowLength, secondMatrixColumnLength, "Enter rows of second matrix : ", "Enter columns of second matrix : ");

        double **secondMatrix = allocateMemoryForMatrix(secondMatrixRowLength, secondMatrixColumnLength);
        readMatrixFromUser(secondMatrix, secondMatrixRowLength, secondMatrixColumnLength);

        performMatrixOperations(firstMatrix, secondMatrix, firstMatrixRowLength, firstMatrixColumnLength, secondMatrixRowLength, secondMatrixColumnLength);

        deleteMemoryOfMatrix(firstMatrix, firstMatrixRowLength);
        deleteMemoryOfMatrix(secondMatrix, secondMatrixRowLength);

        userInputChoice = readUserChoice();

    } while (userInputChoice != 0);

    std::cout << "\nExiting program...\nThank you for using the program\n";
    return 0;
}
