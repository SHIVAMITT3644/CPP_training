#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>
#include <optional>
#include "IFileUserStorage.h"
#include "User.h"

class UserManager
{
private:
    IFileUserStorage& userStorage;

public:
    UserManager(IFileUserStorage& userStorage);

    bool createUser(const User& user);
    bool updateUser(const User& user);
    bool deleteUser(const std::string& username);

    bool userExists(const std::string& username) const;
    std::optional<User> getUserByUsername(const std::string& username) const;
    std::vector<User> getAllUsers() const;
};

#endif
