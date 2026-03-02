#ifndef ADMIN_H
#define ADMIN_H

#include "IUser.h"

class Admin : public User
{
public:
    Admin(const std::string &name, const std::string &userName, const std::string &password);

    void showMenu() const override;

    bool isAdmin() const override;

    bool viewAccountHolderBalance(User* user) const;
    bool viewAccountHolderTransactionHistory(User* user) const;
};

#endif
