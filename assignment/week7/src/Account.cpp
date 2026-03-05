#include <iostream>
#include "Account.h"
#include "Constants.h"

Account::Account(int accountNumber, double balance, const std::string &status)
{
    this->accountNumber = accountNumber;
    this->balance = balance;
    this->status = status;

    this->transactionCount = 0;
    this->transactionsCapacity = 0;
    this->transactions = nullptr;

    if (balance > 0)
    {
        addTransaction(balance, INITIAL_DEPOSIT);
    }
}

void Account::addTransaction(double amount, const std::string &type)
{
    if (transactionCount == 0)
    {
        transactionsCapacity = 1;
        transactions = new Transaction*[transactionsCapacity];
    }
    else if (transactionCount == transactionsCapacity)
    {
        transactionsCapacity *= 2;

        Transaction** newTransactionsArray = new Transaction*[transactionsCapacity];

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
    status = newStatus;
}

bool Account::deposit(double amount)
{
    bool isDepositSuccessful = false;

    if (amount > 0)
    {
        balance += amount;
        addTransaction(amount, DEPOSITE);
        isDepositSuccessful = true;
    }

    return isDepositSuccessful;
}

bool Account::withdraw(double amount)
{
    bool isWithdrawalSuccessful = false;

    if (amount > 0)
    {
        if (amount <= balance)
        {
            balance -= amount;
            addTransaction(amount, WITHDRAW);
            isWithdrawalSuccessful = true;
        }
    }

    return isWithdrawalSuccessful;
}

void Account::displayTransactions(int startIndex) const
{
    if (transactionCount == 0)
    {
        std::cout << NO_TRANSACTION_ERROR_MESSAGE;
    }
    else
    {
        std::cout << TRANSACTION_STATEMENT_HEADER;

        for (int transactionIndex = startIndex;
             transactionIndex < transactionCount;
             transactionIndex++)
        {
            (*(transactions + transactionIndex))
                ->displayTransactionDetails();
        }

        std::cout << CURRENT_BALANCE_MESSAGE
                  << getBalance() << "\n";
    }
}

void Account::displayMiniStatement() const
{
    std::cout << MINI_STATEMENT_MESSAGE
              << accountNumber << "\n";

    int startTransactionIndex =
        transactionCount > 5 ? transactionCount - 5 : 0;

    displayTransactions(startTransactionIndex);
}

void Account::displayFullStatement() const
{
    std::cout << FULL_STATEMENT_MESSAGE
              << accountNumber << "\n";

    displayTransactions(0);
}

void Account::displayAccountDetails() const
{
    std::cout << ACCOUNT_NUMBER << accountNumber << "\n";
    std::cout << BALANCE << balance << "\n";
    std::cout << STATUS << status << "\n";
}
