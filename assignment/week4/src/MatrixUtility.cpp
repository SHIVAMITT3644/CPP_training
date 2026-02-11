#include <iostream>
#include "MatrixUtility.h"
#include "Input.h"
#include "Matrix.h"
#include "Constants.h"

void MatrixUtility::displayMatrixOperationMenu()
{
    std::cout << GREETING_MESSAGE;
    std::cout << LIST_MATRIX_OPERATION;
}

char MatrixUtility::readMatrixOperationChoice()
{
    int matrixOperationChoice = 0;
    char matrixOperationChoiceChar;

    while (true)
    {
        matrixOperationChoice = readValidatedIntegerNumber(MATRIX_OPERATION_CHOICE_MESSAGE);

        if (matrixOperationChoice == 1) 
        {
            matrixOperationChoiceChar = '+';
            break;
        }
        else if (matrixOperationChoice == 2)
        {
            matrixOperationChoiceChar = '*';
            break;
        }
        else
        {
            std::cout << INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE;
            continue;
        }
    }

    return matrixOperationChoiceChar;
}

int MatrixUtility::readValidMatrixDimensionLength(const std::string &message)
{
    int dimensionValue = 0;

    while (true)
    {
        dimensionValue = readValidatedIntegerNumber(message);

        if (dimensionValue > 0)
        {
            break;
        }
        else
        {
            std::cout << INVALID_MATRIX_DIMENSION_ERROR_MESSAGE;
        }
    }

    return dimensionValue;
}



bool MatrixUtility::isMatrixAdditionPossible()
{
    bool isAdittionPossible = true;

    if (firstMatrixRowLength != secondMatrixRowLength || firstMatrixColumnLength != secondMatrixColumnLength)
    {
        std::cout << ADDITION_NOT_POSSIBLE_ERROR_MESSAGE;
        isAdittionPossible = false;
    }

    return isAdittionPossible;
}

bool MatrixUtility::isMatrixMultiplicationPossible()
{
    bool isMultiplicationPossible = true;

    if (firstMatrixColumnLength != secondMatrixRowLength)
    {
        std::cout << MULTIPLICATION_NOT_POSSIBLE_ERROR_MESSAGE;
        isMultiplicationPossible = false;
    }

    return isMultiplicationPossible;
}

 bool MatrixUtility::isMatrixCalculationPossible(char matrixOperationChoice)
 {
    bool isCalculationPossible = false;

    switch (matrixOperationChoice)
    {
    case '+':
        isCalculationPossible = isMatrixAdditionPossible();
        break;

    case '*':
        isCalculationPossible = isMatrixMultiplicationPossible();
        break;
    
    default:
        std::cout << INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE;
        break;
    }

    return isCalculationPossible;
 }


void MatrixUtility::initializeFirstMatrixDimension()
{
    firstMatrixRowLength = readValidMatrixDimensionLength(FIRST_MATRIX_ROW_INPUT_MESSAGE);
    firstMatrixColumnLength = readValidMatrixDimensionLength(FIRST_MATRIX_COLUMN_INPUT_MESSAGE);
}

void MatrixUtility::initializeSecondMatrixDimension()
{
    secondMatrixRowLength = readValidMatrixDimensionLength(SECOND_MATRIX_ROW_INPUT_MESSAGE);
    secondMatrixColumnLength = readValidMatrixDimensionLength(SECOND_MATRIX_COLUMN_INPUT_MESSAGE);
}

int MatrixUtility::getFirstMatrixRowLength()
{
    return firstMatrixRowLength;
}

int MatrixUtility::getFirstMatrixColumnLength()
{
    return firstMatrixColumnLength;
}

int MatrixUtility::getSecondMatrixRowLength()
{
    return secondMatrixRowLength;
}       

int MatrixUtility::getSecondMatrixColumnLength()
{
    return secondMatrixColumnLength;
}

void MatrixUtility::createMatrix(Matrix &matrix , const std::string& message)
{
    std::cout << message;

    for (int rowIndex = 0; rowIndex < matrix.getRowLength(); rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < matrix.getColumnLength(); columnIndex++)
        {
            
            *(*(matrix.getMatrixPointer() + rowIndex) + columnIndex) = readValidatedDecimalNumber("Enter value for Position Matrix[" + std::to_string(rowIndex) + "][" + std::to_string(columnIndex) + "] : ");
        }
    }
}
