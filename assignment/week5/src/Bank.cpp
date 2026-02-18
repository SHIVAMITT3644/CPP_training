#include <iostream>
#include "Bank.h"
#include "Constants.h"
#include "Input.h"
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

bool Bank::addUser(User *user)
{
    bool isAdded;

    if (findUser(user->getUserName()) != nullptr)
    {
        isAdded = false;
    }
    else
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

        isAdded = true;
    }

    return isAdded;
}

bool Bank::removeUser(int accountNumber, RemovalType type)
{
    bool isFound = false;
    bool isRemoved = false;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(*(users + userIndex));

        if (accountHolder != nullptr && accountHolder->getAccount()->getAccountNumber() == accountNumber)
        {
            isFound = true;

            if (type == RemovalType::Temporary)
            {
                if (accountHolder->getAccount()->getStatus() == INACTIVE)
                {
                    std::cout << ACCOUNT_ALREADY_DEACTIVATE_MESSAGE;
                }
                else
                {
                    accountHolder->getAccount()->changeStatus(INACTIVE);
                    isRemoved = true;
                    std::cout << ACCOUNT_DEACTIVATE_MESSAGE;
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
                std::cout << ACCOUNT_DELETE_MESSAGE;
                isRemoved = true;
            }

            break;
        }
    }

    if (isFound == false)
    {
        std::cout << ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE;
    }

    return isRemoved;
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

User *Bank::findUser(const std::string &userName) const
{
    User *user = nullptr;

    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        if ((*(users + userIndex))->getUserName() == userName)
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

Bank::~Bank()
{
    for (int userIndex = 0; userIndex < numberOfUsers; userIndex++)
    {
        delete *(users + userIndex);
    }

    delete[] users;
}

User* Bank::loginAccountHolder() const
{
    int inputAccountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
    std::string password = User::getValidPasswordInput();

    User *user = findUser(inputAccountNumber);
    AccountHolder *accountHolder = nullptr;

    if (user != nullptr)
    {
        accountHolder = dynamic_cast<AccountHolder *>(user);

        if (accountHolder != nullptr && user->getPassword() == password)
        {
            if (accountHolder->getAccount()->getStatus() != ACTIVE)
            {
                std::cout << CURRENT_ACCOUNT_STATUS_MESSAGE << accountHolder->getAccount()->getStatus() << CONTACT_BANK_ERROR_MESSAGE;
                accountHolder = nullptr;
            }
        }
        else
        {
            std::cout << INVALID_PASSWORD_ERROR_MESSAGE;
            accountHolder = nullptr;
        }
    }
    else
    {
        std::cout << ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE;
        accountHolder = nullptr;
    }

    return accountHolder;
}

User* Bank::loginAdmin() const
{
    std::string username = User::getValidUserNameInput();
    std::string password = User::getValidPasswordInput();

    User *user = findUser(username);

    if (user != nullptr)
    {
        if (user->getPassword() != password)
        {
            user = nullptr;
            std::cout << INVALID_PASSWORD_ERROR_MESSAGE;
        }
    }
    else
    {
        std::cout << ADMIN_NOT_FOUND_ERROR_MESSAGE;
    }

    return user;
}

User *Bank::login(const std::string &role) const
{
    User *user = nullptr;

    if (role == ACCOUNT_HOLDER)
    {
        user = loginAccountHolder();
    }
    else
    {
        user = loginAdmin();
    }

    return user;
}
