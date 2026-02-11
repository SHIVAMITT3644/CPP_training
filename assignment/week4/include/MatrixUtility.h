#ifndef MATRIX_UTILITY_H
#define MATRIX_UTILITY_H

#include <iostream>
#include "Matrix.h"
class MatrixUtility
{
    int firstMatrixRowLength;
    int firstMatrixColumnLength;
    int secondMatrixRowLength;
    int secondMatrixColumnLength;

    int readValidMatrixDimensionLength(const std::string &message);

public:
    void displayMatrixOperationMenu();
    char readMatrixOperationChoice();

    void initializeFirstMatrixDimension();
    void initializeSecondMatrixDimension();
    int getFirstMatrixRowLength();
    int getFirstMatrixColumnLength();
    int getSecondMatrixRowLength();
    int getSecondMatrixColumnLength();

    bool isMatrixCalculationPossible(char matrixOperationChoice);
    bool isMatrixAdditionPossible();
    bool isMatrixMultiplicationPossible();

    void createMatrix(Matrix &matrix, const std::string &message);
};

#endif
