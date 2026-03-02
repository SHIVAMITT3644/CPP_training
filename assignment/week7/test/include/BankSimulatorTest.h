#ifndef BANK_SIMULATOR_TEST_H
#define BANK_SIMULATOR_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "AccountHolder.h"
#include "Admin.h"
#include "MockBank.h"

class BankSimulatorFixture : public ::testing::Test
{
protected:
    AccountHolder* user = nullptr;

    void SetUp() override
    {
        user = new AccountHolder("Name", "u1", "p1", 101, 500);
    }

    void TearDown() override
    {
        delete user;
        user = nullptr;
    }
};

class BankUsecaseFixture : public ::testing::Test
{
protected:
    MockBank bank;
    int createdAccountNumber = 0;

    void SetUp() override
    {
        createdAccountNumber = 0;
    }
};

#endif
