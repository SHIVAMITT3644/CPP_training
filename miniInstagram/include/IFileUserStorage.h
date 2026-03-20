#ifndef IFILEUSERSTORAGE_H
#define IFILEUSERSTORAGE_H

#include <string>
#include <vector>
#include <optional>
#include "User.h"

class IFileUserStorage
{
public:
    virtual ~IFileUserStorage() = default;

    virtual bool addUser(const User& user) = 0;
    virtual bool updateUser(const User& user) = 0;
    virtual bool deleteUser(const std::string& username) = 0;

    virtual std::optional<User> getUserByUsername(const std::string& username) const = 0;
    virtual bool userExists(const std::string& username) const = 0;
    virtual std::vector<User> getAllUsers() const = 0;
};

#endif
