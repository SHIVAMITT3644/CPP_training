#ifndef MOCK_BANK_H
#define MOCK_BANK_H

#include <gmock/gmock.h>
#include "IBank.h"

class MockBank : public IBank
{
public:
    MOCK_METHOD(std::string, getBankName, (), (const, override));

    MOCK_METHOD(int, generateAccountNumber, (), (override));

    MOCK_METHOD(bool, addUser, (User *user), (override));
    MOCK_METHOD(bool, removeUser, (int accountNumber, IBank::RemovalType type), (override));

    MOCK_METHOD(void, displayAllUsers, (), (const, override));

    MOCK_METHOD(User*, findUser, (int accountNumber), (const, override));
    MOCK_METHOD(User*, findUser, (const std::string &userName), (const, override));

    MOCK_METHOD(User*, login, (IBank::Role role, const std::string &id, const std::string &password), (const, override));
};

#endif
