#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

constexpr const char* MAIN_MENU_BODY = R"(
Welcome to Parser Program
============================
1. Parse Json File
2. Parse Csv File
3. Parse Xml File
4. Exit
============================
)";

constexpr const char* PARSER_CONTINUE_EXIT_MENU = R"(
============================
1. Enter File Name
2. Exit
============================
)";

constexpr const char* ENTER_CHOICE_PROMPT = "\nPlease enter your choice: ";
constexpr const char* CONTINUE_PROGRAM_MESSAGE = "\nEnter 1 to continue and Enter 0 to exit the program : ";
constexpr const char*  EXIT_PROGRAM_MESSAGE = "Thank you for using the Parser Program\n";

constexpr const char* INVALID_STRING_INPUT_ERROR_MESSAGE = "\nError: Input cannot be empty. Please try again.\n";
constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
constexpr const char* TECHNICAL_ERROR_MESSAGE = "\nSomething went wrong. Please try again.\n";

#endif