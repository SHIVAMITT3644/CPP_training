#ifndef BANK_TEST_H
#define BANK_TEST_H

#include <gtest/gtest.h>
#include "Bank.h"

class BankFixture : public ::testing::Test
{
protected:
    Bank* bank_ = nullptr;

    static constexpr const char* bankName = "Test";

    void SetUp() override
    {
        bank_ = new Bank(bankName);
    }

    void TearDown() override
    {
        delete bank_;
        bank_ = nullptr;
    }
};

#endif
