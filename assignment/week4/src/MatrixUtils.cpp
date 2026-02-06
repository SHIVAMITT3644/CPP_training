#include <iostream>
#include "MatrixUtils.h"
#include "ReadUserInput.h"

void MatrixUtils::displayMatrixOperationMenu()
{
    std::cout << "Choose Value you want to proceed\n";

    std::cout << "--------------------------------\n";
    std::cout << "1.Matrix Addition\n2.Matrix Multiplcation\n";
    std::cout << "--------------------------------\n";
}


bool MatrixUtils::validateMatrixOperation(int matrixOperationChoice, firstMatrixDimension dimensionOfFirstMatrix, secondMatrixDimension dimensionOfSecondMatrix, int &userInputChoice)
{
    bool isCalculationPossible = true;

    if (matrixOperationChoice == 1)
    {
        isCalculationPossible = areMatrixAdditionPossible(dimensionOfFirstMatrix, dimensionOfSecondMatrix);
    }
    else
    {
        isCalculationPossible = areMatrixMultiplicationPossible(dimensionOfFirstMatrix, dimensionOfSecondMatrix);
    }

    if (!isCalculationPossible)
    {
        ReadUserInput readUserInput;
        userInputChoice = readUserInput.readUserChoice();
    }

    return isCalculationPossible;
}

bool MatrixUtils::areMatrixAdditionPossible(firstMatrixDimension dimensionOfFirstMatrix, secondMatrixDimension dimensionOfSecondMatrix)
{
    if (dimensionOfFirstMatrix.firstMatrixRowLength != dimensionOfSecondMatrix.secondMatrixRowLength || dimensionOfFirstMatrix.firstMatrixColumnLength != dimensionOfSecondMatrix.secondMatrixColumnLength)
    {
        std::cout << "\nAddition of matrix is not possible\n";
        isAdittionPossible = false;
    }

    return isAdittionPossible;
}

bool MatrixUtils::areMatrixMultiplicationPossible(firstMatrixDimension dimensionOfFirstMatrix, secondMatrixDimension dimensionOfSecondMatrix)
{
    if (dimensionOfFirstMatrix.firstMatrixColumnLength != dimensionOfSecondMatrix.secondMatrixRowLength)
    {
        std::cout << "\nMultiplication of matrix is not possible\n";
        isMultiplicationPossible = false;
    }

    return isMultiplicationPossible;
}
