#include "FileUserStorage.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

FileUserStorage::FileUserStorage(const std::string& userDirectoryPath)
    : userDirectoryPath(userDirectoryPath)
{
    ensureUserDirectoryExists();
}

std::string FileUserStorage::getUserFilePath(const std::string& username) const
{
    return userDirectoryPath + "/" + username + ".json";
}

bool FileUserStorage::ensureUserDirectoryExists() const
{
    try
    {
        if (!std::filesystem::exists(userDirectoryPath))
        {
            return std::filesystem::create_directories(userDirectoryPath);
        }

        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool FileUserStorage::addUser(const User& user)
{
    if (!ensureUserDirectoryExists())
    {
        return false;
    }

    if (userExists(user.getUserName()))
    {
        return false;
    }

    json userJson;
    userJson["username"] = user.getUserName();
    userJson["name"] = user.getName();
    userJson["password"] = user.getEncryptedPassword();
    userJson["bio"] = user.getBio();

    std::ofstream outputFile(getUserFilePath(user.getUserName()));

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << userJson.dump(4);
    return outputFile.good();
}

bool FileUserStorage::updateUser(const User& user)
{
    if (!ensureUserDirectoryExists())
    {
        return false;
    }

    json userJson;
    userJson["username"] = user.getUserName();
    userJson["name"] = user.getName();
    userJson["password"] = user.getEncryptedPassword();
    userJson["bio"] = user.getBio();

    std::ofstream outputFile(getUserFilePath(user.getUserName()));

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << userJson.dump(4);
    return outputFile.good();
}

bool FileUserStorage::deleteUser(const std::string& username)
{
    try
    {
        std::string filePath = getUserFilePath(username);

        if (!std::filesystem::exists(filePath))
        {
            return false;
        }

        return std::filesystem::remove(filePath);
    }
    catch (...)
    {
        return false;
    }
}

std::optional<User> FileUserStorage::getUserByUsername(const std::string& username) const
{
    std::ifstream inputFile(getUserFilePath(username));

    if (!inputFile.is_open())
    {
        return std::nullopt;
    }

    try
    {
        json userJson;
        inputFile >> userJson;

        User user(
            userJson.value("username", ""),
            userJson.value("name", ""),
            userJson.value("password", ""),
            userJson.value("bio", "")
        );

        if (user.getUserName().empty())
        {
            return std::nullopt;
        }

        return user;
    }
    catch (...)
    {
        return std::nullopt;
    }
}

bool FileUserStorage::userExists(const std::string& username) const
{
    return std::filesystem::exists(getUserFilePath(username));
}

std::vector<User> FileUserStorage::getAllUsers() const
{
    std::vector<User> users;

    if (!std::filesystem::exists(userDirectoryPath))
    {
        return users;
    }

    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(userDirectoryPath))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            if (entry.path().extension() != ".json")
            {
                continue;
            }

            std::ifstream inputFile(entry.path());

            if (!inputFile.is_open())
            {
                continue;
            }

            json userJson;
            inputFile >> userJson;

            User user(
                userJson.value("username", ""),
                userJson.value("name", ""),
                userJson.value("password", ""),
                userJson.value("bio", "")
            );

            if (!user.getUserName().empty())
            {
                users.push_back(user);
            }
        }
    }
    catch (...)
    {
        return users;
    }

    return users;
}
