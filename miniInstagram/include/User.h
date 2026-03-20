#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    std::string userName;
    std::string name;
    std::string encryptedPassword;
    std::string bio;

public:
    User() = default;

    User(const std::string& userName,
         const std::string& name,
         const std::string& encryptedPassword,
         const std::string& bio);

    std::string getUserName() const;
    std::string getName() const;
    std::string getEncryptedPassword() const;
    std::string getBio() const;
};

#endif
