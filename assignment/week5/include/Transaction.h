#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

class Transaction
{
    int transactionID;
    double amount;
    std::string transactionType;
    std::string dateAndTime;
    std::string getCurrentDateAndTime();

public:

    Transaction(int transactionID, double amount, const std::string &transactionType);
    void displayTransactionDetails() const;
};

#endif
