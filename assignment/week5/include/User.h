#ifndef USER_H
#define USER_H
#include <string>

class Bank;

class User
{
    std::string name;
    std::string userName;
    std::string password;
    static User* accountHolderLogin(const Bank& bank);
    static User* adminLogin(const Bank& bank);
    std::string getPassword() const;

    public:
    static std::string getValidPasswordInput();
    static std::string getValidUserNameInput();
    
    std::string getName() const;
    std::string getUserName() const;

    void setName(const std::string &name);
    void setUserName(const std::string &userName);
    void setPassword(const std::string &password);

    static User* login(const Bank& bank , std::string userType);
    virtual void showMenu() const = 0;
};

#endif
