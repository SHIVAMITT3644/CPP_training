#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

const std::string GREETING_MESSAGE = "Welcome to Matrix Calculator\n";
const std::string LIST_MATRIX_OPERATION = "----------------\n1.Matrix Addition\n2.Matrix Multiplcation\n-------------------\n";
const std::string MATRIX_OPERATION_CHOICE_MESSAGE = "Enter your choice for matrix operation : ";
const std::string FIRST_MATRIX_ROW_INPUT_MESSAGE = "Enter row of first matrix : ";
const std::string FIRST_MATRIX_COLUMN_INPUT_MESSAGE = "Enter column of first matrix : ";
const std::string SECOND_MATRIX_ROW_INPUT_MESSAGE = "Enter row of second matrix : "; 
const std::string SECOND_MATRIX_COLUMN_INPUT_MESSAGE = "Enter column of second matrix : ";
const std::string FIRST_MATRIX_INPUT_MESSAGE = "\nPlease enter your First matrix\n";
const std::string FIRST_MATRIX_OUTPUT_MESSAGE = "\nYour First Matrix\n\n";
const std::string SECOND_MATRIX_INPUT_MESSAGE = "\nPlease enter your Second matrix\n";
const std::string SECOND_MATRIX_OUTPUT_MESSAGE = "\nYour Second Matrix\n\n";
const std::string CONTINUE_PROGRAM_MESSAGE = "\nEnter 1 to continue and Enter 0 to exit the program : ";
const std::string EXIT_PROGRAM_MESSAGE = "\nExiting program...\nThank you for using the program\n";

const std::string INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
const std::string INVALID_MATRIX_DIMENSION_ERROR_MESSAGE = "\nError: Matrix dimensions must be greater than zero.\n";  
const std::string ADDITION_NOT_POSSIBLE_ERROR_MESSAGE = "\nError: Matrix addition is not possible with the given dimensions.\n";
const std::string MULTIPLICATION_NOT_POSSIBLE_ERROR_MESSAGE = "\nError: Matrix multiplication is not possible with the given dimensions.\n";
const std::string INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE = "\nError: Invalid matrix operation choice.\n";

#endif
