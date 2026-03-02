#ifndef ACCOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include "IUser.h"
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

    bool isAccountHolder() const override;

    Account* getAccount() const override;

    void showMenu() const override;
    void displayUserDetails() const;
};

#endif