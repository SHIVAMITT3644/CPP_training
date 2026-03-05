#ifndef ADMIN_TEST_H
#define ADMIN_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Admin.h"
#include "MockUser.h"
#include "Account.h"

class AdminFixture : public ::testing::Test
{
protected:
    Admin* admin_ = nullptr;
    MockUser* mockUser_ = nullptr;
    Account* account_ = nullptr;

    void SetUp() override
    {
        admin_ = new Admin("Admin", "adminUser", "adminPass");
        mockUser_ = new MockUser();
        account_ = new Account(1, 500.0);
    }

    void TearDown() override
    {
        delete account_;
        delete mockUser_;
        delete admin_;
    }
};

#endif
