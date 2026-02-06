#include "Matrix.h"

Matrix::Matrix(int rowLength, int columnLength)
{
    matrix = new double *[rowLength];

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        *(matrix + rowIndex) = new double[columnLength];
    }

    this->rowLength = rowLength;
    this->columnLength = columnLength;
}

void Matrix::readMatrixFromUser(const std::string& message)
{
    std::cout << message;

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columnLength; columnIndex++)
        {
            *(*(matrix + rowIndex) + columnIndex) = readValidatedMatrixValue(rowIndex, columnIndex);
        }
    }
}

void Matrix::displayMatrix(const std::string &message)
{
    std::cout << message;

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columnLength; columnIndex++)
        {
            std::cout << *(*(matrix + rowIndex) + columnIndex) << " ";
        }
        std::cout << "\n";
    }
}

Matrix Matrix::operator +(const Matrix &secondMatrix)
{  
    Matrix sumMatrix(rowLength , columnLength);

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < columnLength; columnIndex++)
        {
            *(*(sumMatrix.matrix + rowIndex) + columnIndex) =
                *(*(matrix + rowIndex) + columnIndex) +
                *(*(secondMatrix.matrix + rowIndex) + columnIndex);
        }
    }

    return sumMatrix;
}

Matrix Matrix::operator *(const Matrix &secondMatrix)
{
    Matrix multiplicationMatrix(rowLength , secondMatrix.columnLength);

    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < secondMatrix.columnLength; columnIndex++)
        {
            *(*(multiplicationMatrix.matrix + rowIndex) + columnIndex) = 0;

            for (int innerIndex = 0; innerIndex < columnLength; innerIndex++)
            {
                *(*(multiplicationMatrix.matrix + rowIndex) + columnIndex) +=
                    (*(*(matrix+ rowIndex) + innerIndex)) *
                    (*(*(secondMatrix.matrix + innerIndex) + columnIndex));
            }
        }
    }

    return multiplicationMatrix;
}

Matrix::~Matrix()
{
    for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
    {
        delete[] *(matrix + rowIndex);
    }

    delete[] matrix;    
}   
