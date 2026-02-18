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

void Admin::viewAccountHolderBalance(User* user) const
{
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

void Admin::viewAccountHolderTransactionHistory(User* user) const
{
   
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
