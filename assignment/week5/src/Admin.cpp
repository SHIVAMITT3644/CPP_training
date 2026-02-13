#include "Admin.h"
#include <iostream>
#include "AccountHolder.h"
#include "Constants.h"
#include "Input.h"

void Admin::showMenu() const
{

    std::cout << "\n-----------------------------------";
    std::cout << "\nWelcome, " << getUserName() << "!\n";
    std::cout << "1. Create Account Holder Account\n";
    std::cout << "2. Delete Account Holder Account\n";
    std::cout << "3. View All Account Holders\n";
    std::cout << "4. View Account Holder Balance\n";
    std::cout << "5. View Account Holder Transaction History\n";
    std::cout << "6. Logout\n";
    std::cout << "-----------------------------------\n";
}

Admin::Admin(const std::string &userName, const std::string &email, const std::string &password)
{
    setUserName(userName);
    setEmail(email);
    setPassword(password);
}

void Admin::createAccountHolderAccount(Bank& bank)
{
    std::string name, email, password, address, dob;
    double initialDeposit;

    readCompleteLineInput(std::cin , name , NAME_INPUT_PROMPT);
    readCompleteLineInput(std::cin , email , EMAIL_INPUT_PROMPT);
    readCompleteLineInput(std::cin , password , PASSWORD_INPUT_PROMPT);          
    initialDeposit = readValidatedDecimalNumber(INITIAL_DEPOSIT_INPUT_PROMPT);

    User* newAccountHolder = new AccountHolder(name, email, password, initialDeposit);
    bank.addUser(newAccountHolder);
}

void Admin::deleteAccountHolderAccount(Bank& bank ,int accountNumber, Bank::RemovalType type)
{
    bank.removeUser(accountNumber, type);
}

void Admin::viewAllAccountHolders(const Bank& bank) const
{
    bank.displayAllUsers();
}

void Admin::viewAccountHolderBalance(const Bank& bank, int accountNumber) const
{
    User* user = bank.findUser(accountNumber);
    if (user != nullptr)
    {
        AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(user);
        if (accountHolder != nullptr)
        {
            std::cout << "\nAccount Balance for " << accountHolder->getUserName() << ": RS " << accountHolder->getAccount()->getBalance() << "\n";
        }
        else
        {
            std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
        }
    }
    else
    {
        std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
    }
}

void Admin::viewAccountHolderTransactionHistory(const Bank& bank, int accountNumber) const
{
    User* user = bank.findUser(accountNumber);
    if (user != nullptr)
    {
        AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(user);
        if (accountHolder != nullptr)
        {
            std::cout << "\nTransaction History for " << accountHolder->getUserName() << ":\n";
            accountHolder->getAccount()->displayFullStatement();
        }
        else
        {
            std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
        }
    }
    else
    {
        std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
    }
}
