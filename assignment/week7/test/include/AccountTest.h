#ifndef ACCOUNT_TEST_H
#define ACCOUNT_TEST_H

#include <gtest/gtest.h>
#include "Account.h"
#include "Constants.h"

class AccountFixture : public ::testing::Test
{
protected:
    static constexpr int accountNumberZero_ = 1;
    static constexpr int accountNumberWithBalance_ = 2;
    static constexpr double zeroBalance_ = 0.0;
    static constexpr double initialBalance_ = 50.0;

    Account* accountZero_ = nullptr;
    Account* accountWithBalance_ = nullptr;

    void SetUp() override
    {
        accountZero_ = new Account(accountNumberZero_, zeroBalance_, ACTIVE);
        accountWithBalance_ = new Account(accountNumberWithBalance_, initialBalance_, ACTIVE);
    }

    void TearDown() override
    {
        delete accountZero_;
        delete accountWithBalance_;

        accountZero_ = nullptr;
        accountWithBalance_ = nullptr;
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
