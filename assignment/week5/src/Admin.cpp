#include <iostream>
#include "Admin.h"
#include "AccountHolder.h"
#include "Constants.h"
#include "Input.h"

void Admin::showMenu() const
{
    std::cout << "\n===================================\n";
    std::cout << "Welcome, " << getName() << "!\n";
    std::cout << ADMIN_MENU_BODY;
}

Admin::Admin(const std::string &name, const std::string &userName, const std::string &password)
{
    setName(name);
    setUserName(userName);
    setPassword(password);
}

void Admin::createAccountHolderAccount(Bank& bank)
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
    
    while(true)
    {
        initialDeposit = readValidFloatingInput(INITIAL_DEPOSIT_INPUT_PROMPT);
        if(initialDeposit < 0)
        {
            std::cout << INITIAL_DEPOSITE_AMOUNT_ERROR_MESSAGE;
        }
        else{
            break;
        }
    }

    User* newAccountHolder = new AccountHolder(name, userName, password, initialDeposit);
    bank.addUser(newAccountHolder);

    AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(newAccountHolder);
    std::cout << ACCOUNT_CREATED_MESSAGE << accountHolder->getAccount()->getAccountNumber()<< "\n";
}

void Admin::deleteAccountHolderAccount(Bank& bank ,int accountNumber, Bank::RemovalType type)
{
    bank.removeUser(accountNumber, type);
}

void Admin::viewAllAccountHolders(const Bank& bank) const
{
    bank.displayAllUsers();
}

void Admin::viewAccountHolderBalance(const Bank& bank) const
{
    int accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);

    User* user = bank.findUser(accountNumber);

    if (user != nullptr)
    {
        AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(user);
        if (accountHolder != nullptr)
        {
            std::cout << ACCOUNT_BALANCE_MESSAGE << accountHolder->getName() << ": RS " << accountHolder->getAccount()->getBalance() << "\n";
        }
        else
        {
            std::cout << TECHNICAL_ERROR_MESSAGE;
        }
    }
    else
    {
        std::cout << ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE;
    }
}

void Admin::viewAccountHolderTransactionHistory(const Bank& bank) const
{
    int accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);

    User* user = bank.findUser(accountNumber);
    if (user != nullptr)
    {
        AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(user);
        if (accountHolder != nullptr)
        {
            std::cout << TRANSACTION_HISTORY_MESSAGE << accountHolder->getUserName() << ":\n";
            accountHolder->getAccount()->displayFullStatement();
        }
        else
        {
            std::cout << TECHNICAL_ERROR_MESSAGE;
        }
    }
    else
    {
        std::cout << ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE;
    }
}
