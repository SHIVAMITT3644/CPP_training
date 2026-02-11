#include "MatrixUtility.h"
#include "Input.h"
#include "MatrixOperation.h"
#include "Matrix.h"
#include "Constants.h"

void initializeMatrices(MatrixUtility& matrixUtility,Matrix& firstMatrix, Matrix& secondMatrix)
{
    matrixUtility.createMatrix(firstMatrix, FIRST_MATRIX_INPUT_MESSAGE);
    firstMatrix.displayMatrix(FIRST_MATRIX_OUTPUT_MESSAGE);

    matrixUtility.createMatrix(secondMatrix, SECOND_MATRIX_INPUT_MESSAGE);
    secondMatrix.displayMatrix(SECOND_MATRIX_OUTPUT_MESSAGE);
}

void performMatrixOperation(char matrixOperationChoice, const Matrix& firstMatrix, const Matrix& secondMatrix)
{
    MatrixOperation matrixOperation;

    switch (matrixOperationChoice)
    {
        case '+':
        {
            Matrix sumMatrix = matrixOperation.sumOfMatrix(firstMatrix, secondMatrix);
            sumMatrix.displayMatrix("\nThe Sum of Matrix is : \n");
            break;
        }

        case '*':
        {
            Matrix productMatrix = matrixOperation.productOfMatrix(firstMatrix, secondMatrix);
            productMatrix.displayMatrix("\nThe Product of Matrix is : \n");
            break;
        }

        default:
            std::cout << INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE;
            break;
    }
}

void runMatrixCalculator()
{
    int userInputChoice;
    char matrixOperationChoice;

    do
    {
        MatrixUtility matrixUtility;
        matrixUtility.displayMatrixOperationMenu();

        matrixOperationChoice = matrixUtility.readMatrixOperationChoice();

        matrixUtility.initializeFirstMatrixDimension();
        matrixUtility.initializeSecondMatrixDimension();

        if (!matrixUtility.isMatrixCalculationPossible(matrixOperationChoice))
        {
            userInputChoice = readContinueProgramChoice();
            continue;
        }

        Matrix firstMatrix(matrixUtility.getFirstMatrixRowLength(), matrixUtility.getFirstMatrixColumnLength());
        Matrix secondMatrix(matrixUtility.getSecondMatrixRowLength(), matrixUtility.getSecondMatrixColumnLength());
        initializeMatrices(matrixUtility, firstMatrix, secondMatrix);

        performMatrixOperation(matrixOperationChoice, firstMatrix, secondMatrix);

        userInputChoice = readContinueProgramChoice();

    } while (userInputChoice != 0);

    std::cout << EXIT_PROGRAM_MESSAGE;
}
