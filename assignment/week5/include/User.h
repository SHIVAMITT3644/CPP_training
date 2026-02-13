#ifndef USER_H
#define USER_H
#include <string>

class Bank;

class User
{
    std::string userName;
    std::string email;
    std::string password;
    static User* accountHolderLogin(const Bank& bank);
    static User* adminLogin(const Bank& bank);
    std::string getPassword() const;

    public:
    static User* login(const Bank& bank , std::string userType);
    virtual void showMenu() const = 0;

    std::string getUserName() const;
    std::string getUserEmail() const;
    

    void setUserName(const std::string &userName);
    void setEmail(const std::string &email);
    void setPassword(const std::string &password);
    
};

#endif