#include <iostream>
#include "MatrixUtils.h"

void runMatrixCalculator()
{
    int userInputChoice = -1;
    int matrixOperationChoice;

    do
    {
        displayMatrixOperationMenu();
        matrixOperationChoice = readMatrixOperationChoice();

        Matrix firstMatrix, secondMatrix;

        readDimensionOfMatrix(firstMatrix, "Enter row of first matrix : ", "Enter column of first matrix : ");
        readDimensionOfMatrix(secondMatrix, "Enter row of second matrix : ", "Enter column of second matrix : ");

        if (!validateMatrixOperation(matrixOperationChoice, firstMatrix, secondMatrix, userInputChoice))
        {
            continue;
        }

        firstMatrix.data = allocateMemoryForMatrix(firstMatrix.rowLength, firstMatrix.columnLength);
        readMatrixFromUser(firstMatrix, "\nPlease enter your First matrix\n");
        displayMatrix(firstMatrix, "\nYour First Matrix\n\n");

        secondMatrix.data = allocateMemoryForMatrix(secondMatrix.rowLength, secondMatrix.columnLength);
        readMatrixFromUser(secondMatrix, "\nPlease enter your Second matrix\n");
        displayMatrix(secondMatrix, "\nYour Second Matrix\n\n");

        switch (matrixOperationChoice)
        {
        case 1:
            performAdditionOperation(firstMatrix, secondMatrix);
            deleteMemoryOfMatrix(firstMatrix);
            deleteMemoryOfMatrix(secondMatrix);
            break;

        case 2:
            performMultiplicationOperation(firstMatrix, secondMatrix);
            deleteMemoryOfMatrix(firstMatrix);
            deleteMemoryOfMatrix(secondMatrix);
            break;
        }

        userInputChoice = readUserChoice();

    } while (userInputChoice != 0);

    std::cout << "\nExiting program...\nThank you for using the program\n";
}

int main()
{
    runMatrixCalculator();
    return 0;
}
