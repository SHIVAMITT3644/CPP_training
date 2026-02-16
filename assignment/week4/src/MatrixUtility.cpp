#include <iostream>
#include "MatrixUtility.h"
#include "Input.h"
#include "Matrix.h"
#include "Constants.h"

void MatrixUtility::displayMatrixOperationMenu()
{
    displayMessage(GREETING_MESSAGE);
    displayMessage(LIST_MATRIX_OPERATION);
}

void MatrixUtility::displayMessage(const std::string& message) const
{
    std::cout << message;
}

char MatrixUtility::readMatrixOperationChoice()
{
    while (true)
    {
        int matrixOperationChoice =
            readValidatedIntegerNumber(MATRIX_OPERATION_CHOICE_MESSAGE);

        if (matrixOperationChoice == 1)
            return '+';
        else if (matrixOperationChoice == 2)
            return '*';

        std::cout << INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE;
    }
}

int MatrixUtility::readValidMatrixDimensionLength(const std::string &message)
{
    while (true)
    {
        int dimensionValue = readValidatedIntegerNumber(message);

        if (dimensionValue > 0)
            return dimensionValue;

        std::cout << INVALID_MATRIX_DIMENSION_ERROR_MESSAGE;
    }
}

void MatrixUtility::initializeFirstMatrixDimension()
{
    firstMatrix.rowLength =
        readValidMatrixDimensionLength(FIRST_MATRIX_ROW_INPUT_MESSAGE);

    firstMatrix.columnLength =
        readValidMatrixDimensionLength(FIRST_MATRIX_COLUMN_INPUT_MESSAGE);
}

void MatrixUtility::initializeSecondMatrixDimension()
{
    secondMatrix.rowLength =
        readValidMatrixDimensionLength(SECOND_MATRIX_ROW_INPUT_MESSAGE);

    secondMatrix.columnLength =
        readValidMatrixDimensionLength(SECOND_MATRIX_COLUMN_INPUT_MESSAGE);
}

int MatrixUtility::getFirstMatrixRowLength() const
{
    return firstMatrix.rowLength;
}

int MatrixUtility::getFirstMatrixColumnLength() const
{
    return firstMatrix.columnLength;
}

int MatrixUtility::getSecondMatrixRowLength() const
{
    return secondMatrix.rowLength;
}

int MatrixUtility::getSecondMatrixColumnLength() const
{
    return secondMatrix.columnLength;
}

bool MatrixUtility::isMatrixAdditionPossible() const
{
    if (firstMatrix.rowLength != secondMatrix.rowLength ||
        firstMatrix.columnLength != secondMatrix.columnLength)
    {
        std::cout << ADDITION_NOT_POSSIBLE_ERROR_MESSAGE;
        return false;
    }

    return true;
}

bool MatrixUtility::isMatrixMultiplicationPossible() const
{
    if (firstMatrix.columnLength != secondMatrix.rowLength)
    {
        std::cout << MULTIPLICATION_NOT_POSSIBLE_ERROR_MESSAGE;
        return false;
    }

    return true;
}

bool MatrixUtility::isMatrixCalculationPossible(char matrixOperationChoice) const
{
    switch (matrixOperationChoice)
    {
        case '+':
            return isMatrixAdditionPossible();

        case '*':
            return isMatrixMultiplicationPossible();

        default:
            std::cout << INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE;
            return false;
    }
}

void MatrixUtility::createMatrix(Matrix &matrix, const std::string& message)
{
    displayMessage(message);

    for (int rowIndex = 0; rowIndex < matrix.getRowLength(); rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.getColumnLength(); columnIndex++)
        {
            *(*(matrix.getMatrixPointer() + rowIndex) + columnIndex) =
                readValidatedDecimalNumber(
                    "Enter value for Position Matrix[" +
                    std::to_string(rowIndex) + "][" +
                    std::to_string(columnIndex) + "] : ");
        }
    }
}
