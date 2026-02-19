#ifndef BANK_H
#define BANK_H                                                
#include<string>

class User;
    
class Bank                               
{  
        std::string bankName;
        int numberOfUsers;
        int capacityOfUsers;
        User** users;   

    User* loginAccountHolder() const;
    User* loginAdmin() const;

    public:  

        enum class RemovalType
        {
            Temporary,
            Permanent
        };

        static int accountNumberGenerator;                                                
        Bank(const std::string &bankName); 
        ~Bank();

        std::string getBankName() const;        
        bool addUser(User *user);
        bool removeUser(int accountNumber, RemovalType type);
        void displayAllUsers() const;
        User* findUser(int accountNumber) const;
        User* findUser(const std::string &userName) const;
        User* login(const std::string& role) const;
};   

#endif
