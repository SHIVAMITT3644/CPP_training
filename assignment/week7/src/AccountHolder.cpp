#include <iostream>
#include "AccountHolder.h"
#include "Constants.h"

AccountHolder::AccountHolder(const std::string &name, const std::string &userName, const std::string &password, int accountNumber, double initialBalance)
{
    setName(name);
    setUserName(userName);
    setPassword(password);

    account = new Account(accountNumber, initialBalance);
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
    std::cout << "\n===================================\n";
    std::cout << "Welcome, " << getName() << "\n";
    std::cout << ACCOUNT_HOLDER_MENU_BODY;
}

void AccountHolder::displayUserDetails() const
{
    std::cout << ACCOUNT_HOLDER_NAME << getName() << std::endl;
    std::cout << ACCOUNT_HOLDER_USERNAME << getUserName() << std::endl;

    if (account != nullptr)
    {
        account->displayAccountDetails();
    }
    else
    {
        std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
    }
}
