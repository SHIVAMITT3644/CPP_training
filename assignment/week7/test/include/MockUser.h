#ifndef MOCK_USER_H
#define MOCK_USER_H

#include <gmock/gmock.h>
#include "IUser.h"

class MockUser : public User
{
public:
    MOCK_METHOD(void, showMenu, (), (const, override));

    MOCK_METHOD(std::string, getName, (), (const, override));
    MOCK_METHOD(std::string, getUserName, (), (const, override));
    MOCK_METHOD(std::string, getPassword, (), (const, override));

    MOCK_METHOD(bool, isAccountHolder, (), (const, override));
    MOCK_METHOD(bool, isAdmin, (), (const, override));

    MOCK_METHOD(Account*, getAccount, (), (const, override));
};

#endif
