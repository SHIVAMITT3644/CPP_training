#include <iostream>
#include <string>
#include "BankSimulator.h"
#include "IBank.h"
#include "Admin.h"
#include "AccountHolder.h"
#include "Input.h"
#include "Constants.h"


bool performDeposit(AccountHolder *accountHolderUser, double amount)
{
    bool isSuccessful = false;

    if (accountHolderUser != nullptr)
    {
        isSuccessful = accountHolderUser->getAccount()->deposit(amount);
    }

    return isSuccessful;
}

bool performWithdrawal(AccountHolder *accountHolderUser, double amount)
{
    bool isSuccessful = false;

    if (accountHolderUser != nullptr)
    {
        isSuccessful = accountHolderUser->getAccount()->withdraw(amount);
    }

    return isSuccessful;
}

bool createAccountHolderInBank(IBank &bank,
                               const std::string &name,
                               const std::string &userName,
                               const std::string &password,
                               double initialDeposit,
                               int &createdAccountNumber)
{
    bool isCreated = false;
    createdAccountNumber = 0;

    if (bank.findUser(userName) == nullptr)
    {
        if (initialDeposit >= 0)
        {
            int newAccountNumber = bank.generateAccountNumber();

            User *newAccountHolder = new AccountHolder(name, userName, password, newAccountNumber, initialDeposit);

            if (bank.addUser(newAccountHolder))
            {
                createdAccountNumber = newAccountNumber;
                isCreated = true;
            }
            else
            {
                delete newAccountHolder;
            }
        }
    }

    return isCreated;
}

bool deleteAccount(IBank &bank, int accountNumber, IBank::RemovalType type)
{
    bool isRemoved = false;
    isRemoved = bank.removeUser(accountNumber, type);
    return isRemoved;
}

User* loginAdminFlow(IBank &bank)
{
    User *loggedInUser = nullptr;

    std::string userName = User::getValidUserNameInput();
    std::string password = User::getValidPasswordInput();

    User *foundUser = bank.findUser(userName);

    if (foundUser == nullptr)
    {
        std::cout << ADMIN_NOT_FOUND_ERROR_MESSAGE;
    }
    else
    {
        if (foundUser->getPassword() != password)
        {
            std::cout << INVALID_PASSWORD_ERROR_MESSAGE;
        }
        else
        {
            loggedInUser = bank.login(IBank::Role::Admin, userName, password);
        }
    }

    return loggedInUser;
}

User* loginAccountHolderFlow(IBank &bank)
{
    User *loggedInUser = nullptr;

    int accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
    std::string password = User::getValidPasswordInput();

    User *foundUser = bank.findUser(accountNumber);

    if (foundUser == nullptr)
    {
        std::cout << ACCOUNT_NUMBER_NOT_FOUND_ERROR_MESSAGE;
    }
    else
    {
        AccountHolder *accountHolder = dynamic_cast<AccountHolder *>(foundUser);

        if (accountHolder == nullptr)
        {
            std::cout << TECHNICAL_ERROR_MESSAGE;
        }
        else
        {
            if (foundUser->getPassword() != password)
            {
                std::cout << INVALID_PASSWORD_ERROR_MESSAGE;
            }
            else
            {
                if (accountHolder->getAccount()->getStatus() != ACTIVE)
                {
                    std::cout << CURRENT_ACCOUNT_STATUS_MESSAGE
                              << accountHolder->getAccount()->getStatus()
                              << CONTACT_BANK_ERROR_MESSAGE;
                }
                else
                {
                    loggedInUser = bank.login(IBank::Role::AccountHolder,
                                              std::to_string(accountNumber),
                                              password);
                }
            }
        }
    }

    return loggedInUser;
}

void displayWelcomeMessage(const IBank &bank)
{
    std::cout << "Welcome to " << bank.getBankName() << " Simulator!\n";
    std::cout << MAIN_MENU_BODY;
}

void deleteAccountByType(IBank &bank)
{
    int accountNumber = 0;
    int deleteTypeChoice = 0;
    bool isRemoved = false;

    while (deleteTypeChoice != 1 && deleteTypeChoice != 2)
    {
        std::cout << DELETE_ACCOUNT_MENU;
        deleteTypeChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

        if (deleteTypeChoice == 1 || deleteTypeChoice == 2)
        {
            accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);

            IBank::RemovalType type =
                (deleteTypeChoice == 1)
                    ? IBank::RemovalType::Temporary
                    : IBank::RemovalType::Permanent;

            isRemoved = deleteAccount(bank, accountNumber, type);

            if (!isRemoved)
            {
                std::cout << ACCOUNT_NOT_REMOVED_ERROR_MESSAGE;
            }
            else
            {
                if (type == IBank::RemovalType::Temporary)
                {
                    std::cout << ACCOUNT_DEACTIVATE_MESSAGE;
                }
                else
                {
                    std::cout << ACCOUNT_DELETE_MESSAGE;
                }
            }
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }
}

