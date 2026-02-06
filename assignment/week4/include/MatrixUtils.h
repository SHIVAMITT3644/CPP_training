#ifndef HELPER_UTILITY_H
#define HELPER_UTILITY_H
#include "MatrixDimension.h"
#include "MatrixDimension.h"

class MatrixUtils
{
    bool isAdittionPossible = true;
    bool isMultiplicationPossible = true;
    bool areMatrixAdditionPossible(firstMatrixDimension, secondMatrixDimension);
    bool areMatrixMultiplicationPossible(firstMatrixDimension, secondMatrixDimension);

    public:
    void displayMatrixOperationMenu();  
    bool validateMatrixOperation(int matrixOperationChoice, firstMatrixDimension dimensionOfFirstMatrix, secondMatrixDimension dimensionOfSecondMatrix, int &userInputChoice);

};

#endif
