#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

constexpr const char* ACCOUNT_HOLDER = "AccountHolder";
constexpr const char* ADMIN = "Admin";
constexpr const char* ACCOUNT_HOLDER_NAME = "\nAccount Holder Name: ";
constexpr const char* ACCOUNT_HOLDER_USERNAME =  "Account Holder UserName: ";
constexpr const char* ACTIVE = "Active";
constexpr const char* INACTIVE = "Inactive";
constexpr const char* INITIAL_DEPOSIT = "Initial Deposit";
constexpr const char* DEPOSITE = "Deposit   ";
constexpr const char* WITHDRAW = "Withdrawal";
constexpr const char* ACCOUNT_NUMBER = "Account Number: ";
constexpr const char* BALANCE = "Balance: ";
constexpr const char* STATUS = "Status: ";

constexpr const char* MAIN_MENU_BODY = R"(
============================
1. Admin
2. Account Holder
3. Exit
============================
)";

constexpr const char* ACCOUNT_HOLDER_MENU_BODY = R"(
1. View Account Details
2. Deposit
3. Withdraw
4. View Balance
5. View Mini Statement
6. View Full Statement
7. Logout
====================================
)";

constexpr const char* ADMIN_MENU_BODY = R"(
1. Create Account Holder Account
2. Delete Account Holder Account
3. View All Account Holders
4. View Account Holder Balance
5. View Account Holder Transaction History
6. Logout
=====================================
)";

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
constexpr const char*  EXIT_PROGRAM_MESSAGE = "Thank you for using the bank simulator. Goodbye!\n";
constexpr const char* LOGGING_OUT_MESSAGE = "\nLogging out...\n";

constexpr const char* ENTER_CHOICE_PROMPT = "\nPlease enter your choice: ";
constexpr const char* ACCOUNT_CREATED_MESSAGE = "\nAccount created successfully. \nYour account number is: ";
constexpr const char* INSUFFICIENT_BALANCE_ERROR_MESSAGE = "\nError: Insufficient balance for withdrawal.\n";
constexpr const char* TRANSACTION_STATEMENT_HEADER = "\n----------------------------------------------------------------\nDate and Time       | Transaction ID | Transaction Type | Amount\n-------------------------------------------------------------------\n";

constexpr const char* DEPOSITE_AMOUNT_PROMPT = "Enter Amount to Deposit : ";
constexpr const char* DEPOSITE_SUCCESS_MESSAGE = "\nDeposit successful. Updated balance: ";
constexpr const char* DEPOSITE_AMOUNT_ERROR_MESSAGE = "\nError: Deposit amount must be greater than zero.\n";
constexpr const char* INITIAL_DEPOSITE_AMOUNT_ERROR_MESSAGE = "\nError: Initial Deposit amount must be greater or equal to zero.\n";
constexpr const char* DEPOSITE_TECHNICAL_ERROR_MESSAGE = "\nERROR: Deposite Unsuccessful!Please try again later";

constexpr const char* WITHDRAW_AMOUNT_PROMPT = "Enter Amount to Withdraw : ";
constexpr const char* WITHDRAW_SUCCESS_MESSAGE = "\nWithdrawal successful. Remaining balance: ";
constexpr const char* WITHDRAW_AMOUNT_ERROR_MESSAGE = "\nError: Withdrawal amount must be greater than zero.\n"; 
constexpr const char* WITHDRAW_ERROR_MESSAGE = "\nError: Withdrawal amount must be less than remaining balance\n";
constexpr const char* WITHDRAW_NOT_POSSIBLE_ERROR_MESSAGE = "\nError: You don't have Balance to withdrawal. \nPlease Deposit amout First\n";
constexpr const char* WITHDRAW_TECHNICAL_ERROR_MESSAGE = "\nERROR: Withdraw Unsuccessful!Please try again later";

constexpr const char* TECHNICAL_ERROR_MESSAGE_FOR_USER_ADD = "\nSomething went wrong while adding user.\n";
constexpr const char* ACCOUNT_NUMBER_INPUT_PROMPT = "Enter Account Number: ";
constexpr const char* PASSWORD_INPUT_PROMPT = "Enter Password: ";
constexpr const char* NAME_INPUT_PROMPT = "Please enter name: ";
constexpr const char* USERNAME_INPUT_PROMPT = "Please enter your Username: ";
constexpr const char* INITIAL_DEPOSIT_INPUT_PROMPT = "Please enter initial deposit amount: ";

constexpr const char* CURRENT_BALANCE_MESSAGE = "\nCurrent Balance: ";

constexpr const char* ACCOUNT_DELETE_MESSAGE = "\nThe account has been permanently removed successfully.\n";
constexpr const char*  ACCOUNT_DEACTIVATE_MESSAGE = "\nThe account has been temporarily deactivated successfully.\n";
constexpr const char* ACCOUNT_ALREADY_DEACTIVATE_MESSAGE = "\nAccount is already inactive.\n";
constexpr const char* CURRENT_ACCOUNT_STATUS_MESSAGE = "\nYour account is currently ";

constexpr const char* MINI_STATEMENT_MESSAGE = "\nMini Statement for Account Number: ";
constexpr const char* FULL_STATEMENT_MESSAGE = "\nFull Statement for Account Number: ";

constexpr const char* TRANSACTION_HISTORY_MESSAGE = "\nTransaction History for ";
constexpr const char* ACCOUNT_BALANCE_MESSAGE = "\nAccount Balance for ";

constexpr const char* ADMIN_NOT_FOUND_ERROR_MESSAGE = "\nError: Admin user not found.\n";
constexpr const char* ACCOUNTHOLDER_NOT_FOUND_MESSAGE = "\nError: No account holders found.\n";
constexpr const char* ACCOUNT_NOT_FOUND_ERROR_MESSAGE = "\nError: no account associated with this account holder.\n";
constexpr const char* INVALID_STRING_INPUT_ERROR_MESSAGE = "\nError: Input cannot be empty. Please try again.\n";

constexpr const char* USERNAME_INPUT_ERROR_MESSAGE = "\nError: UserName must be 5 character Long\n";
constexpr const char* PASSWORD_INPUT_ERROR_MESSAGE = "\nError: Password must be 5 character Long\n";

constexpr const char* ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE = "\nError: Account number not found.\n";
constexpr const char* INVALID_PASSWORD_ERROR_MESSAGE = "\nError: Invalid password.\n";

constexpr const char* CONTACT_BANK_ERROR_MESSAGE = "\nPlease contact the bank for more information.\n";
constexpr const char* CREATE_ACCOUT_USER_EXIST_ERROR_MESSAGE = "\nError: Username already exists. Please choose another username.\n";

constexpr const char* INVALID_INPUT_ERROR_MESSAGE = "\nError: Please enter a valid Number.\n";
constexpr const char* TECHNICAL_ERROR_MESSAGE = "\nSomething went wrong. Please try again.\n";

constexpr const char* NO_TRANSACTION_ERROR_MESSAGE = "\nNo transactions has done yet.\n";

#endif