void handleCreateAccountHolder(IBank &bank)
{
    std::string name, userName, password;
    double initialDeposit = 0.0;
    int createdAccountNumber = 0;

    readCompleteLineInput(std::cin, name, NAME_INPUT_PROMPT);

    while (true)
    {
        userName = User::getValidUserNameInput();

        if (bank.findUser(userName) != nullptr)
        {
            std::cout << CREATE_ACCOUT_USER_EXIST_ERROR_MESSAGE;
        }
        else
        {
            break;
        }
    }

    password = User::getValidPasswordInput();

    while (true)
    {
        initialDeposit = readValidFloatingInput(INITIAL_DEPOSIT_INPUT_PROMPT);

        if (initialDeposit < 0)
        {
            std::cout << INITIAL_DEPOSITE_AMOUNT_ERROR_MESSAGE;
        }
        else
        {
            break;
        }
    }

    bool isCreated = createAccountHolderInBank(bank, name, userName, password, initialDeposit, createdAccountNumber);

    if (isCreated)
    {
        std::cout << ACCOUNT_CREATED_MESSAGE << createdAccountNumber << "\n";
    }
    else
    {
        std::cout << TECHNICAL_ERROR_MESSAGE_FOR_USER_ADD;
    }
}

User* getUserByAccountNumber(const IBank &bank)
{
    int accountNumber = readValidUserInput(ACCOUNT_NUMBER_INPUT_PROMPT);
    return bank.findUser(accountNumber);
}

void executeAdminAction(Admin *adminUser, IBank &bank, int choice)
{
    switch (choice)
    {
    case 1:
        handleCreateAccountHolder(bank);
        break;

    case 2:
        deleteAccountByType(bank);
        break;

    case 3:
        bank.displayAllUsers();
        break;

    case 4:
    {
        User *user = getUserByAccountNumber(bank);
        adminUser->viewAccountHolderBalance(user);
        break;
    }

    case 5:
    {
        User *user = getUserByAccountNumber(bank);
        adminUser->viewAccountHolderTransactionHistory(user);
        break;
    }

    case 6:
        std::cout << LOGGING_OUT_MESSAGE;
        break;

    default:
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        break;
    }
}

void runAdminSimulator(IBank &bank, User *admin)
{
    Admin *adminUser = dynamic_cast<Admin *>(admin);

    if (adminUser != nullptr)
    {
        int adminChoice = 0;

        while (adminChoice != 6)
        {
            adminUser->showMenu();
            adminChoice = readValidUserInput(ENTER_CHOICE_PROMPT);
            executeAdminAction(adminUser, bank, adminChoice);
        }
    }
    else
    {
        std::cout << TECHNICAL_ERROR_MESSAGE;
    }
}

void handleDepositOperation(AccountHolder *accountHolderUser)
{
    double amount = readValidFloatingInput(DEPOSITE_AMOUNT_PROMPT);

    bool isDepositSuccessful =
        performDeposit(accountHolderUser, amount);

    if (isDepositSuccessful)
    {
        std::cout << DEPOSITE_SUCCESS_MESSAGE
                  << accountHolderUser->getAccount()->getBalance()
                  << "\n";
    }
    else
    {
        std::cout << DEPOSITE_AMOUNT_ERROR_MESSAGE;
    }
}

void handleWithdrawalOperation(AccountHolder *accountHolderUser)
{
    double amount = readValidFloatingInput(WITHDRAW_AMOUNT_PROMPT);

    bool isWithdrawalSuccessful =
        performWithdrawal(accountHolderUser, amount);

    if (isWithdrawalSuccessful)
    {
        std::cout << WITHDRAW_SUCCESS_MESSAGE
                  << accountHolderUser->getAccount()->getBalance()
                  << "\n";
    }
    else
    {
        if (amount <= 0)
        {
            std::cout << WITHDRAW_AMOUNT_ERROR_MESSAGE;
        }
        else
        {
            std::cout << WITHDRAW_ERROR_MESSAGE;
        }
    }
}

void executeAccountHolderAction(AccountHolder *accountHolderUser, int choice)
{
    switch (choice)
    {
    case 1:
        accountHolderUser->displayUserDetails();
        break;

    case 2:
        handleDepositOperation(accountHolderUser);
        break;

    case 3:
        handleWithdrawalOperation(accountHolderUser);
        break;

    case 4:
        std::cout << CURRENT_BALANCE_MESSAGE
                  << accountHolderUser->getAccount()->getBalance();
        break;

    case 5:
        accountHolderUser->getAccount()->displayMiniStatement();
        break;

    case 6:
        accountHolderUser->getAccount()->displayFullStatement();
        break;

    case 7:
        std::cout << LOGGING_OUT_MESSAGE;
        break;

    default:
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        break;
    }
}

void runAccountHolderSimulator(User *accountHolder)
{
    AccountHolder *accountHolderUser = dynamic_cast<AccountHolder *>(accountHolder);

    if (accountHolderUser != nullptr)
    {
        int accountHolderChoice = 0;

        while (accountHolderChoice != 7)
        {
            accountHolderUser->showMenu();
            accountHolderChoice = readValidUserInput(ENTER_CHOICE_PROMPT);
            executeAccountHolderAction(accountHolderUser, accountHolderChoice);
        }
    }
    else
    {
        std::cout << TECHNICAL_ERROR_MESSAGE;
    }
}

void runBankSimulator(IBank &bank)
{
    while (true)
    {
        int bankUserChoice = 0;

        displayWelcomeMessage(bank);
        bankUserChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

        if (bankUserChoice == 1)
        {
            User *adminUser = loginAdminFlow(bank);

            if (adminUser != nullptr)
            {
                runAdminSimulator(bank, adminUser);
            }
        }
        else if (bankUserChoice == 2)
        {
            User *accountHolderUser = loginAccountHolderFlow(bank);

            if (accountHolderUser != nullptr)
            {
                runAccountHolderSimulator(accountHolderUser);
            }
        }
        else if (bankUserChoice == 3)
        {
            std::cout << EXIT_PROGRAM_MESSAGE;
            break;
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }
}
