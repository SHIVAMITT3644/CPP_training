#include <iostream>
#include "Bank.h"
#include "BankSimulator.h"
#include "Admin.h"

int main()
{
    Bank bank("ITT Tech Bank");
    bank.addUser(new Admin("Shivam Pratap", "shivam123", "admin123"));

    runBankSimulator(bank);
    return 0;
}
