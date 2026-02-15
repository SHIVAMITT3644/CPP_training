#include <iostream>
#include "BankSimulator.h"
#include "Bank.h"
#include "Admin.h"
#include "AccountHolder.h"
#include "Input.h"
#include "Constants.h"

void displayWelcomeMessage(const Bank &bank)
{
    std::cout << "Welcome to " << bank.getBankName() << " Simulator!\n";
    std::cout << MAIN_MENU_BODY;
}

void deleteAccountByType(Admin *adminUser, Bank &bank, Bank::RemovalType type)
{
    int accountNumber;
    int deleteTypeChoice;

    while (deleteTypeChoice != 1 && deleteTypeChoice != 2)
    {
        std::cout << DELETE_ACCOUNT_MENU;
        deleteTypeChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

        if (deleteTypeChoice == 1)
        {
            accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
            adminUser->deleteAccountHolderAccount(bank, accountNumber, Bank::RemovalType::Temporary);
        }
        else if (deleteTypeChoice == 2)
        {
            accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
            adminUser->deleteAccountHolderAccount(bank, accountNumber, Bank::RemovalType::Permanent);
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }
}

void executeAdminAction(Admin *adminUser, Bank &bank, int choice)
{
    switch (choice)
    {
    case 1:
        adminUser->createAccountHolderAccount(bank);
        break;

    case 2:
        deleteAccountByType(adminUser, bank, Bank::RemovalType::Temporary);
        break;

    case 3:
        adminUser->viewAllAccountHolders(bank);
        break;

    case 4:
    {
        int accountNumberForBalance;
        accountNumberForBalance = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
        adminUser->viewAccountHolderBalance(bank, accountNumberForBalance);
        break;
    }

    case 5:
    {
        int accountNumberForTransactionHistory;
        accountNumberForTransactionHistory = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
        adminUser->viewAccountHolderTransactionHistory(bank, accountNumberForTransactionHistory);
        break;
    }
    case 6:
        std::cout << LOGGING_OUT_MESSAGE;
        break;

    default:
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        break;
    }
}

void runAdminSimulator(Bank &bank, User *admin)
{
    Admin *adminUser = dynamic_cast<Admin *>(admin);

    if (adminUser != nullptr)
    {
        int adminChoice;

        while (adminChoice != 6)
        {
            adminUser->showMenu();
            adminChoice = readValidUserInput(ENTER_CHOICE_PROMPT);
            executeAdminAction(adminUser, bank, adminChoice);
        }
    }
    else
    {
        std::cout << TECHNICAL_ERROR_MESSAGE;
    }
}

void handleDepositOperation(AccountHolder *accountHolderUser)
{
    if (accountHolderUser->getAccount()->deposit())
    {
        std::cout << DEPOSITE_SUCCESS_MESSAGE << accountHolderUser->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << DEPOSITE_TECHNICAL_ERROR_MESSAGE;
    }
}

void handleWithdrawalOperation(AccountHolder *accountHolderUser)
{
    if(accountHolderUser->getAccount()->getBalance() <= 0)
    {
        std::cout << WITHDRAW_NOT_POSSIBLE_ERROR_MESSAGE;
    }
    else
    {
        if (accountHolderUser->getAccount()->withdraw())
        {
            std::cout << WITHDRAW_SUCCESS_MESSAGE << accountHolderUser->getAccount()->getBalance() << "\n";
        }
        else
        {
            std::cout << WITHDRAW_TECHNICAL_ERROR_MESSAGE;
        }
    }
}

void executeAccountHolderAction(AccountHolder *accountHolderUser, int choice)
{
    switch (choice)
    {

    case 1:
        accountHolderUser->displayUserDetails();
        break;

    case 2:
        handleDepositOperation(accountHolderUser);
        break;

    case 3:
        handleWithdrawalOperation(accountHolderUser);
        break;

    case 4:
        std::cout << CURRENT_BALANCE_MESSAGE << accountHolderUser->getAccount() -> getBalance();
        break;
        
    case 5:
        accountHolderUser->getAccount()->displayMiniStatement();
        break;

    case 6:
        accountHolderUser->getAccount()->displayFullStatement();
        break;

    case 7:
        std::cout << LOGGING_OUT_MESSAGE;
        break;

    default:
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        break;
    }
}

void runAccountHolderSimulator(User *accountHolder)
{
    AccountHolder *accountHolderUser = dynamic_cast<AccountHolder *>(accountHolder);

    if (accountHolderUser != nullptr)
    {
        int accountHolderChoice;

        while (accountHolderChoice != 7)
        {
            accountHolderUser->showMenu();
            accountHolderChoice = readValidUserInput(ENTER_CHOICE_PROMPT);
            executeAccountHolderAction(accountHolderUser, accountHolderChoice);
        }
    }
    else
    {
        std::cout << TECHNICAL_ERROR_MESSAGE;
    }
}

void SignUp(Bank& bank)
{
    std::string name, userName, password;
    double initialDeposit;

    readCompleteLineInput(std::cin, name, NAME_INPUT_PROMPT);

    while (true)
    {
        userName = User::getValidUserNameInput();

        if (bank.findUser(userName) != nullptr)
        {
            std::cout << CREATE_ACCOUT_USER_EXIST_ERROR_MESSAGE;
        }
        else
        {
            break;
        }
    }
    password = User::getValidPasswordInput();
    initialDeposit = readValidFloatingInput(INITIAL_DEPOSIT_INPUT_PROMPT);

    User* newAccountHolder = new AccountHolder(name, userName, password, initialDeposit);
    bank.addUser(newAccountHolder);

    AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(newAccountHolder);
    std::cout << ACCOUNT_CREATED_MESSAGE << accountHolder->getAccount()->getAccountNumber()<< "\n";
}

void handleAccountHolderMenu(Bank &bank)
{
    bool stayInAccountHolderMenu = true;

    while (stayInAccountHolderMenu)
    {
        std::cout << ACCOUNT_HOLDER_ENTRY_MENU;

        int accountHolderChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

        if (accountHolderChoice == 1)
        {
            User *accountHolder = User::login(bank, ACCOUNT_HOLDER);

            if (accountHolder != nullptr)
            {
                runAccountHolderSimulator(accountHolder);
                stayInAccountHolderMenu = false;
            }
        }
        else if (accountHolderChoice == 2)
        {
            SignUp(bank);
        }
        else if (accountHolderChoice == 3)
        {
            stayInAccountHolderMenu = false;
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }
}

void runBankSimulator(Bank &bank)
{
    while (true)
    {
        int bankUserChoice;
        displayWelcomeMessage(bank);
        
        bankUserChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

        if (bankUserChoice == 1)
        {
            User *admin = User::login(bank, ADMIN);

            if (admin != nullptr)
            {
                runAdminSimulator(bank, admin);
            }
        }
        else if (bankUserChoice == 2)
        {
            handleAccountHolderMenu(bank);
        }
        else if (bankUserChoice == 3)
        {
            std::cout << EXIT_PROGRAM_MESSAGE;
            break;
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }
}
