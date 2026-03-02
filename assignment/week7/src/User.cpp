#include "IUser.h"
#include "Constants.h"
#include "Input.h"

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

bool User::isAccountHolder() const
{
    return false;
}

bool User::isAdmin() const
{
    return false;
}

Account* User::getAccount() const
{
    return nullptr;
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
