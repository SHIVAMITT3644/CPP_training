#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix
{
    private:
    int rowLength , columnLength;
    double **matrix;

    public:

    Matrix(int rowLength, int columnLength);
    void displayMatrix(const std::string &message);
    Matrix operator+(const Matrix& secondMatrix) const;
    Matrix operator*(const Matrix& secondMatrix) const;
    void operator =(const Matrix &secondMatrix) const;

    int getRowLength() const;
    int getColumnLength() const;    
    double **getMatrixPointer();

    ~Matrix();    
};

#endif
