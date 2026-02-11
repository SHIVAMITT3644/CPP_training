#include "MatrixOperation.h"
#include "Constants.h"

Matrix MatrixOperation::sumOfMatrix(const Matrix &matrix1, const Matrix &matrix2)
{
    return matrix1 + matrix2;
}

Matrix MatrixOperation::productOfMatrix(const Matrix &matrix1, const Matrix &matrix2)
{
    return matrix1 * matrix2;
}
