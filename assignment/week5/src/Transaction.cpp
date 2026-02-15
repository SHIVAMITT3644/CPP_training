#include "Transaction.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string Transaction::getCurrentDateAndTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(local_time, "%d-%m-%Y %H:%M:%S");

    return oss.str();
}

Transaction::Transaction(int transactionID, double amount, const std::string &transactionType)
{
    this->transactionID = transactionID;
    this->amount = amount;
    this->transactionType = transactionType;
    this->dateAndTime = getCurrentDateAndTime();
}

void Transaction::displayTransactionDetails() const
{
    std::cout << "|" << dateAndTime << " |  "  << transactionID << "  | " << transactionType << " | " << amount << " \n";
}
