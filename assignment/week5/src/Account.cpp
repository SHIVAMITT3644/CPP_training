#include <iostream>
#include "Account.h"
#include "Constants.h"
#include "Input.h"

Account::Account(int accountNumber, double balance, const std::string &status)
{
    this->accountNumber = accountNumber;
    this->balance = balance;
    this->status = status;
    this->transactionCount = 0;
    this->transactionsCapacity = 0;

    if (balance > 0)
    {
        addTransaction(balance, INITIAL_DEPOSIT);
    }
    else
    {
        transactions = nullptr;
    }
}

void Account::addTransaction(double amount, const std::string &type)
{

    if (transactionCount == 0)
    {
        transactionsCapacity = 1;
        transactions = new Transaction *[transactionsCapacity];
    }
    else if (transactionCount == transactionsCapacity)
    {
        transactionsCapacity *= 2;

        Transaction **newTransactionsArray = new Transaction *[transactionsCapacity];

        for (int transactionIndex = 0; transactionIndex < transactionCount; transactionIndex++)
        {
            *(newTransactionsArray + transactionIndex) = *(transactions + transactionIndex);
        }

        delete[] transactions;
        transactions = newTransactionsArray;
    }

    *(transactions + transactionCount) = new Transaction(transactionCount + 1, amount, type);
    transactionCount++;
}

Account::~Account()
{
    for (int transactionIndex = 0; transactionIndex < transactionCount; transactionIndex++)
    {
        delete *(transactions + transactionIndex);
    }

    delete[] transactions;
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

double Account::getBalance() const
{
    return balance;
}

std::string Account::getStatus() const
{
    return status;
}

void Account::changeStatus(const std::string &newStatus)
{
    this->status = newStatus;
}

bool Account::deposit()
{
    double amount;
    bool isDepositSuccessful = false;

    amount = readValidFloatingInput(DEPOSITE_AMOUNT_PROMPT);

    while (true)
    {
        if (amount > 0)
        {
            balance += amount;
            addTransaction(amount, DEPOSITE);
            isDepositSuccessful = true;
            break;
        }
        else
        {
            std::cout << DEPOSITE_AMOUNT_ERROR_MESSAGE;
            amount = readValidFloatingInput(DEPOSITE_AMOUNT_PROMPT);
        }
    }

    return isDepositSuccessful;
}

bool Account::withdraw()
{
    double amount;
    bool isWithdrawalSuccessful = false;
    amount = readValidFloatingInput(WITHDRAW_AMOUNT_PROMPT);

    while (true)
    {
        if (amount > 0)
        {
            if (amount <= balance)
            {
                balance -= amount;
                addTransaction(amount, WITHDRAW);
                isWithdrawalSuccessful = true;
                break;
            }
            else
            {
                std::cout << WITHDRAW_ERROR_MESSAGE;
                amount = readValidFloatingInput(WITHDRAW_AMOUNT_PROMPT);
            }
        }
        else
        {
            std::cout << WITHDRAW_AMOUNT_ERROR_MESSAGE;
            amount = readValidFloatingInput(WITHDRAW_AMOUNT_PROMPT);
        }
    }

    return isWithdrawalSuccessful;
}

void Account::showTransactions(int startIndex) const
{
    if (transactionCount == 0)
    {
        std::cout << NO_TRANSACTION_ERROR_MESSAGE;
    }
    else
    {
        std::cout << TRANSACTION_STATEMENT_HEADER;

        for (int transactionIndex = startIndex; transactionIndex < transactionCount; transactionIndex++)
        {
            (*(transactions + transactionIndex))->displayTransactionDetails();
        }
        std ::cout << CURRENT_BALANCE_MESSAGE << getBalance() << "\n";
    }
}

void Account::displayMiniStatement() const
{
    std::cout << MINI_STATEMENT_MESSAGE << accountNumber << "\n";

    int startTransactionIndex = transactionCount > 5 ? transactionCount - 5 : 0;
    showTransactions(startTransactionIndex);
}

void Account::displayFullStatement() const
{
    std::cout << FULL_STATEMENT_MESSAGE << accountNumber << "\n";
    showTransactions(0);
}

void Account::displayAccountDetails() const
{
    std::cout << ACCOUNT_NUMBER << accountNumber << "\n";
    std::cout << BALANCE << balance << "\n";
    std::cout << STATUS << status << "\n";
}
