#ifndef ACCOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include "User.h"
#include "Account.h"

class AccountHolder : public User
{
    Account* account;

public:
    AccountHolder(const std::string &name,
                  const std::string &userName,
                  const std::string &password,
                  int accountNumber,
                  double initialBalance);

    ~AccountHolder();

    Account* getAccount() const;

    void showMenu() const override;
    void displayUserDetails() const;
};

#endif
