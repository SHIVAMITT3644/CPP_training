#ifndef  MATRIX_UTILS_H
#define  MATRIX_UTILS_H

#include <iostream>

struct Matrix
{
    int rowLength;
    int columnLength;
    double **data;
};

void displayMatrixOperationMenu();
int readMatrixOperationChoice();
void readDimensionOfMatrix(Matrix &matrix, const std::string &messageForRowLength, const std::string &messageForColumnLength);
bool validateMatrixDimensions(int matrixLength);
bool validateMatrixOperation(int matrixOperationChoice, const Matrix &firstMatrix, const Matrix &secondMatrix, int &userInputChoice);
double **allocateMemoryForMatrix(int rowLength, int columnLength);
void readMatrixFromUser(Matrix &matrix,  const std::string &messageForRowLength);
void deleteMemoryOfMatrix(Matrix &matrix);
void displayMatrix(const Matrix &matrix, const std::string &message);
void performAdditionOperation(const Matrix &firstMatrix, const Matrix &secondMatrix);
void performMultiplicationOperation(const Matrix &firstMatrix, const Matrix &secondMatrix);
int readUserChoice();

#endif
