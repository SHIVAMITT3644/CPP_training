#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Transaction.h"

class Account
{
    int accountNumber;
    double balance;
    std::string status;
    Transaction** transactions;
    int transactionCount;
    int transactionsCapacity;
    void addTransaction(double amount, const std::string &type);
    void displayTransactions(int startIndex) const;

public:
    Account(int accountNumber, double balance , const std::string &status = "Active");
    ~Account();
    int getAccountNumber() const;
    double getBalance() const;
    std::string getStatus() const;
    void changeStatus(const std::string &newStatus);
    
    bool deposit();
    bool withdraw();
    void displayMiniStatement() const;
    void displayFullStatement() const;
    void displayAccountDetails() const;
};

#endif
