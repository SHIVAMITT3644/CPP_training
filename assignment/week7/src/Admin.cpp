#include <iostream>
#include "Admin.h"
#include "AccountHolder.h"
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

bool Admin::viewAccountHolderBalance(User* user) const
{
    bool isSuccessful = false;

    if (user != nullptr)
    {
        AccountHolder* accountHolder =
            dynamic_cast<AccountHolder*>(user);

        if (accountHolder != nullptr)
        {
            std::cout << ACCOUNT_BALANCE_MESSAGE
                      << accountHolder->getName()
                      << ": RS "
                      << accountHolder->getAccount()->getBalance()
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

AccountHolder* Admin::getValidAccountHolder(User* user) const
{
    AccountHolder* accountHolder = nullptr;

    if (user != nullptr)
    {
        accountHolder = dynamic_cast<AccountHolder*>(user);
    }

    return accountHolder;
}


bool Admin::viewAccountHolderTransactionHistory(User* user) const
{
    bool isSuccessful = false;

    AccountHolder* accountHolder = getValidAccountHolder(user);

    if (accountHolder != nullptr)
    {
        std::cout << TRANSACTION_HISTORY_MESSAGE
                  << accountHolder->getUserName()
                  << ":\n";

        accountHolder->getAccount()->displayFullStatement();

        isSuccessful = true;
    }
    else
    {
        if (user == nullptr)
        {
            std::cout << ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE;
        }
        else
        {
            std::cout << TECHNICAL_ERROR_MESSAGE;
        }
    }

    return isSuccessful;
}
