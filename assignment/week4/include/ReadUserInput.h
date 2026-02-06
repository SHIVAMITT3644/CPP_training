#ifndef READ_USER_INPUT_H
#define READ_USER_INPUT_H

#include <iostream>
#include "CheckUserInputValidity.h"
#include "MatrixDimension.h"

class ReadUserInput : public CheckUserInputValidity
{
private:
    std::string rawInput;
    void readCompleteLineWithNoSkipWS(std::istream& inputStream, std::string& output);

public:
    int readValidatedUserInput(const std::string& inputMessage);
    double readValidatedMatrixValue(int rowIndex, int columnIndex);

    int readMatrixOperationChoice();
    int readValidMatrixDimensionLength(const std::string& message);
    void readMatrixDimension(int& rowLength, int& columnLength, const std::string& rowMessage, const std::string& columnMessage);

    int readUserChoice();
};

#endif
