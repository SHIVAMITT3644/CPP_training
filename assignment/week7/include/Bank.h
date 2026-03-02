#ifndef BANK_H
#define BANK_H

#include <string>
#include "IBank.h"

class User;

class Bank : public IBank
{
private:
    std::string bankName;
    int numberOfUsers;
    int capacityOfUsers;
    User** users;

    int accountNumberGenerator;

    void resizeIfNeeded();

public:
    Bank(const std::string &bankName);
    ~Bank();

    std::string getBankName() const override;

    int generateAccountNumber() override;

    bool addUser(User *user) override;
    bool removeUser(int accountNumber, IBank::RemovalType type) override;

    void displayAllUsers() const ;

    User* findUser(int accountNumber) const override;
    User* findUser(const std::string &userName) const override;

    User* login(IBank::Role role, const std::string &id, const std::string &password) const override;
};

#endif
