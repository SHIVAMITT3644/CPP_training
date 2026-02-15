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
        void addUser(User* user);
        void removeUser(int accountNumber, RemovalType type);
        void displayAllUsers() const;
        User* findUser(int accountNumber) const;
        User* findUser(const std::string &userName) const;

};   

#endif
