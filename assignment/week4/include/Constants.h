#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string_view>

constexpr const char*  GREETING_MESSAGE =
    "Welcome to Matrix Calculator\n";

constexpr const char* LIST_MATRIX_OPERATION =
    "----------------\n"
    "1.Matrix Addition\n"
    "2.Matrix Multiplcation\n"
    "-------------------\n";

constexpr const char* MATRIX_OPERATION_CHOICE_MESSAGE =
    "Enter your choice for matrix operation : ";

constexpr const char* FIRST_MATRIX_ROW_INPUT_MESSAGE =
    "Enter row of first matrix : ";

constexpr const char* FIRST_MATRIX_COLUMN_INPUT_MESSAGE =
    "Enter column of first matrix : ";

constexpr const char* SECOND_MATRIX_ROW_INPUT_MESSAGE =
    "Enter row of second matrix : ";

constexpr const char* SECOND_MATRIX_COLUMN_INPUT_MESSAGE =
    "Enter column of second matrix : ";

constexpr const char* FIRST_MATRIX_INPUT_MESSAGE =
    "\nPlease enter your First matrix\n";

constexpr const char* FIRST_MATRIX_OUTPUT_MESSAGE =
    "\nYour First Matrix\n\n";

constexpr const char* SECOND_MATRIX_INPUT_MESSAGE =
    "\nPlease enter your Second matrix\n";

constexpr const char* SECOND_MATRIX_OUTPUT_MESSAGE =
    "\nYour Second Matrix\n\n";

constexpr const char* CONTINUE_PROGRAM_MESSAGE =
    "\nEnter 1 to continue and Enter 0 to exit the program : ";

constexpr const char* EXIT_PROGRAM_MESSAGE =
    "\nExiting program...\n"
    "Thank you for using the program\n";

constexpr const char* INVALID_INPUT_ERROR_MESSAGE =
    "\nError: Please enter a valid Number.\n";

constexpr const char* INVALID_MATRIX_DIMENSION_ERROR_MESSAGE =
    "\nError: Matrix dimensions must be greater than zero.\n";

constexpr const char* ADDITION_NOT_POSSIBLE_ERROR_MESSAGE =
    "\nError: Matrix addition is not possible with the given dimensions.\n";

constexpr const char* MULTIPLICATION_NOT_POSSIBLE_ERROR_MESSAGE =
    "\nError: Matrix multiplication is not possible with the given dimensions.\n";

constexpr const char* INVALID_MATRIX_OPERATION_CHOICE_ERROR_MESSAGE =
    "\nError: Invalid matrix operation choice.\n";

#endif //CONSTANTS_H
