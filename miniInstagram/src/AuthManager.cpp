#include "AuthManager.h"

AuthManager::AuthManager(UserManager& userManager, ICryptoService& cryptoService)
    : userManager(userManager),
      cryptoService(cryptoService)
{
}

bool AuthManager::isValidUsername(const std::string& username) const
{
    return username.length() >= 5;
}

bool AuthManager::isValidPassword(const std::string& password) const
{
    return password.length() >= 5;
}

bool AuthManager::isValidName(const std::string& name) const
{
    return !name.empty();
}

bool AuthManager::signUp(const std::string& username,
                         const std::string& name,
                         const std::string& password,
                         const std::string& bio)
{
    if (!isValidUsername(username))
    {
        return false;
    }

    if (!isValidName(name))
    {
        return false;
    }

    if (!isValidPassword(password))
    {
        return false;
    }

    if (userManager.userExists(username))
    {
        return false;
    }

    std::string encryptedPassword = cryptoService.encrypt(password);
    User newUser(username, name, encryptedPassword, bio);

    return userManager.createUser(newUser);
}

bool AuthManager::signIn(const std::string& username, const std::string& password)
{
    std::optional<User> storedUser = userManager.getUserByUsername(username);

    if (!storedUser.has_value())
    {
        return false;
    }

    std::string decryptedPassword = cryptoService.decrypt(storedUser->getEncryptedPassword());

    if (decryptedPassword != password)
    {
        return false;
    }

    loggedInUser = storedUser;
    return true;
}

void AuthManager::signOut()
{
    loggedInUser.reset();
}

bool AuthManager::isUserLoggedIn() const
{
    return loggedInUser.has_value();
}

std::optional<User> AuthManager::getLoggedInUser() const
{
    return loggedInUser;
}
