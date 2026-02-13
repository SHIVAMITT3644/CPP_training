#include "User.h"
#include "Constants.h"
#include "Input.h"
#include "Bank.h"
#include "AccountHolder.h"

std::string User::getUserName() const
{
    return userName;
}

std::string User::getUserEmail() const
{
    return email;
}

std::string User::getPassword() const
{
    return password;
}

void User::setUserName(const std::string &userName)
{
    this->userName = userName;
}

void User::setEmail(const std::string &email)
{
    this->email = email;
}

void User::setPassword(const std::string &password)
{
    this->password = password;
}

User* User::accountHolderLogin(const Bank& bank)
{
    int inputAccountNumber;
    std::string inputPassword;

    inputAccountNumber = readValidatedIntegerNumber(ACCOUNT_NUMBER_INPUT_PROMPT);
    readCompleteLineInput(std::cin, inputPassword, PASSWORD_INPUT_PROMPT);

    User* user = bank.findUser(inputAccountNumber);
    AccountHolder* accountHolder = nullptr;

    if (user != nullptr)
    {
        accountHolder = dynamic_cast<AccountHolder*>(user);

        if (accountHolder != nullptr && user->getPassword() == inputPassword)
        {
            if(accountHolder->getAccount()->getStatus() != "Active")
            {
                std::cout << "\nYour account is currently " << accountHolder->getAccount()->getStatus() << CONTACT_BANK_ERROR_MESSAGE;
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
        std::cout << ACCOUNT_NOT_FOUND_ERROR_MESSAGE;
        accountHolder = nullptr;
    }

    return accountHolder; 
}

User* User::adminLogin(const Bank& bank)
{
    std::string email,inputPassword;

    readCompleteLineInput(std::cin, email, EMAIL_INPUT_PROMPT);
    readCompleteLineInput(std::cin, inputPassword, PASSWORD_INPUT_PROMPT);

    User* user = bank.findUser(email);    

    if(user != nullptr)
    {
        if(user->getPassword() != inputPassword)
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

User* User::login(const Bank& bank, std::string userType)
{
    User* user = nullptr;

    if(userType == "AccountHolder")
    {
        user = accountHolderLogin(bank);
    }
    else
    {
        user = adminLogin(bank);
    }

    return user;
}
