#ifndef FILEUSERSTORAGE_H
#define FILEUSERSTORAGE_H

#include <string>
#include <vector>
#include <optional>
#include "IFileUserStorage.h"
#include "User.h"

class FileUserStorage : public IFileUserStorage
{
private:
    std::string userDirectoryPath;

    std::string getUserFilePath(const std::string& username) const;
    bool ensureUserDirectoryExists() const;

public:
    explicit FileUserStorage(const std::string& userDirectoryPath);

    bool addUser(const User& user) override;
    bool updateUser(const User& user) override;
    bool deleteUser(const std::string& username) override;

    std::optional<User> getUserByUsername(const std::string& username) const override;
    bool userExists(const std::string& username) const override;
    std::vector<User> getAllUsers() const override;
};

#endif
