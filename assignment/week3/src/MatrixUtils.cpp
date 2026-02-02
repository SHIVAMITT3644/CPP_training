#include <MatrixUtils.h>
#include <limits>

void displayMatrixOperationMenu()
{
    std::cout << "Choose Value you want to proceed\n";

    std::cout << "--------------------------------\n";
    std::cout << "1.Matrix Addition\n2.Matrix Multiplcation\n";
    std::cout << "--------------------------------\n";
}

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

int readValidatedUserInput(const std::string& inputMessage)
{
    int userInput;

    while (true)
    {
        std::cout <<inputMessage ;
        std::cin >> userInput;
        if (isInputValid())
        {
            break;
        }
    }

    return userInput;
}

int readMatrixOperationChoice()
{
    int matrixOperationChoice;

    while (true)
    {
        matrixOperationChoice = readValidatedUserInput("");

        if (matrixOperationChoice != 1 && matrixOperationChoice != 2)
        {
            std::cout << "\nPlease Enter Valid Choice : ";
            continue;
        }

        break;
    }

    return matrixOperationChoice;
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

int readValidMatrixDimension(const std::string &message)
{
    int matixDimensionValue;

    while (true)
    {
        matixDimensionValue = readValidatedUserInput(message);

        if (validateMatrixDimensions(matixDimensionValue))
        {
            break;
        }
    }

    return matixDimensionValue;
}

void readDimensionOfMatrix(Matrix &matrix, const std::string &messageForRowLength, const std::string &messageForColumnLength)
{
    std::cout << "\n";

    matrix.rowLength = readValidMatrixDimension(messageForRowLength);
    matrix.columnLength = readValidMatrixDimension(messageForColumnLength);
}

bool validateMatrixDimensions(int matrixDimensionLength)
{
    bool isMatrixDimensionValid = true;

    if (matrixDimensionLength <= 0)
    {
        std::cout << "\nError: Matrix dimensions must be greater than zero.\n";
        isMatrixDimensionValid = false;
    }

    return isMatrixDimensionValid;
}

bool areMatrixAdditionPossible(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    bool isAdittionPossible = true;

    if (firstMatrix.rowLength != secondMatrix.rowLength || firstMatrix.columnLength != secondMatrix.columnLength)
    {
        std::cout << "\nError: Matrix addition not possible\n";
        isAdittionPossible = false;
    }

    return isAdittionPossible;
}

bool areMatrixMultiplicationPossible(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    bool isMultiplicationPossible = true;

    if (firstMatrix.columnLength != secondMatrix.rowLength)
    {
        std::cout << "\nError: Matrix multiplication not possible\n";
        isMultiplicationPossible = false;
    }

    return isMultiplicationPossible;
}

bool validateMatrixOperation(int matrixOperationChoice, const Matrix &firstMatrix, const Matrix &secondMatrix, int &userInputChoice)
{
    bool isPossible = true;

    if (matrixOperationChoice == 1)
    {
        isPossible = areMatrixAdditionPossible(firstMatrix, secondMatrix);
    }
    else
    {
        isPossible = areMatrixMultiplicationPossible(firstMatrix, secondMatrix);
    }

    if (!isPossible)
    {
        userInputChoice = readUserChoice();
    }

    return isPossible;
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

void readMatrixFromUser(Matrix &matrix , const std::string& message)
{
    std::cout << message;

    for (int rowIndex = 0; rowIndex < matrix.rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.columnLength; columnIndex++)
        {
            *(*(matrix.data + rowIndex) + columnIndex) = readValidatedMatrixValue(rowIndex, columnIndex);
        }
    }
}

void deleteMemoryOfMatrix(Matrix &matrix)
{
    for (int rowIndex = 0; rowIndex < matrix.rowLength; rowIndex++)
    {
        delete[] *(matrix.data + rowIndex);
    }

    delete[] matrix.data;
}

void displayMatrix(const Matrix &matrix, const std::string &message)
{
    std::cout << message;

    for (int rowIndex = 0; rowIndex < matrix.rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.columnLength; columnIndex++)
        {
            std::cout << *(*(matrix.data + rowIndex) + columnIndex) << " ";
        }
        std::cout << "\n";
    }
}

void performMatrixAddition(const Matrix &firstMatrix,  const Matrix &secondMatrix,  Matrix &sumMatrix)
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


void performAdditionOperation(const Matrix &firstMatrix, const Matrix &secondMatrix)
{
    Matrix sumMatrix;

    sumMatrix.rowLength = firstMatrix.rowLength;
    sumMatrix.columnLength = firstMatrix.columnLength;
    sumMatrix.data = allocateMemoryForMatrix(sumMatrix.rowLength, sumMatrix.columnLength);

    performMatrixAddition(firstMatrix, secondMatrix, sumMatrix);
    displayMatrix(sumMatrix, "\nAddition of given matrix \n");
    deleteMemoryOfMatrix(sumMatrix);
    
}

void performMultiplicationOperation(const Matrix &firstMatrix, const Matrix &secondMatrix)
{

    Matrix multiplicationMatrix;

    multiplicationMatrix.rowLength = firstMatrix.rowLength;
    multiplicationMatrix.columnLength = secondMatrix.columnLength;
    multiplicationMatrix.data =  allocateMemoryForMatrix(multiplicationMatrix.rowLength,  multiplicationMatrix.columnLength);

    performMatrixMultiplication(firstMatrix, secondMatrix, multiplicationMatrix);
    displayMatrix(multiplicationMatrix, "\nMultiplication of given matrix\n");
    deleteMemoryOfMatrix(multiplicationMatrix);
    
}

int readUserChoice()
{
    int userInputChoice;

    while (true)
    {
        userInputChoice = readValidatedUserInput("\nEnter 1 to continue and Enter 0 to exit the program : ");

        if (userInputChoice != 1 && userInputChoice != 0)
        {
            std::cout << "\nPlease Enter Valid Choice ";
            continue;
        }

        break;
    }

    return userInputChoice;
}
