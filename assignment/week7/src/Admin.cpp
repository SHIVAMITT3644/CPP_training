#include <iostream>
#include "Admin.h"
#include "Account.h"
#include "Constants.h"

Admin::Admin(const std::string &name, const std::string &userName, const std::string &password)
{
    setName(name);
    setUserName(userName);
    setPassword(password);
}

void Admin::showMenu() const
{
    std::cout << "\n===================================\n";
    std::cout << "Welcome, " << getName() << "!\n";
    std::cout << ADMIN_MENU_BODY;
}

bool Admin::isAdmin() const
{
    return true;
}

bool Admin::viewAccountHolderBalance(User* user) const
{
    bool isSuccessful = false;

    if (user != nullptr)
    {
        if (user->isAccountHolder() && user->getAccount() != nullptr)
        {
            std::cout << ACCOUNT_BALANCE_MESSAGE
                      << user->getName()
                      << ": RS "
                      << user->getAccount()->getBalance()
                      << "\n";

            isSuccessful = true;
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

    return isSuccessful;
}

bool Admin::viewAccountHolderTransactionHistory(User* user) const
{
    bool isSuccessful = false;

    if (user != nullptr)
    {
        if (user->isAccountHolder() && user->getAccount() != nullptr)
        {
            std::cout << TRANSACTION_HISTORY_MESSAGE
                      << user->getUserName()
                      << ":\n";

            user->getAccount()->displayFullStatement();

            isSuccessful = true;
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

    return isSuccessful;
}
