#ifndef ACCOUNT_TEST_H
#define ACCOUNT_TEST_H

#include <gtest/gtest.h>
#include "Account.h"
#include "Constants.h"

class AccountFixture : public ::testing::Test
{
protected:
    static constexpr int accountNumber = 1;
    static constexpr double zeroBalance = 0.0;
    static constexpr double initialBalance = 50.0;

    Account* accountZero = nullptr;
    Account* accountWithBalance = nullptr;

    void SetUp() override
    {
        accountZero = new Account(accountNumber, zeroBalance, ACTIVE);
        accountWithBalance = new Account(accountNumber, initialBalance, ACTIVE);
    }

    void TearDown() override
    {
        delete accountZero;
        delete accountWithBalance;

        accountZero = nullptr;
        accountWithBalance = nullptr;
    }
};

class AccountDepositInvalidAmountFixture
    : public AccountFixture,
      public ::testing::WithParamInterface<double>
{
};

class AccountWithdrawInvalidAmountFixture
    : public AccountFixture,
      public ::testing::WithParamInterface<double>
{
};

#endif 
