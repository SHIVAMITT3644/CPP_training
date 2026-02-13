#include "Bank.h"
#include <iostream>
#include "Constants.h"
#include "AccountHolder.h"

int Bank::accountNumberGenerator = 1;

Bank::Bank(const std::string &bankName)
{
    this->bankName = bankName;
    this->capacityOfUsers = 0;
    this->numberOfUsers = 0;
    this->users = nullptr;
}

std::string Bank::getBankName() const
{
    return bankName;
}

void Bank::addUser(User *user)
{
    if (numberOfUsers == 0)
    {
        capacityOfUsers = 1;
        users = new User *[capacityOfUsers];
    }
    else if (numberOfUsers == capacityOfUsers)
    {
        capacityOfUsers *= 2;
        User **newUsersArray = new User *[capacityOfUsers];

        for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
        {
            *(newUsersArray + userIndex) = *(users + userIndex);
        }

        delete[] users;
        users = newUsersArray;
    }

    *(users + numberOfUsers) = user;
    numberOfUsers++;

    // AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(user);

    // if (accountHolder != nullptr)
    // {
    //     std::cout << ACCOUNT_CREATED_MESSAGE << accountHolder->getAccount()->getAccountNumber() << "\n";
    // }
    // else
    // {
    //     std::cout << TECHNICAL_ERROR_MESSAGE_FOR_USER_ADD;
    // }
}

void Bank::removeUser(int accountNumber, RemovalType type)
{
    AccountHolder *accountHolder = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        accountHolder = dynamic_cast<AccountHolder *> (*(users + userIndex));

        if (accountHolder != nullptr && accountHolder->getAccount()->getAccountNumber() == accountNumber)
        {
            if (type == RemovalType::Temporary)
            {
                if(accountHolder->getAccount()->getStatus() == "Inactive")
                {
                    std::cout << "\nAccount is already inactive.\n";
                }
                else
                {
                    accountHolder->getAccount()->changeStatus("Inactive");
                    std::cout << "\nAccount temporarily deactivated.\n";
                }
            }
            else
            {
                delete *(users + userIndex);  
                for (int shiftIndex = userIndex; shiftIndex < numberOfUsers - 1; shiftIndex++)
                {
                    *(users + shiftIndex) = *(users + shiftIndex + 1);
                }

                numberOfUsers--;
                std::cout << "\nAccount permanently removed.\n";   
            }
        }
        else
        {
            accountHolder = nullptr;
        }
    }

    if (accountHolder == nullptr)
    {
        std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
    }
}

User *Bank::findUser(int accountNumber) const
{
    User *user = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(*(users + userIndex));

        if (accountHolder != nullptr && accountHolder->getAccount()->getAccountNumber() == accountNumber)
        {
            user = *(users + userIndex);
        }
    }

    return user;
}

User* Bank::findUser(const std::string &email) const
{
    User *user = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        if ((*(users + userIndex))->getUserEmail() == email)
        {
            user = *(users + userIndex);
        }
    }

    return user;
}

void Bank::displayAllUsers() const
{
    int accountHolderCount = 0;

    for (int accountHolderIndex = 0; accountHolderIndex < numberOfUsers; accountHolderIndex++)
    {
        AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(*(users + accountHolderIndex));

        if (accountHolder != nullptr)
        {
            accountHolderCount++;

            std::cout << "\nAccount Holder " << accountHolderCount << ":\n";
            accountHolder->displayUserDetails();
        }
    }

    if (accountHolderCount == 0)
    {
        std::cout << "\nNo account holders found.\n";
    }
}

Bank::~Bank()
{
    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        delete *(users + userIndex);
    }

    delete[] users;
}