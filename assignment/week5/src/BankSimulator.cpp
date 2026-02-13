#include <iostream>
#include "BankSimulator.h"
#include "Bank.h"
#include "Admin.h"
#include "AccountHolder.h"
#include "Input.h"
#include "Constants.h"

void displayWelcomeMessage(const Bank &bank)
{
    std::cout << "\nWelcome to " << bank.getBankName() << " Simulator!\n";
    std::cout << "1.Admin\n";
    std::cout << "2.Account Holder\n";
    std::cout << "3.Exit\n";
}

void deleteAccountByType(Admin *adminUser, Bank &bank, Bank::RemovalType type)
{
    int accountNumber;
    int deleteTypeChoice;

    while (deleteTypeChoice != 1 && deleteTypeChoice != 2)
    {
        std::cout << "----------------------------\n";
        std::cout << "1.Temperory Delete\n";
        std::cout << "2.Permanent Delete\n";
        std::cout << "----------------------------\n";

        deleteTypeChoice = readValidatedIntegerNumber(ENTER_CHOICE_PROMPT);

        if (deleteTypeChoice == 1)
        {
            accountNumber = readValidatedIntegerNumber(ACCOUNT_NUMBER_INPUT_PROMPT);
            adminUser->deleteAccountHolderAccount(bank, accountNumber, Bank::RemovalType::Temporary);
        }
        else if (deleteTypeChoice == 2)
        {
            accountNumber = readValidatedIntegerNumber(ACCOUNT_NUMBER_INPUT_PROMPT);
            adminUser->deleteAccountHolderAccount(bank, accountNumber, Bank::RemovalType::Permanent);
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }
}

void executeAdminAction(Admin *adminUser, Bank &bank, int choice)
{
    switch (choice)
    {
    case 1:
        adminUser->createAccountHolderAccount(bank);
        break;

    case 2:
        deleteAccountByType(adminUser, bank, Bank::RemovalType::Temporary);
        break;

    case 3:
        adminUser->viewAllAccountHolders(bank);
        break;

    case 4:
    {
        int accountNumberForBalance;
        accountNumberForBalance = readValidatedIntegerNumber(ACCOUNT_NUMBER_INPUT_PROMPT);
        adminUser->viewAccountHolderBalance(bank, accountNumberForBalance);
        break;
    }

    case 5:
    {
        int accountNumberForTransactionHistory;
        accountNumberForTransactionHistory = readValidatedIntegerNumber(ACCOUNT_NUMBER_INPUT_PROMPT);
        adminUser->viewAccountHolderTransactionHistory(bank, accountNumberForTransactionHistory);
        break;
    }
    case 6:
        std::cout << "\nLogging out...\n";
        break;

    default:
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        break;
    }
}

void runAdminSimulator(Bank &bank, User *admin)
{
    Admin *adminUser = dynamic_cast<Admin *>(admin);

    if (adminUser != nullptr)
    {
        int adminChoice;

        while (adminChoice != 6)
        {
            adminUser->showMenu();
            adminChoice = readValidatedIntegerNumber(ENTER_CHOICE_PROMPT);
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
    if (accountHolderUser->getAccount()->deposit())
    {
        std::cout << DEPOSITE_SUCCESS_MESSAGE << accountHolderUser->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << DEPOSITE_ERROR_MESSAGE;
    }
}

void handleWithdrawalOperation(AccountHolder *accountHolderUser)
{
    if (accountHolderUser->getAccount()->withdraw())
    {
        std::cout << WITHDRAW_SUCCESS_MESSAGE << accountHolderUser->getAccount()->getBalance() << "\n";
    }
    else
    {
        std::cout << WITHDRAW_ERROR_MESSAGE;
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
        accountHolderUser->getAccount()->displayMiniStatement();
        break;

    case 5:
        accountHolderUser->getAccount()->displayFullStatement();
        break;

    case 6:
        std::cout << "\nLogging out...\n";
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
        int accountHolderChoice;

        while (accountHolderChoice != 6)
        {
            accountHolderUser->showMenu();
            accountHolderChoice = readValidatedIntegerNumber(ENTER_CHOICE_PROMPT);
            executeAccountHolderAction(accountHolderUser, accountHolderChoice);
        }
    }
    else
    {
        std::cout << TECHNICAL_ERROR_MESSAGE;
    }
}

void runBankSimulator(Bank &bank)
{
    while (true)
    {
        int bankUserChoice;
        displayWelcomeMessage(bank);
        
        bankUserChoice = readValidatedIntegerNumber(ENTER_CHOICE_PROMPT);

        if (bankUserChoice == 1)
        {
            User *admin = User::login(bank, "Admin");

            if (admin != nullptr)
            {
                runAdminSimulator(bank, admin);
            }
        }

        else if (bankUserChoice == 2)
        {
            User *accountHolder = User::login(bank, "AccountHolder");
            if (accountHolder != nullptr)
            {
                runAccountHolderSimulator(accountHolder);
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
