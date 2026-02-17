#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Bank.h"

class Admin : public User
{
    public:
    void showMenu() const override;
    
    Admin(const std::string &name, const std::string &userName, const std::string &password);
    void createAccountHolderAccount(Bank& bank);
    void deleteAccountHolderAccount(Bank& bank ,int accountNumber, Bank::RemovalType type);
    void viewAllAccountHolders(const Bank& bank) const;
    void viewAccountHolderBalance(const Bank& bank) const;
    void viewAccountHolderTransactionHistory(const Bank& bank) const;
};

#endif
