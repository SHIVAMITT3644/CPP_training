#ifndef USER_H
#define USER_H
#include <string>

class User
{
    std::string name;
    std::string userName;
    std::string password;

    public:
    static std::string getValidPasswordInput();
    static std::string getValidUserNameInput();
    
    std::string getName() const;
    std::string getUserName() const;
    std::string getPassword() const;

    void setName(const std::string &name);
    void setUserName(const std::string &userName);
    void setPassword(const std::string &password);

    virtual void showMenu() const = 0;
};

#endif
