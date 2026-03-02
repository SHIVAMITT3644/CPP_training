#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
class AccountHolder;

class Admin : public User
{
    
public:
    Admin(const std::string &name, const std::string &userName, const std::string &password);

    void showMenu() const override;

    AccountHolder* getValidAccountHolder(User* user) const;

    bool viewAccountHolderBalance(User* user) const;

    bool viewAccountHolderTransactionHistory(User* user) const;
};

#endif
