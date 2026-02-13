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

    if(balance > 0)
    {
        addTransaction(balance, "Initial Deposit");
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

    transactionCount++;
    *(transactions + transactionCount) = new Transaction(transactionCount, amount, type);

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

    amount = readValidatedDecimalNumber(DEPOSITE_AMOUNT_PROMPT);

    if (amount > 0)
    {
        balance += amount;
        addTransaction(amount, "Deposit   ");
        isDepositSuccessful = true;
    }

    return isDepositSuccessful;
}

bool Account::withdraw()
{
    double amount;
    bool isWithdrawalSuccessful = false;

    amount = readValidatedDecimalNumber(WITHDRAW_AMOUNT_PROMPT);

    if (amount > 0)
    {
        if (amount < balance)
        {
            balance -= amount;
            addTransaction(amount, "Withdrawal");

            isWithdrawalSuccessful = true;
        }
        else
        {
            std::cout << INSUFFICIENT_BALANCE_ERROR_MESSAGE;
        }
    }

    return isWithdrawalSuccessful;  
}

void Account::showTransactions(int startIndex) const
{
    if(transactionCount == 0)
    {
        std::cout << "\nNo transactions has done yet.\n";
    }
    else
    {
        std::cout << TRANSACTION_STATEMENT_HEADER;
        for (int transactionIndex = startIndex; transactionIndex < transactionCount; transactionIndex++)
        {
            (*(transactions + transactionIndex))->displayTransactionDetails();
        }
    }   
}

void Account::displayMiniStatement() const
{
    std::cout << "\nMini Statement for Account Number: " << accountNumber << "\n";
    
    int startTransactionIndex = transactionCount > 5 ? transactionCount - 5 : 0;
    showTransactions(startTransactionIndex);
}

void Account::displayFullStatement() const
{
    std::cout << "\nFull Statement for Account Number: " << accountNumber << "\n";
    showTransactions(0);
}



void Account::displayAccountDetails() const
{
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Balance: " << balance << "\n";
    std::cout << "Status: " << status << "\n";
}