#ifndef BANK_SIMULATOR_TEST_H
#define BANK_SIMULATOR_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MockUser.h"
#include "MockBank.h"
#include "Account.h"
#include "IBank.h"

class BankSimulatorFixture : public ::testing::Test
{
protected:
    MockUser mockUser_;
    Account account_{101, 500.0};
};

class BankUsecaseFixture : public ::testing::Test
{
protected:
    MockBank mockBank_;
    int createdAccountNumber_ ;

    void SetUp() override
    {
        createdAccountNumber_ = 0;
    }
};

#endif
