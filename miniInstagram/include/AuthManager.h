#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <optional>
#include "UserManager.h"
#include "ICryptoService.h"
#include "User.h"

class AuthManager
{
private:
    UserManager& userManager;
    ICryptoService& cryptoService;
    std::optional<User> loggedInUser;

    bool isValidUsername(const std::string& username) const;
    bool isValidPassword(const std::string& password) const;
    bool isValidName(const std::string& name) const;

public:
    AuthManager(UserManager& userManager, ICryptoService& cryptoService);

    bool signUp(const std::string& username,
                const std::string& name,
                const std::string& password,
                const std::string& bio);

    bool signIn(const std::string& username, const std::string& password);

    void signOut();

    bool isUserLoggedIn() const;
    std::optional<User> getLoggedInUser() const;
};

#endif
