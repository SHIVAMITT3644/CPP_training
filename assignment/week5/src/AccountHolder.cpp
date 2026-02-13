#include <iostream>
#include "AccountHolder.h"
#include "Constants.h"
#include "Account.h"
#include "Bank.h"

AccountHolder::AccountHolder(const std::string &name, const std::string &email, const std::string &password, int intialBalance)
{
    setUserName(name);
    setEmail(email);
    setPassword(password);
    account = new Account(Bank::accountNumberGenerator, intialBalance) ;
    Bank::accountNumberGenerator++;
}

AccountHolder::~AccountHolder()
{
    delete account;
}

Account* AccountHolder::getAccount() const
{
    return account;
}

void AccountHolder::showMenu() const
{
    std::cout << "\n-----------------------------------\n";
    std::cout << "\nWelcome, " << getUserName() << "!\n";
    std::cout << "1. View Account Details\n";
    std::cout << "2. Deposit Funds\n";
    std::cout << "3. Withdraw Funds\n";
    std::cout << "4. View Mini Statement\n";
    std::cout << "5. View Full Statement\n";
    std::cout << "6. Logout\n";
    std::cout << "\n-----------------------------------\n";
}

void AccountHolder::displayUserDetails() const
{
    std::cout << "\nAccount Holder Name: " << getUserName() << std::endl;
    std::cout << "Account Holder Email: " << getUserEmail() << std::endl;

    if (account != nullptr)
    {
        account->displayAccountDetails();
    }
    else
    {
        std::cout << "\nNo account associated with this account holder.\n";
    }
}

