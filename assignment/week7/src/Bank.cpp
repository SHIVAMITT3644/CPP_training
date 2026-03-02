#include <iostream>
#include <string>
#include "Bank.h"
#include "User.h"
#include "AccountHolder.h"
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
        AccountHolder *accountHolder =
            dynamic_cast<AccountHolder *>(*(users + userIndex));

        if (accountHolder != nullptr)
        {
            if (accountHolder->getAccount()->getAccountNumber() == accountNumber)
            {
                if (type == IBank::RemovalType::Temporary)
                {
                    if (accountHolder->getAccount()->getStatus() == ACTIVE)
                    {
                        accountHolder->getAccount()->changeStatus(INACTIVE);
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

    return isRemoved;
}

User* Bank::findUser(int accountNumber) const
{
    User *foundUser = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        AccountHolder *accountHolder =
            dynamic_cast<AccountHolder *>(*(users + userIndex));

        if (accountHolder != nullptr)
        {
            if (accountHolder->getAccount()->getAccountNumber() == accountNumber)
            {
                foundUser = *(users + userIndex);
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

    for (int accountHolderIndex = 0; accountHolderIndex < numberOfUsers; accountHolderIndex++)
    {
        AccountHolder *accountHolder =
            dynamic_cast<AccountHolder *>(*(users + accountHolderIndex));

        if (accountHolder != nullptr)
        {
            accountHolderCount++;

            std::cout << ACCOUNT_HOLDER << " : " << accountHolderCount << "\n";
            accountHolder->displayUserDetails();
            std::cout << "-----------------------------------\n";
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
            AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(user);

            if (accountHolder != nullptr)
            {
                if (user->getPassword() == password)
                {
                    if (accountHolder->getAccount()->getStatus() == ACTIVE)
                    {
                        result = accountHolder;
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
            if (user->getPassword() == password)
            {
                result = user;
            }
        }
    }

    return result;
}
