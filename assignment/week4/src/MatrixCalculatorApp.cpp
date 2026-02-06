#include <iostream>
#include "MatrixUtils.h"
#include "ReadUserInput.h"
#include "Matrix.h"
#include "MatrixDimension.h"
#include "MatrixUtils.h"

void runMatrixCalculator()
{
    int userInputChoice = -1;
    int matrixOperationChoice;

    do
    {
        MatrixUtils matrixUtils;
        matrixUtils.displayMatrixOperationMenu();

        ReadUserInput readUserInput;
        matrixOperationChoice = readUserInput.readMatrixOperationChoice();

        firstMatrixDimension firstMatrixSize;
        secondMatrixDimension secondMatrixSize;
        readUserInput.readMatrixDimension(firstMatrixSize.firstMatrixRowLength, firstMatrixSize.firstMatrixColumnLength, "Enter row of first matrix : ", "Enter column of first matrix : ");
        readUserInput.readMatrixDimension(secondMatrixSize.secondMatrixRowLength, secondMatrixSize.secondMatrixColumnLength, "Enter row of second matrix : ", "Enter column of second matrix : ");
        
        if (!matrixUtils.validateMatrixOperation(matrixOperationChoice, firstMatrixSize, secondMatrixSize, userInputChoice))
        {
            continue;
        }

        Matrix firstMatrix(firstMatrixSize.firstMatrixRowLength, firstMatrixSize.firstMatrixColumnLength);
        firstMatrix.readMatrixFromUser("\nPlease enter your First matrix\n");
        firstMatrix.displayMatrix("\nYour First Matrix\n\n");

        Matrix secondMatrix(secondMatrixSize.secondMatrixRowLength, secondMatrixSize.secondMatrixColumnLength);
        secondMatrix.readMatrixFromUser("\nPlease enter your Second matrix\n");
        secondMatrix.displayMatrix("\nYour Second Matrix\n\n");

        if (matrixOperationChoice == 1)
        {
            Matrix sumMatrix = firstMatrix + secondMatrix;
            sumMatrix.displayMatrix("\nThe Sum of Matrix is : \n");
        }
        else
        {
           Matrix multiplicationMatrix = firstMatrix * secondMatrix;
           multiplicationMatrix.displayMatrix("\nThe Multiplication of Matrix is : \n");
        }

        userInputChoice = readUserInput.readUserChoice();

    } while (userInputChoice != 0);

    std::cout << "\nExiting program...\nThank you for using the program\n";
}

int main()
{
    runMatrixCalculator();
    return 0;
}
