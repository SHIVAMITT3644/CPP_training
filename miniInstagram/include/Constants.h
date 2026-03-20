#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

constexpr const char* DELETE_ACCOUNT_MENU = R"(
============================
1. Temporary Delete
2. Permanent Delete
============================
)";

constexpr const char* ACCOUNT_HOLDER_ENTRY_MENU = R"(
============================
1. Login
2. Signup
3. Back
============================
)";

constexpr const char* CONTINUE_PROGRAM_MESSAGE = "\nEnter 1 to continue and Enter 0 to exit the program : ";
constexpr const char*  EXIT_PROGRAM_MESSAGE = "Thank you for using the instagram. Goodbye!\n";
constexpr const char* LOGGING_OUT_MESSAGE = "\nLogging out...\n";

constexpr const char* ENTER_CHOICE_PROMPT = "\nPlease enter your choice: ";
constexpr const char* ACCOUNT_CREATED_MESSAGE = "\nAccount created successfully. \nYour user name is: ";

constexpr const char* TECHNICAL_ERROR_MESSAGE_FOR_USER_ADD = "\nSomething went wrong while adding user.\n";
constexpr const char* PASSWORD_INPUT_PROMPT = "Enter Password: ";
constexpr const char* NAME_INPUT_PROMPT = "Please enter name: ";
constexpr const char* USERNAME_INPUT_PROMPT = "Please enter your Username: ";

constexpr const char* ACCOUNT_DELETE_MESSAGE = "\nThe account has been permanently removed successfully.\n";
constexpr const char*  ACCOUNT_DEACTIVATE_MESSAGE = "\nThe account has been temporarily deactivated successfully.\n";
constexpr const char* CURRENT_ACCOUNT_STATUS_MESSAGE = "\nYour account is currently ";
constexpr const char* ACCOUNT_NOT_REMOVED_ERROR_MESSAGE = "\nAccount not Removed\n";

constexpr const char* UserName_NOT_FOUND_MESSAGE = "\nError: Username not found.\n";
constexpr const char* INVALID_STRING_INPUT_ERROR_MESSAGE = "\nError: Input cannot be empty. Please try again.\n";

constexpr const char* USERNAME_INPUT_ERROR_MESSAGE = "\nError: UserName must be 5 character Long\n";
constexpr const char* PASSWORD_INPUT_ERROR_MESSAGE = "\nError: Password must be 5 character Long\n";

constexpr const char* INVALID_PASSWORD_ERROR_MESSAGE = "\nError: Invalid password.\n";
constexpr const char* CREATE_ACCOUT_USER_EXIST_ERROR_MESSAGE = "\nError: Username already exists. Please choose another username.\n";
constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
constexpr const char* TECHNICAL_ERROR_MESSAGE = "\nSomething went wrong. Please try again.\n";

#endif