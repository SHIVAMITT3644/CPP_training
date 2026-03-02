#ifndef ACCOUNT_HOLDER_TEST_H
#define ACCOUNT_HOLDER_TEST_H

#include <gtest/gtest.h>
#include "AccountHolder.h"

class AccountHolderFixture : public ::testing::Test
{
protected:
    static constexpr int accountNumber = 10;
    static constexpr double initialBalance = 1000.0;

    AccountHolder* accountHolder = nullptr;

    void SetUp() override
    {
        accountHolder = new AccountHolder("Name", "user1", "pass1", accountNumber, initialBalance);
    }

    void TearDown() override
    {
        delete accountHolder;
        accountHolder = nullptr;
    }
};

class AccountHolderDepositInvalidAmountFixture
    : public AccountHolderFixture,
      public ::testing::WithParamInterface<double>
{
};

class AccountHolderWithdrawInvalidAmountFixture
    : public AccountHolderFixture,
      public ::testing::WithParamInterface<double>
{
};

#endif
