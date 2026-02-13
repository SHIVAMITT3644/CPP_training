#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>


constexpr const char* CONTINUE_PROGRAM_MESSAGE = "\nEnter 1 to continue and Enter 0 to exit the program : ";
constexpr const char*  EXIT_PROGRAM_MESSAGE = "Thank you for using the bank simulator. Goodbye!\n";
constexpr const char* ENTER_CHOICE_PROMPT = "\nPlease enter your choice: ";
constexpr const char* ACCOUNT_CREATED_MESSAGE = "\nAccount created successfully. \nYour account number is: ";
constexpr const char* INSUFFICIENT_BALANCE_ERROR_MESSAGE = "\nError: Insufficient balance for withdrawal.\n";
constexpr const char* TRANSACTION_STATEMENT_HEADER = "\n----------------------------------------------------------------\nDate and Time | Transaction ID | Transaction Type | Amount\n-------------------------------------------------------------------\n";
constexpr const char* DEPOSITE_AMOUNT_PROMPT = "Enter Amount to Deposit : ";
constexpr const char* DEPOSITE_SUCCESS_MESSAGE = "\nDeposit successful. Updated balance: ";
constexpr const char* DEPOSITE_ERROR_MESSAGE = "\nError: Deposit amount must be greater than zero.\n";

constexpr const char* WITHDRAW_AMOUNT_PROMPT = "Enter Amount to Withdraw : ";
constexpr const char* WITHDRAW_SUCCESS_MESSAGE = "\nWithdrawal successful. Remaining balance: ";
constexpr const char* WITHDRAW_ERROR_MESSAGE = "\nError: Withdrawal amount must be greater than zero.\n"; 

constexpr const char* TECHNICAL_ERROR_MESSAGE_FOR_USER_ADD = "\nSomething went wrong while adding user.\n";
constexpr const char* ACCOUNT_NUMBER_INPUT_PROMPT = "Enter Account Number: ";
constexpr const char* PASSWORD_INPUT_PROMPT = "Enter Password: ";
constexpr const char* NAME_INPUT_PROMPT = "Please enter name: ";
constexpr const char* EMAIL_INPUT_PROMPT = "Please enter email: ";
constexpr const char* ADDRESS_INPUT_PROMPT = "Please enter address: ";
constexpr const char* DOB_INPUT_PROMPT = "Please enter date of birth (YYYY-MM-DD): ";
constexpr const char* INITIAL_DEPOSIT_INPUT_PROMPT = "Please enter initial deposit amount: ";
constexpr const char* ADMIN_NOT_FOUND_ERROR_MESSAGE = "\nError: Admin user not found.\n";

constexpr const char* ACCOUNT_NOT_FOUND_ERROR_MESSAGE = "\nError: Account number not found.\n";
constexpr const char* INVALID_PASSWORD_ERROR_MESSAGE = "\nError: Invalid password.\n";
constexpr const char* CONTACT_BANK_ERROR_MESSAGE = "\nPlease contact the bank for more information.\n";
constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
constexpr const char* TECHNICAL_ERROR_MESSAGE = "\nSomething went wrong. Please try again.\n";

#endif