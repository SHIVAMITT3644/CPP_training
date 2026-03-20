#include "User.h"

User::User(const std::string& userName,
           const std::string& name,
           const std::string& encryptedPassword,
           const std::string& bio)
    : userName(userName),
      name(name),
      encryptedPassword(encryptedPassword),
      bio(bio)
{
}

std::string User::getUserName() const
{
    return userName;
}

std::string User::getName() const
{
    return name;
}

std::string User::getEncryptedPassword() const
{
    return encryptedPassword;
}

std::string User::getBio() const
{
    return bio;
}
