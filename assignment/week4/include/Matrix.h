#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "ReadUserInput.h"

class Matrix : public ReadUserInput
{
    private:
    int rowLength , columnLength;
    double **matrix;

    public:

    Matrix(int rowLength, int columnLength);

    void readMatrixFromUser(const std::string& message);
    void displayMatrix(const std::string &message);
    Matrix operator +(const Matrix &secondMatrix);
    Matrix operator *(const Matrix &secondMatrix);

    ~Matrix();    
};

#endif
