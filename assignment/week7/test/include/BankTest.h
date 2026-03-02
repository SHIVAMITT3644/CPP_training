#ifndef BANK_TEST_H
#define BANK_TEST_H

#include <gtest/gtest.h>

#include "Bank.h"
#include "Admin.h"
#include "AccountHolder.h"
#include "Constants.h"

class BankFixture : public ::testing::Test
{
protected:
    Bank* bank = nullptr;

    static constexpr const char* bankName = "Test";

    static constexpr const char* setupAdminName = "SetupAdmin";
    static constexpr const char* setupAdminUser = "adminUser";
    static constexpr const char* setupAdminPass = "adminPass";

    void SetUp() override
    {
        bank = new Bank(bankName);

        bank->addUser(new Admin(setupAdminName, setupAdminUser, setupAdminPass));
    }

    void TearDown() override
    {
        delete bank;
        bank = nullptr;
    }
};

#endif
