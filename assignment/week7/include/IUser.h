#ifndef USER_H
#define USER_H

#include <string>

class Account;

class User
{
private:
    std::string name;
    std::string userName;
    std::string password;

public:
    virtual ~User() = default;

    static std::string getValidPasswordInput();
    static std::string getValidUserNameInput();

    virtual std::string getName() const;
    virtual std::string getUserName() const;
    virtual std::string getPassword() const;

    void setName(const std::string &name);
    void setUserName(const std::string &userName);
    void setPassword(const std::string &password);

    virtual void showMenu() const = 0;

    virtual bool isAccountHolder() const;
    virtual bool isAdmin() const;
    
    virtual Account* getAccount() const;
};

#endif