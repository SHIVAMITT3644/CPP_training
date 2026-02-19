#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User
{
    public:
    void showMenu() const override;
    
    Admin(const std::string &name, const std::string &userName, const std::string &password);
    void viewAccountHolderBalance(User* user) const;
    void viewAccountHolderTransactionHistory(User* user) const;
};

#endif
