#include "UserManager.h"

UserManager::UserManager(IFileUserStorage& userStorage)
    : userStorage(userStorage)
{
}

bool UserManager::createUser(const User& user)
{
    if (userStorage.userExists(user.getUserName()))
    {
        return false;
    }

    return userStorage.addUser(user);
}

bool UserManager::updateUser(const User& user)
{
    if (!userStorage.userExists(user.getUserName()))
    {
        return false;
    }

    return userStorage.updateUser(user);
}

bool UserManager::deleteUser(const std::string& username)
{
    if (!userStorage.userExists(username))
    {
        return false;
    }

    return userStorage.deleteUser(username);
}

bool UserManager::userExists(const std::string& username) const
{
    return userStorage.userExists(username);
}

std::optional<User> UserManager::getUserByUsername(const std::string& username) const
{
    return userStorage.getUserByUsername(username);
}

std::vector<User> UserManager::getAllUsers() const
{
    return userStorage.getAllUsers();
}
