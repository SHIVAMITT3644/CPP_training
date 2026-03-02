#include <iostream>
#include <string>
#include "Bank.h"
#include "IUser.h"
#include "Account.h"
#include "Constants.h"

Bank::Bank(const std::string &bankName)
{
    this->bankName = bankName;
    this->capacityOfUsers = 0;
    this->numberOfUsers = 0;
    this->users = nullptr;
    this->accountNumberGenerator = 1;
}

Bank::~Bank()
{
    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        delete *(users + userIndex);
    }

    delete[] users;
}

std::string Bank::getBankName() const
{
    return bankName;
}

int Bank::generateAccountNumber()
{
    int generatedNumber = accountNumberGenerator;
    accountNumberGenerator++;
    return generatedNumber;
}

void Bank::resizeIfNeeded()
{
    if (numberOfUsers == 0)
    {
        capacityOfUsers = 1;
        users = new User*[capacityOfUsers];
    }
    else if (numberOfUsers == capacityOfUsers)
    {
        capacityOfUsers *= 2;

        User** newUsersArray = new User*[capacityOfUsers];

        for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
        {
            *(newUsersArray + userIndex) = *(users + userIndex);
        }

        delete[] users;
        users = newUsersArray;
    }
}

bool Bank::addUser(User *user)
{
    bool isAdded = false;

    if (user != nullptr)
    {
        if (findUser(user->getUserName()) == nullptr)
        {
            resizeIfNeeded();

            *(users + numberOfUsers) = user;
            numberOfUsers++;

            isAdded = true;
        }
    }

    return isAdded;
}

bool Bank::removeUser(int accountNumber, IBank::RemovalType type)
{
    bool isRemoved = false;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        User* user = *(users + userIndex);

        if (user != nullptr)
        {
            if (user->isAccountHolder())
            {
                if (user->getAccount() != nullptr)
                {
                    if (user->getAccount()->getAccountNumber() == accountNumber)
                    {
                        if (type == IBank::RemovalType::Temporary)
                        {
                            if (user->getAccount()->getStatus() == ACTIVE)
                            {
                                user->getAccount()->changeStatus(INACTIVE);
                                isRemoved = true;
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
                            isRemoved = true;
                        }
                    }
                }
            }
        }
    }

    return isRemoved;
}

User* Bank::findUser(int accountNumber) const
{
    User *foundUser = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        User* user = *(users + userIndex);

        if (user != nullptr)
        {
            if (user->isAccountHolder())
            {
                if (user->getAccount() != nullptr)
                {
                    if (user->getAccount()->getAccountNumber() == accountNumber)
                    {
                        foundUser = user;
                    }
                }
            }
        }
    }

    return foundUser;
}

User* Bank::findUser(const std::string &userName) const
{
    User *foundUser = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        if ((*(users + userIndex))->getUserName() == userName)
        {
            foundUser = *(users + userIndex);
        }
    }

    return foundUser;
}

void Bank::displayAllUsers() const
{
    int accountHolderCount = 0;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        User* user = *(users + userIndex);

        if (user != nullptr)
        {
            if (user->isAccountHolder())
            {
                if (user->getAccount() != nullptr)
                {
                    accountHolderCount++;

                    std::cout << ACCOUNT_HOLDER << " : " << accountHolderCount << "\n";
                    std::cout << ACCOUNT_HOLDER_NAME << user->getName() << "\n";
                    std::cout << ACCOUNT_HOLDER_USERNAME << user->getUserName() << "\n";
                    user->getAccount()->displayAccountDetails();
                    std::cout << "-----------------------------------\n";
                }
            }
        }
    }

    if (accountHolderCount == 0)
    {
        std::cout << ACCOUNTHOLDER_NOT_FOUND_MESSAGE;
    }
}

User* Bank::login(IBank::Role role, const std::string &id, const std::string &password) const
{
    User *result = nullptr;

    if (role == IBank::Role::AccountHolder)
    {
        int accountNumber = std::stoi(id);

        User *user = findUser(accountNumber);

        if (user != nullptr)
        {
            if (user->isAccountHolder())
            {
                if (user->getAccount() != nullptr)
                {
                    if (user->getPassword() == password)
                    {
                        if (user->getAccount()->getStatus() == ACTIVE)
                        {
                            result = user;
                        }
                    }
                }
            }
        }
    }
    else
    {
        User *user = findUser(id);

        if (user != nullptr)
        {
            if (user->isAdmin())
            {
                if (user->getPassword() == password)
                {
                    result = user;
                }
            }
        }
    }

    return result;
}
