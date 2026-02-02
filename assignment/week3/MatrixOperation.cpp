#include <iostream>
#include <limits>

struct Matrix
{
    int rowLength;
    int columnLength;
    double **data;
};

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

const int readValidatedUserInput()
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

    const int returnUserInput = userInput;

    return returnUserInput;
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

void deleteMemoryOfMatrix(Matrix &matrix)
{
    for (int rowIndex = 0; rowIndex < matrix.rowLength; rowIndex++)
    {
        delete[] *(matrix.data + rowIndex);
    }

    delete[] matrix.data;
    matrix.data = nullptr;
}

void readMatrixFromUser(Matrix &matrix)
{
    std::cout << "\nPlease enter your matrix\n";

    for (int rowIndex = 0; rowIndex < matrix.rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.columnLength; columnIndex++)
        {
            *(*(matrix.data + rowIndex) + columnIndex) = readValidatedMatrixValue(rowIndex, columnIndex);
        }
    }
}

void displayMatrix(const Matrix &matrix, const std::string &message)
{
    std::cout << "\nMatrix " << message << " Result:\n\n";

    for (int rowIndex = 0; rowIndex < matrix.rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.columnLength; columnIndex++)
        {
            std::cout << *(*(matrix.data + rowIndex) + columnIndex) << " ";
        }
        std::cout << "\n";
    }
}

void performMatrixAddition(const Matrix &firstMatrix, const Matrix &secondMatrix, Matrix &sumMatrix)
{
    for (int rowIndex = 0; rowIndex < firstMatrix.rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < firstMatrix.columnLength; columnIndex++)
        {
            *(*(sumMatrix.data + rowIndex) + columnIndex) =
                *(*(firstMatrix.data + rowIndex) + columnIndex) +
                *(*(secondMatrix.data + rowIndex) + columnIndex);
        }
    }
}

void performMatrixMultiplication(const Matrix &firstMatrix, const Matrix &secondMatrix, Matrix &multiplicationMatrix)
{
    for (int rowIndex = 0; rowIndex < firstMatrix.rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < secondMatrix.columnLength; columnIndex++)
        {
            *(*(multiplicationMatrix.data + rowIndex) + columnIndex) = 0;

            for (int innerIndex = 0; innerIndex < firstMatrix.columnLength; innerIndex++)
            {
                *(*(multiplicationMatrix.data + rowIndex) + columnIndex) +=
                    (*(*(firstMatrix.data + rowIndex) + innerIndex)) *
                    (*(*(secondMatrix.data + innerIndex) + columnIndex));
            }
        }
    }
}

bool areMatrixAdditionPossible(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    if (firstMatrix.rowLength != secondMatrix.rowLength ||
        firstMatrix.columnLength != secondMatrix.columnLength)
    {
        std::cout << "\nError: Matrix addition not possible\n";
        return false;
    }

    return true;
}

bool areMatrixMultiplicationPossible(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    if (firstMatrix.columnLength != secondMatrix.rowLength)
    {
        std::cout << "\nError: Matrix multiplication not possible\n";
        return false;
    }

    return true;
}

bool validateMatrixDimensions(int rowLength, int columnLength)
{
    if (rowLength <= 0 || columnLength <= 0)
    {
        std::cout << "\nError: Matrix dimensions must be greater than zero.\n";
        return false;
    }

    return true;
}

void readDimensionOfMatrix(Matrix &matrix, const std::string &messageForRowLength, const std::string &messageForColumnLength)
{
    while (true)
    {
        std::cout << "\n" << messageForRowLength;
        matrix.rowLength = readValidatedUserInput();;

        std::cout << messageForColumnLength;
        matrix.columnLength = readValidatedUserInput();

        if (validateMatrixDimensions(matrix.rowLength, matrix.columnLength))
        {
            break;
        }
    }
}

void performMatrixOperations(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    if (areMatrixAdditionPossible(firstMatrix, secondMatrix))
    {
        Matrix sumMatrix;
        sumMatrix.rowLength = firstMatrix.rowLength;
        sumMatrix.columnLength = firstMatrix.columnLength;
        sumMatrix.data = allocateMemoryForMatrix(sumMatrix.rowLength, sumMatrix.columnLength);

        performMatrixAddition(firstMatrix, secondMatrix, sumMatrix);
        displayMatrix(sumMatrix, "Addition");
        deleteMemoryOfMatrix(sumMatrix);
    }

    if (areMatrixMultiplicationPossible(firstMatrix, secondMatrix))
    {
        Matrix multiplicationMatrix;

        multiplicationMatrix.rowLength = firstMatrix.rowLength;
        multiplicationMatrix.columnLength = secondMatrix.columnLength;

        multiplicationMatrix.data =  allocateMemoryForMatrix(multiplicationMatrix.rowLength,  multiplicationMatrix.columnLength);

        performMatrixMultiplication(firstMatrix, secondMatrix, multiplicationMatrix);

        displayMatrix(multiplicationMatrix, "Multiplication");

        deleteMemoryOfMatrix(multiplicationMatrix);
    }
}

int main()
{
    int userInputChoice;

    do
    {
        Matrix firstMatrix, secondMatrix;

        readDimensionOfMatrix(firstMatrix, "Enter rows of first matrix : ", "Enter columns of first matrix : ");

        firstMatrix.data = allocateMemoryForMatrix(firstMatrix.rowLength, firstMatrix.columnLength);

        readMatrixFromUser(firstMatrix);

        readDimensionOfMatrix(secondMatrix, "Enter rows of second matrix : ", "Enter columns of second matrix : ");

        secondMatrix.data = allocateMemoryForMatrix(secondMatrix.rowLength, secondMatrix.columnLength);

        readMatrixFromUser(secondMatrix);

        performMatrixOperations(firstMatrix, secondMatrix);

        deleteMemoryOfMatrix(firstMatrix);
        deleteMemoryOfMatrix(secondMatrix);

        userInputChoice = readUserChoice();

    } while (userInputChoice != 0);

    std::cout << "\nExiting program...\nThank you for using the program\n";
    return 0;
}
