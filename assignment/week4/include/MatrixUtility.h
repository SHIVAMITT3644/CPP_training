#ifndef MATRIX_UTILITY_H
#define MATRIX_UTILITY_H

#include <iostream>
#include "Matrix.h"

class MatrixUtility
{
    struct MatrixDimension
    {
        int rowLength;
        int columnLength;
    };

    MatrixDimension firstMatrix;
    MatrixDimension secondMatrix;

    int readValidMatrixDimensionLength(const std::string &message);

public:
    void displayMatrixOperationMenu();
    char readMatrixOperationChoice();
    void displayMessage(const std::string& message) const;

    void initializeFirstMatrixDimension();
    void initializeSecondMatrixDimension();

    int getFirstMatrixRowLength() const;
    int getFirstMatrixColumnLength() const;
    int getSecondMatrixRowLength() const;
    int getSecondMatrixColumnLength() const;

    bool isMatrixCalculationPossible(char matrixOperationChoice) const;
    bool isMatrixAdditionPossible() const;
    bool isMatrixMultiplicationPossible() const;

    void createMatrix(Matrix &matrix, const std::string &message);
};

#endif // MATRIX_UTILITY_H