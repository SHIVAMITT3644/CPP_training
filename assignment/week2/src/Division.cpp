#include <stdexcept>
#include "Division.h"

double division(double firstOperand , double secondOperand)
{
    if(secondOperand == 0.0)
    {
        throw std::runtime_error("Division by zero");
    }

    return firstOperand / secondOperand;
}