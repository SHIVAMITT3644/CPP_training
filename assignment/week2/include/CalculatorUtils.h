#include <iostream>

#ifndef CALCULATOR_UTILS_H
#define CALCULATOR_UTILS_H

extern "C" void displayCalculatorMenu();
extern "C" bool checkForGarbageAfterInput();
extern "C" void displayResult(double result, double firstOperand, double secondOperand, std ::string operation);
extern "C" bool isInputValid();
extern "C" int readValidatedUserChoice();
extern "C" double readValidatedOperand();

#endif
