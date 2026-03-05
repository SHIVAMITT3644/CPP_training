#ifndef IBANK_H
#define IBANK_H

#include <string>

class User;

class IBank
{
public:
    enum class RemovalType
    {
        Temporary,
        Permanent
    };

    enum class Role
    {
        Admin,
        AccountHolder
    };

    virtual ~IBank() = default;

    virtual std::string getBankName() const = 0;

    virtual int generateAccountNumber() = 0;

    virtual bool addUser(User *user) = 0;
    virtual bool removeUser(int accountNumber, RemovalType type) = 0;

    virtual void displayAllUsers() const = 0;

    virtual User* findUser(int accountNumber) const = 0;
    virtual User* findUser(const std::string &userName) const = 0;

    virtual User* login(Role role, const std::string &id, const std::string &password) const = 0;
};

#endif
