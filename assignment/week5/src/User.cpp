#include "User.h"
#include "Constants.h"
#include "Input.h"
#include "Bank.h"
#include "AccountHolder.h"

std::string User::getName() const
{
    return name;
}

std::string User::getUserName() const
{
    return userName;
}

std::string User::getPassword() const
{
    return password;
}

void User::setName(const std::string &name)
{
    this->name = name;
}

void User::setUserName(const std::string &userName)
{
    this->userName = userName;
}

void User::setPassword(const std::string &password)
{
    this->password = password;
}


std::string User::getValidUserNameInput() 
{
    std::string userName;

    while (true)
    {
        readCompleteLineInput(std::cin, userName, USERNAME_INPUT_PROMPT);

        if (userName.length() <= 4)
        {
            std::cout << USERNAME_INPUT_ERROR_MESSAGE;
        }
        else
        {
            break;
        }
    }

    return userName;
}

std::string User::getValidPasswordInput() 
{
    std::string password;

    while (true)
    {
        password = readHiddenPassword(PASSWORD_INPUT_PROMPT);

        if (password.length() <= 4)
        {
            std::cout << PASSWORD_INPUT_ERROR_MESSAGE;
        }
        else
        {
            break;
        }
    }

    return password;
}

User *User::accountHolderLogin(const Bank &bank)
{
    int inputAccountNumber;
    std::string password;

    inputAccountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
    password = getValidPasswordInput();
    
    User *user = bank.findUser(inputAccountNumber);
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

User *User::adminLogin(const Bank &bank)
{
    std::string password;

    User *user = bank.findUser(getValidUserNameInput());
    password = getValidPasswordInput();

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

User *User::login(const Bank &bank, std::string userType)
{
    User *user = nullptr;

    if (userType == ACCOUNT_HOLDER)
    {
        user = accountHolderLogin(bank);
    }
    else
    {
        user = adminLogin(bank);
    }

    return user;
}
